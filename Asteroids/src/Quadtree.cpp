#include "Quadtree.h"
#include "Config.h"
#include <cstdlib>
#include <iostream>


Quadtree::Quadtree() :
    Quadtree(1, iRectangle(0, 0, config::SCR_WIDTH, config::SCR_HEIGHT))
{
}

Quadtree::Quadtree(int level, iRectangle bounds) :
    level(level),
    bounds(bounds),
    boundsCentre((bounds.bl + bounds.tr) / 2),
    subtreesEmpty(true)
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
    objects.push_back(line);

    // if the node is over max capacity to remain a leaf node
    if (objects.size() > MAX_OBJECTS)
    {
        Quadtree* target = getSubtree(line);

        // if object just added caused node to go over capacity
        if (subtreesEmpty)
        {
            split();
        } // else the node has already split in the past, therefore add object to subtree
        else if (target != this)
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
        return objects;
    }
    else
    {
        return target->retrieve(line);
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

void Quadtree::split()
{
    subtreesEmpty = false;

    for (Line* line : objects)
    {
        Quadtree* target = getSubtree(line);
        
        if (target != this)
        {
            target->insert(line);
        }
    }
}

// TODO: optimise by bitshifting ints
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
