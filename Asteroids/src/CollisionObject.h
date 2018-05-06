#pragma once

#include <glm\gtc\type_ptr.hpp>

#include <vector>

#include "Line.h"


class CollisionObject
{
public:
    CollisionObject(std::vector<glm::vec3>& collisionMesh);

    void move(glm::vec3 position, float rotation);
    bool testObjectCollision(CollisionObject& a);

private:
    std::vector<glm::vec3> collisionMesh;

    bool testLineCollision(Line& a, Line& b);
};
