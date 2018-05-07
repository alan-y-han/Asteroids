#pragma once
#include <glm\gtc\type_ptr.hpp>

#include "CollisionObject.h"
#include "Line.h"
#include "Rectangle.h"

// debug
#include "RenderObject.h"


class Quadtree
{
public:
    Quadtree();
    ~Quadtree();

    void clear();
    void insert(Line line);
    std::vector<Line> retrieve(Line line);


    // debug
    void getBoxes(std::vector<RenderObject*>& boxList);


private:
    enum Quadrant
    {
        topRight,
        topLeft,
        bottomLeft,
        bottomRight
    };
    static const int MAX_LEVELS = 6;
    static const int MAX_OBJECTS = 3;


    Quadtree(int level, iRectangle bounds);

    Quadtree* getSubtree(Line line);
    void split();
    Quadrant getQuadrant(glm::vec2 point);
    void retrieveAll(std::vector<Line>& objectList);


    int level;
    iRectangle bounds;
    const glm::ivec2 boundsCentre;
    std::vector<Line> objects; // contains objects in the current node and all subtrees
    bool subtreesEmpty; // N.B. also indicates whether the node has split into subtrees
    Quadtree* subtrees[4];


    // debug

    std::vector<glm::vec3> debugVertices;
    RenderObject debugBox;
};
