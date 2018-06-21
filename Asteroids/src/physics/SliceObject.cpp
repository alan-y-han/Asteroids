#include "SliceObject.h"
#include "Quadtree.h"

// debug
#include <iostream>

SliceObject::SliceObject(std::vector<glm::vec2>& vertices)
{
    // debug
    if (vertices.size() < 3)
    {
        std::cerr << "SliceObject: warning <3 vertices supplied" << std::endl;
        return;
    }
    // end debug

    for (int i = 0; i < vertices.size(); i++)
    {
        collisionMesh.emplace_back(vertices[i], vertices[(i + 1) % vertices.size()]);
    }
}

//SliceObject::SliceObject(std::vector<glm::vec2>& vertices, Transform& transform)
//{
//    // debug
//    if (vertices.size() < 3)
//    {
//        std::cerr << "SliceObject: warning <3 vertices supplied" << std::endl;
//        return;
//    }
//    // end debug
//
//
//    std::vector<glm::vec2> worldVertices;
//
//    glm::mat4 model = transform.getModelMatrix(0, 0);
//    for (const glm::vec2& v : vertices)
//    {
//        worldVertices.push_back(model * glm::vec4(v, 0.0f, 1.0f)); // TODO: maybe use emplace_back
//    }
//
//    for (int i = 0; i < vertices.size(); i++)
//    {
//        collisionMesh.emplace_back(worldVertices[i], worldVertices[(i + 1) % vertices.size()]);
//    }
//}

void SliceObject::addMeshToQuadtree(Quadtree & quadtree)
{
    for (Line& l : collisionMesh)
    {
        quadtree.insert(&l);
    }
}

// TODO: try and remove duplication
std::unordered_map<Line*, std::vector<std::pair<glm::vec2, Line*>>> SliceObject::getCollisions(Quadtree& quadtree)
{
    std::unordered_map<Line*, std::vector<std::pair<glm::vec2, Line*>>> collisions;


    //std::vector<glm::vec2> collisions;
    glm::vec2 collisionPoint;

    for (Line& line : collisionMesh)
    {
        std::vector<Line*> asteroidLines = quadtree.retrieve(&line);

        for (Line* asteroidLine : asteroidLines)
        {
            if (checkLineLineCollision(line, *asteroidLine, collisionPoint))
            {
                collisions[&line].emplace_back(collisionPoint, asteroidLine);
            }
        }
    }

    return collisions;
}

// TODO: remove duplication
bool SliceObject::checkLineLineCollision(Line& a, Line& b, glm::vec2& inCollisionPoint)
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
