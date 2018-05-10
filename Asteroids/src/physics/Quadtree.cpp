#include "Quadtree.h"
#include "Config.h"
#include <cstdlib>
#include <iostream>


Quadtree::Quadtree(iRectangle bounds) :
    Quadtree(1, bounds)
{
}

Quadtree::Quadtree(int level, iRectangle bounds) :
    level(level),
    bounds(bounds),
    boundsCentre((bounds.bl + bounds.tr) / 2),
    subtreesEmpty(true),
    // debug
    debugVertices{
        glm::vec3(0, 0, 0),
        glm::vec3(0, bounds.tr.y - bounds.bl.y, 0),
        glm::vec3(bounds.tr.x - bounds.bl.x, bounds.tr.y - bounds.bl.y, 0),
        glm::vec3(bounds.tr.x - bounds.bl.x, 0, 0)
    },
    gpuDebugBox(debugVertices, glm::vec3(1.0f, 0.5f, 0.0f)),
    renderObject(&gpuDebugBox)
{
    if (level < MAX_LEVELS)
    {
        subtrees[bottomLeft] = new Quadtree(level + 1, iRectangle(bounds.bl, boundsCentre));
        subtrees[bottomRight] = new Quadtree(level + 1, iRectangle(boundsCentre.x, bounds.bl.y, bounds.tr.x, boundsCentre.y));
        subtrees[topLeft] = new Quadtree(level + 1, iRectangle(bounds.bl.x, boundsCentre.y, boundsCentre.x, bounds.tr.y));
        subtrees[topRight]  = new Quadtree(level + 1, iRectangle(boundsCentre, bounds.tr));
    }

    // debug
    glm::mat4& modelMatrix = renderObject.instanceVAs.modelMatrix;
    modelMatrix[3][0] = bounds.bl.x;
    modelMatrix[3][1] = bounds.bl.y;
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

void Quadtree::insert(Line* line)
{
    if (subtreesEmpty)
    {
        // if need to split
        if ((objects.size() >= MAX_OBJECTS) && (level < MAX_LEVELS))
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

std::vector<Line*> Quadtree::retrieve(Line* line)
{
    Quadtree* target = getSubtree(line);

    if (target == this)
    {
        std::vector<Line*> objectList;

        retrieveAll(objectList);

        return objectList;
    }
    else
    {
        return target->retrieve(line);
    }
}

void Quadtree::retrieveAll(std::vector<Line*>& objectList)
{
    objectList.insert(std::end(objectList), std::begin(objects), std::end(objects));

    if (!subtreesEmpty) // && level < MAX_LEVELS implied
    {
        for (Quadtree* subtree : subtrees)
        {
            subtree->retrieveAll(objectList);
        }
    }
}

Quadtree* Quadtree::getSubtree(Line* line)
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
        Quadrant p1Quadrant = getQuadrant(line->p1);
        Quadrant p2Quadrant = getQuadrant(line->p2);
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

// TODO: optimise by removing tempObjects (faster to erase from existing vector than calling malloc again)
void Quadtree::split()
{
    subtreesEmpty = false;
    std::vector<Line*> tempObjects(objects);
    objects.clear();

    for (Line* line : tempObjects)
    {
        Quadtree* target = getSubtree(line);
        
        if (target != this)
        {
            target->insert(line);
        }
        else
        {
            objects.push_back(line);
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

// debug functions

void Quadtree::draw()
{
    if (objects.size() || !subtreesEmpty)
    {
        gpuDebugBox.draw();
    }

    if (!subtreesEmpty) // && level < MAX_LEVELS implied
    {
        for (Quadtree* subtree : subtrees)
        {
            subtree->draw();
        }
    }
}
