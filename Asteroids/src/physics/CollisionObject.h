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
    void addToMesh(int x, int y, int i, std::vector<glm::vec3>& transformed);


    std::vector<Line> collisionMesh;
};
