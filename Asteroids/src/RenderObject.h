#pragma once

#include <glad\glad.h>

#include <vector>


class RenderObject
{
public:
    unsigned int VAO;
    RenderObject(std::vector<float> vertexData, std::vector<float> color) :
        vertexData(vertexData),
        color(color)
    {
        // assemble vertex buffer array from vertexData and color
        //float

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexData.size(), vertexData.data(), GL_STATIC_DRAW);
    }
private:
    unsigned int VBO;
    std::vector<float> vertexData;
    std::vector<float> color;
};
