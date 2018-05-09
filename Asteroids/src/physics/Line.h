#pragma once
#include <glm\gtc\type_ptr.hpp>


// forward declarations
class CollisionObject;

class Line
{
public:
    Line(glm::vec2& p1, glm::vec2& p2, CollisionObject* parent);


    glm::vec2 p1;
    glm::vec2 p2;
    CollisionObject* parent;
};
