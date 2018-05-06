#include "Rectangle.h"


Rectangle::Rectangle(glm::ivec2 bottomLeft, glm::ivec2 topRight) :
    bl(bottomLeft),
    tr(topRight)
{
}
;
Rectangle::Rectangle(int bottomLeftX, int bottomLeftY, int topRightX, int topRightY) :
    bl(glm::ivec2(bottomLeftX, bottomLeftY)),
    tr(glm::ivec2(topRightX, topRightY))
{
}
