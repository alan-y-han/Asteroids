#pragma once

#include <glm\gtc\type_ptr.hpp>

#include <vector>

#include "Line.h"
#include "Transform.h"


// forward declarations
class Quadtree;

// Collision mesh of lines is regenerated every frame, and then stuffed into a quadtree
class CollisionObject
{
public:
    CollisionObject();

    void generateMesh(const std::vector<glm::vec3>& vertices, Transform& transform, Quadtree& quadtree);


private:
    void addLineToMesh(int x, int y, int i, std::vector<glm::vec3>& transformed);

    void addMotionLineToMesh(int x, int y, glm::vec2 vertex, Transform& transform);

    std::vector<Line> collisionMesh;
};
