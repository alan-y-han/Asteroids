#pragma once
#include <glm\glm.hpp>

#include <vector>


// forward declarations
class CollisionObject;

class Line
{
public:
    Line(glm::vec2& p1, glm::vec2& p2);
    Line(glm::vec2& p1, glm::vec2& p2, CollisionObject* parent);


    glm::vec2 p1;
    glm::vec2 p2;
    CollisionObject* parent;
};
