#include "Quadtree.h"
#include "Config.h"
#include <cstdlib>
#include <iostream>


// N.B. a quadtree this size doesn't quite fit objects at the very edge of the virtual 3x3 screen.
// Such objects will be added incorrectly into the quadtree nodes on the very edge,
// but this shouldn't matter as they shouldn't ever be used for collision detection,
// unless you have an object the length of a screen edge.
// If this becomes a problem, simply increase the quadtree bounds

Quadtree::Quadtree() :
    Quadtree(1, iRectangle(-config::SCR_WIDTH, -config::SCR_HEIGHT, config::SCR_WIDTH * 2, config::SCR_HEIGHT * 2))
{
}

Quadtree::Quadtree(int level, iRectangle bounds) :
    level(level),
    bounds(bounds),
    boundsCentre((bounds.bl + bounds.tr) / 2),
    subtreesEmpty(true),
    debugVertices{
        glm::vec3(0, 0, 0),
        glm::vec3(0, bounds.tr.y - bounds.bl.y, 0),
        glm::vec3(bounds.tr.x - bounds.bl.x, bounds.tr.y - bounds.bl.y, 0),
        glm::vec3(bounds.tr.x - bounds.bl.x, 0, 0)
    },
    debugBox(glm::vec3(bounds.bl.x, bounds.bl.y, 0), 0, debugVertices, glm::vec3(1.0f, 0.5f, 0.0f))
{
    if (level < MAX_LEVELS)
    {
        subtrees[bottomLeft] = new Quadtree(level + 1, iRectangle(bounds.bl, boundsCentre));
        subtrees[bottomRight] = new Quadtree(level + 1, iRectangle(boundsCentre.x, bounds.bl.y, bounds.tr.x, boundsCentre.y));
        subtrees[topLeft] = new Quadtree(level + 1, iRectangle(bounds.bl.x, boundsCentre.y, boundsCentre.x, bounds.tr.y));
        subtrees[topRight]  = new Quadtree(level + 1, iRectangle(boundsCentre, bounds.tr));
    }
}

Quadtree::~Quadtree()
{
    if (level < MAX_LEVELS)
    {
        for (Quadtree* subtree : subtrees)
        {
            subtree->clear();
        }
    }
}

void Quadtree::clear()
{
    //std::cerr << "Clearing level: " << level << ", no. objects: " << objects.size() << std::endl;

    if (objects.size())
    {
        objects.clear();
    }
    
    // N.B. if level = MAX_LEVELS then subtreesEmpty = true
    if (!subtreesEmpty) 
    {
        // at least one of the subtrees of this node contains objects

        // below for debugging
        if (level == MAX_LEVELS)
        {
            std::cerr << "Deepest quadtree node has children. Something broke :(" << std::endl;
            return;
        }
        
        for (Quadtree* subtree : subtrees)
        {
            subtree->clear();
        }

        subtreesEmpty = true;
    }
}

void Quadtree::insert(Line line)
{
    if (subtreesEmpty)
    {
        // if need to split
        if (objects.size() >= MAX_OBJECTS && level < MAX_LEVELS)
        {
            split();
            Quadtree* target = getSubtree(line);
            target->insert(line);
        }
        else
        {
            objects.push_back(line);
        }
    }
    else
    {
        Quadtree* target = getSubtree(line);
        if (target == this)
        {
            objects.push_back(line);
        }
        else
        {
            target->insert(line);
        }
    }
}

std::vector<Line> Quadtree::retrieve(Line line)
{
    Quadtree* target = getSubtree(line);

    if (target == this)
    {
        std::vector<Line> objectList;
        objectList.insert(std::end(objectList), std::begin(objects), std::end(objects));

        if (!subtreesEmpty) // && level < MAX_LEVELS implied
        {
            for (Quadtree* subtree : subtrees)
            {
                retrieveAll(objectList);
            }
        }

        return objectList;
    }
    else
    {
        return target->retrieve(line);
    }
}

// helper function for retrieve()
void Quadtree::retrieveAll(std::vector<Line>& objectList)
{
    if (objects.size())
    {
        objectList.insert(std::end(objectList), std::begin(objects), std::end(objects));

        if (!subtreesEmpty && level < MAX_LEVELS)
        {
            for (Quadtree* subtree : subtrees)
            {
                subtree->retrieveAll(objectList);
            }
        }
    }
}

Quadtree* Quadtree::getSubtree(Line line)
{
    // if already deepest tree level, the node cannot be split
    if (level >= MAX_LEVELS)
    {
        // below for debugging
        if (level > MAX_LEVELS)
        {
            std::cerr << "Somehow created quadtree node deeper than maximum allowed depth. Something broke :(" << std::endl;
        }
        return this;
    }
    else // find which quadrant line belongs in
    {
        Quadrant p1Quadrant = getQuadrant(line.p1);
        Quadrant p2Quadrant = getQuadrant(line.p2);
        if (p1Quadrant == p2Quadrant)
        {
            return subtrees[p1Quadrant];
        }
        else
        {
            return this;
        }
    }
}

void Quadtree::split()
{
    subtreesEmpty = false;

    for (Line line : objects)
    {
        Quadtree* target = getSubtree(line);
        
        if (target != this)
        {
            target->insert(line);
        }
    }
}

// TODO: optimise by bitshifting uints
Quadtree::Quadrant Quadtree::getQuadrant(glm::vec2 point)
{
    bool topHalf = point.y > boundsCentre.y;
    bool rightHalf = point.x > boundsCentre.x;

    if (topHalf && rightHalf)
    {
        return topRight;
    }
    else if (topHalf && !rightHalf)
    {
        return topLeft;
    }
    else if (!topHalf && rightHalf)
    {
        return bottomRight;
    }
    else
    {
        return bottomLeft;
    }
}

void Quadtree::getBoxes(std::vector<RenderObject*>& boxList)
{
    //if () // TODO: don't add to list if empty, and stop recursing
    if (objects.size())
    {
        boxList.push_back(&debugBox);

        if (!subtreesEmpty) // && level < MAX_LEVELS implied
        {
            for (Quadtree* subtree : subtrees)
            {
                subtree->getBoxes(boxList);
            }
        }
    }
}
