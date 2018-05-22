#pragma once
#include <glm\glm.hpp>


// int rectangle class
class iRectangle
{
public:
    iRectangle(glm::ivec2 bottomLeft, glm::ivec2 topRight);
    iRectangle(int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);


    glm::ivec2 bl; // bottom left
    glm::ivec2 tr; // top right
};
