#pragma once
#include <glm\glm.hpp>

#include <vector>

#include "CollisionObject.h"
#include "Line.h"
#include "Rectangle.h"

// debug
#include "GPUobject.h"
#include "RenderObject.h"


class Quadtree
{
public:
    Quadtree(iRectangle bounds);
    Quadtree(iRectangle bounds, unsigned int maxLevels, unsigned int maxObjectsPerLevel);
    ~Quadtree();

    void clear();
    void insert(Line* line);
    std::vector<Line*> retrieve(Line* line);
    std::vector<Line*> retrieveAll();

    // debug
    void draw();


private:
    enum Quadrant
    {
        topRight = 0,
        topLeft = 1,
        bottomLeft = 2,
        bottomRight = 3
    };
    const unsigned int MAX_LEVELS;
    const unsigned int MAX_OBJECTS;


    Quadtree(int level, iRectangle bounds, unsigned int maxLevels, unsigned int maxObjectsPerLevel);

    Quadtree* getSubtree(Line* line);
    void split();
    Quadrant getQuadrant(glm::vec2 point);

    void retrieveHelper(Line* line, std::vector<Line*>& retrievedObjects);
    void retrieveAllHelper(std::vector<Line*>& allObjects);


    int level;
    iRectangle bounds;
    const glm::ivec2 boundsCentre;
    std::vector<Line*> objects; // contains objects in the current node and all subtrees
    bool subtreesEmpty; // N.B. also indicates whether the node has split into subtrees
    Quadtree* subtrees[4];


    // debug

    std::vector<glm::vec2> debugVertices;
    GPUobject gpuDebugBox;
    RenderObject renderObject;
};
