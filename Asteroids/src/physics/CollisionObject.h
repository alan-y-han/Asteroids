#pragma once

#include <glm\gtc\type_ptr.hpp>

#include <vector>

#include "Line.h"


// forward declarations
class Quadtree;

// Collision mesh of lines is regenerated every frame, and then stuffed into a quadtree
class CollisionObject
{
public:
    CollisionObject();

    void generateMesh(const std::vector<glm::vec3>& vertices, glm::vec3& position, float angle, Quadtree& quadtree);
    //bool testObjectCollision(CollisionObject& a);


private:
    //bool testLineCollision(Line& a, Line& b);
    void addToMesh(int x, int y, int i, std::vector<glm::vec3>& transformed);


    std::vector<Line> collisionMesh;
};
