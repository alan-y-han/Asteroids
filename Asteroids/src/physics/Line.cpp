#include "Line.h"

Line::Line(glm::vec2 & p1, glm::vec2 & p2) :
    Line(p1, p2, NULL)
{
}

Line::Line(glm::vec2& p1, glm::vec2& p2, CollisionObject* parent) :
    p1(p1),
    p2(p2),
    parent(parent)
{
}
