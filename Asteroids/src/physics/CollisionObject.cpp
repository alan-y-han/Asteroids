#include "CollisionObject.h"
#include "Config.h"
#include "Quadtree.h"

// debug
#include <iostream>


CollisionObject::CollisionObject(GameObject& gameObject) :
    gameObject(gameObject)
{
}

void CollisionObject::generateMesh(const std::vector<glm::vec2>& vertices, Transform& transform)
{
    worldVertices.clear();
    unsplitCollisionMesh.clear();
    collisionMesh.clear();


    // debug
    if (vertices.size() < 2)
    {
        std::cerr << "CollisionObject: generateMesh supplied with <2 vertices, no mesh generated" << std::endl;
        return;
    }
    // end debug


    glm::mat4 model = transform.getModelMatrix(0, 0);
    for (const glm::vec2& v : vertices)
    {
        worldVertices.push_back(model * glm::vec4(v, 0.0f, 1.0f)); // TODO: maybe use emplace_back
        // unsplitCollisionMesh creates new objects so safe to use .back() pointers
        addMotionLineToMesh(worldVertices.back(), transform);
    }

    // special case to prevent doubling a line
    if (worldVertices.size() == 2)
    {
        addLineToMesh(0);
    }
    else
    {
        for (unsigned int i = 0; i < worldVertices.size(); i++)
        {
            addLineToMesh(i);
        }
    }

    splitLines(unsplitCollisionMesh); // split lines and add to collisionMesh
}

void CollisionObject::addMeshToQuadtree(Quadtree& quadtree)
{
    for (Line& l : collisionMesh)
    {
        quadtree.insert(&l);
    }
}

std::unordered_map<CollisionObject*, std::vector<glm::vec2>> CollisionObject::getCollisions(Quadtree& quadtree)
{
    std::unordered_map<CollisionObject*, std::vector<glm::vec2>> collisions;
    glm::vec2 collisionPoint;

    // for each line
    for (Line& line : collisionMesh)
    {
        // get nearby lines from quadtree
        std::vector<Line*> nearbyLines = quadtree.retrieve(&line);

        // test each nearby line for collision
        for (Line* nearbyLine : nearbyLines)
        {
            if (checkLineLineCollision(line, *nearbyLine, collisionPoint))
            {
                collisions[nearbyLine->parent].push_back(collisionPoint);
            }
        }
    }

    return collisions;
}

void CollisionObject::addLineToMesh(int i)
{
    unsigned int i1 = i;
    unsigned int i2 = (i + 1) % worldVertices.size();

    // create new line and add to vector
    unsplitCollisionMesh.emplace_back(worldVertices[i1], worldVertices[i2], this);
}

// add interpolated motion lines for each vertex (to prevent high speed objects going through each other)
void CollisionObject::addMotionLineToMesh(glm::vec2 vertex, Transform& transform)
{
    unsplitCollisionMesh.emplace_back(vertex, vertex - glm::vec2(transform.velocity), this);
}

void CollisionObject::splitLines(const std::vector<Line>& unsplitLines)
{
    for (const Line& line : unsplitLines)
    {
        splitLineX(line);
    }
}

void CollisionObject::splitLineX(const Line& inputLine)
{
    Line line(inputLine);

    if (line.p1.x > config::SCR_WIDTH)
    {
        line.p1.x -= config::SCR_WIDTH;
        line.p2.x -= config::SCR_WIDTH;
    }
    else if (line.p1.x < 0)
    {
        line.p1.x += config::SCR_WIDTH;
        line.p2.x += config::SCR_WIDTH;
    }
    
    // TODO: remove duplication
    if (line.p2.x > config::SCR_WIDTH)
    {
        glm::vec2 intersectPoint = getX(line, config::SCR_WIDTH);

        Line line2(intersectPoint, line.p2, line.parent);
        line.p2 = intersectPoint;

        line2.p1.x -= config::SCR_WIDTH;
        line2.p2.x -= config::SCR_WIDTH;

        splitLineY(line);
        splitLineY(line2);
    }
    else if (line.p2.x < 0)
    {
        glm::vec2 intersectPoint = getX(line, 0);

        Line line2(intersectPoint, line.p2, line.parent);
        line.p2 = intersectPoint;

        line2.p1.x += config::SCR_WIDTH;
        line2.p2.x += config::SCR_WIDTH;

        splitLineY(line);
        splitLineY(line2);
    }
    else
    {
        splitLineY(line);
    }
}

