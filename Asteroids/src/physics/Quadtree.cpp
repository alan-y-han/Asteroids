#include "Quadtree.h"
#include "Config.h"
#include <cstdlib>
#include <iostream>


Quadtree::Quadtree(iRectangle bounds) :
    Quadtree(bounds, 6, 1)
{
}

Quadtree::Quadtree(iRectangle bounds, unsigned int maxLevels, unsigned int maxObjectsPerLevel) :
    Quadtree(1, bounds, maxLevels, maxObjectsPerLevel)
{

}

Quadtree::Quadtree(int level, iRectangle bounds, unsigned int maxLevels, unsigned int maxObjectsPerLevel) :
    MAX_LEVELS(maxLevels),
    MAX_OBJECTS(maxObjectsPerLevel),
    level(level),
    bounds(bounds),
    boundsCentre((bounds.bl + bounds.tr) / 2),
    subtreesEmpty(true),
    // debug
    debugVertices{
        glm::vec2(0, 0),
        glm::vec2(0, bounds.tr.y - bounds.bl.y),
        glm::vec2(bounds.tr.x - bounds.bl.x, bounds.tr.y - bounds.bl.y),
        glm::vec2(bounds.tr.x - bounds.bl.x, 0)
    },
    gpuDebugBox(debugVertices, glm::vec3(1.0f, 0.5f, 0.0f)),
    renderObject(&gpuDebugBox)
{
    if (level < MAX_LEVELS)
    {
        subtrees[bottomLeft] = new Quadtree(level + 1, iRectangle(bounds.bl, boundsCentre), maxLevels, maxObjectsPerLevel);
        subtrees[bottomRight] = new Quadtree(level + 1, iRectangle(boundsCentre.x, bounds.bl.y, bounds.tr.x, boundsCentre.y), maxLevels, maxObjectsPerLevel);
        subtrees[topLeft] = new Quadtree(level + 1, iRectangle(bounds.bl.x, boundsCentre.y, boundsCentre.x, bounds.tr.y), maxLevels, maxObjectsPerLevel);
        subtrees[topRight]  = new Quadtree(level + 1, iRectangle(boundsCentre, bounds.tr), maxLevels, maxObjectsPerLevel);
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
    std::vector<Line*> objectList;
    retrieveHelper(line, objectList);
    return objectList;
}

void Quadtree::retrieveHelper(Line* line, std::vector<Line*>& retrievedObjects)
{
    retrievedObjects.insert(std::end(retrievedObjects), std::begin(objects), std::end(objects));

    if (!subtreesEmpty)
    {
        Quadtree* target = getSubtree(line);

        if (target == this)
        {
            for (Quadtree* subtree : subtrees)
            {
                subtree->retrieveAllHelper(retrievedObjects);
            }
        }
        else
        {
            target->retrieveHelper(line, retrievedObjects);
        }

    }

    //Quadtree* target = getSubtree(line);

    //if (target == this) //  || subtreesEmpty
    //{
    //    if (!subtreesEmpty)
    //    {
    //        std::vector<Line*> objectList(retrieveAll());

    //        retrievedObjects.insert(std::end(retrievedObjects), std::begin(objectList), std::end(objectList));
    //    }
    //    return;
    //}
    //else
    //{
    //    target->retrieveHelper(line, retrievedObjects);
    //}
}

std::vector<Line*> Quadtree::retrieveAll()
{
    std::vector<Line*> allObjects;
    retrieveAllHelper(allObjects);
    return allObjects;
}

void Quadtree::retrieveAllHelper(std::vector<Line*>& allObjects)
{
    allObjects.insert(std::end(allObjects), std::begin(objects), std::end(objects));

    if (!subtreesEmpty) // && level < MAX_LEVELS implied
    {
        for (Quadtree* subtree : subtrees)
        {
            subtree->retrieveAllHelper(allObjects);
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
