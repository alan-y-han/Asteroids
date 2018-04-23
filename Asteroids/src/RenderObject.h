#pragma once

#include <glad\glad.h>

#include <cstdlib>
#include <iostream>
#include <vector>


class RenderObject
{
public:
    unsigned int VAO;
    RenderObject(std::vector<float> vertices, std::vector<float> color);
private:
    unsigned int VBO;
    std::vector<float> vertices;
    std::vector<float> color;
};