// TODO: somehow remove duplication?
void CollisionObject::splitLineY(const Line& inputLine)
{
    Line line(inputLine);

    if (line.p1.y > config::SCR_HEIGHT)
    {
        line.p1.y -= config::SCR_HEIGHT;
        line.p2.y -= config::SCR_HEIGHT;
    }
    else if (line.p1.y < 0)
    {
        line.p1.y += config::SCR_HEIGHT;
        line.p2.y += config::SCR_HEIGHT;
    }

    // TODO: remove duplication
    if (line.p2.y > config::SCR_HEIGHT)
    {
        glm::vec2 intersectPoint = getY(line, config::SCR_HEIGHT);

        Line line2(intersectPoint, line.p2, line.parent);
        line.p2 = intersectPoint;

        line2.p1.y -= config::SCR_HEIGHT;
        line2.p2.y -= config::SCR_HEIGHT;

        collisionMesh.push_back(line);
        collisionMesh.push_back(line2);
    }
    else if (line.p2.y < 0)
    {
        glm::vec2 intersectPoint = getY(line, 0);

        Line line2(intersectPoint, line.p2, line.parent);
        line.p2 = intersectPoint;

        line2.p1.y += config::SCR_HEIGHT;
        line2.p2.y += config::SCR_HEIGHT;

        collisionMesh.push_back(line);
        collisionMesh.push_back(line2);
    }
    else
    {
        collisionMesh.push_back(line);
    }
}

glm::vec2 CollisionObject::getX(const Line& line, const float x)
{
    glm::vec2 s = line.p1;
    glm::vec2 d = line.p2 - line.p1;

    // N.B. d.x == 0 should be impossible, since (from splitLineX which calls this function):
    // it is impossible for (p1.x >= 0 && p2.x < 0) && p1.x == p2.x
    // and same reasoning for SCR_WIDTH

    float y = s.y + ((x - s.x) / d.x) * d.y;

    return glm::vec2(x, y);
}

glm::vec2 CollisionObject::getY(const Line& line, const float y)
{
    glm::vec2 s = line.p1;
    glm::vec2 d = line.p2 - line.p1;

    float x = s.x + ((y - s.y) / d.y) * d.x;

    return glm::vec2(x, y);
}

bool CollisionObject::checkLineLineCollision(Line& a, Line& b, glm::vec2& inCollisionPoint)
{
    glm::vec2& a1 = a.p1;
    glm::vec2& a2 = a.p2;
    glm::vec2& b1 = b.p1;
    glm::vec2& b2 = b.p2;

    // check if either line is of length zero
    if ((a1.x == a2.x && a1.y == a2.y) || (b1.x == b2.x && b1.y == b2.y))
    {
        return false;
    }

    float denominator = (((b2.y - b1.y) * (a2.x - a1.x)) - ((b2.x - b1.x) * (a2.y - a1.y)));
    if (denominator == 0)
    {
        return false;
    }

    float ma = (((b2.x - b1.x) * (a1.y - b1.y)) - ((b2.y - b1.y) * (a1.x - b1.x))) / denominator;
    float mb = (((a2.x - a1.x) * (a1.y - b1.y)) - ((a2.y - a1.y) * (a1.x - b1.x))) / denominator;

    inCollisionPoint = a1 + ((a2 - a1) * ma);

    return ((ma < 1) && (ma >= 0)) && ((mb < 1) && (mb >= 0));
}
