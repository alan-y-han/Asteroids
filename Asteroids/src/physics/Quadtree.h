#pragma once
#include <glm\gtc\type_ptr.hpp>

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
    Quadtree();
    ~Quadtree();

    void clear();
    void insert(Line* line);
    std::vector<Line*> retrieve(Line* line);
    void retrieveAll(std::vector<Line*>& objectList);


    // debug
    void draw();

    std::vector<Line*> objs;


private:
    enum Quadrant
    {
        topRight = 0,
        topLeft = 1,
        bottomLeft = 2,
        bottomRight = 3
    };
    static const int MAX_LEVELS = 6;
    static const int MAX_OBJECTS = 1;


    Quadtree(int level, iRectangle bounds);

    Quadtree* getSubtree(Line* line);
    void split();
    Quadrant getQuadrant(glm::vec2 point);


    int level;
    iRectangle bounds;
    const glm::ivec2 boundsCentre;
    std::vector<Line*> objects; // contains objects in the current node and all subtrees
    bool subtreesEmpty; // N.B. also indicates whether the node has split into subtrees
    Quadtree* subtrees[4];


    // debug

    std::vector<glm::vec3> debugVertices;
    GPUobject gpuDebugBox;
    RenderObject renderObject;
};
