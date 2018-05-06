#pragma once
#include <glm\gtc\type_ptr.hpp>


// forward declarations
class CollisionObject;

struct Line
{
    glm::vec2 p1;
    glm::vec2 p2;
    CollisionObject* parent;
};