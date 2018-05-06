#pragma once

#include <glm\gtc\type_ptr.hpp>

#include <vector>

#include "Line.h"


// Collision mesh of lines is regenerated every frame, and then stuffed into a quadtree
class CollisionObject
{
public:
    CollisionObject();


    void move(glm::vec3& vertices, glm::vec3& position, float rotation);
    bool testObjectCollision(CollisionObject& a);


private:
    bool testLineCollision(Line& a, Line& b);


    std::vector<Line> collisionMesh;
};