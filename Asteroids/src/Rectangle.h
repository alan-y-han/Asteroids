#pragma once
#include <glm\gtc\type_ptr.hpp>


// int rectangle
class Rectangle
{
public:
    Rectangle(glm::ivec2 bottomLeft, glm::ivec2 topRight);
    Rectangle(int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);

    glm::ivec2 bl; // bottom left
    glm::ivec2 tr; // top right
};
