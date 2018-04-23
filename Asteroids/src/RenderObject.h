#pragma once

#include <glad\glad.h>

#include <cstdlib>
#include <iostream>
#include <vector>


class RenderObject
{
public:
    unsigned int VAO;
    RenderObject(std::vector<float> vertices, std::vector<float> color) :
        vertices(vertices),
        color(color)
    {
        // assemble vertex buffer array from vertexData and color

        if (vertices.size() % 3 != 0)
        {
            std::cerr << "Warning: non-integer number of 3D vertices passed to RenderObject" << std::endl;
        }

        int vertexDataSize = vertices.size() * 2;

        float* vertexData = (float*)malloc(vertexDataSize * sizeof(float)); // X, Y, Z, R, G, B
        if (vertexData == NULL)
        {
            std::cerr << "malloc failed" << std::endl;
        }

        for (int i = 0; i < vertices.size(); i += 3)
        {
            vertexData[0 + (i * 2)] = vertices[0 + i];
            vertexData[1 + (i * 2)] = vertices[1 + i];
            vertexData[2 + (i * 2)] = vertices[2 + i];
            vertexData[3 + (i * 2)] = color[0];
            vertexData[4 + (i * 2)] = color[1];
            vertexData[5 + (i * 2)] = color[2];
        }

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexDataSize * sizeof(float), vertexData, GL_STATIC_DRAW);
        free(vertexData);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
private:
    unsigned int VBO;
    std::vector<float> vertices;
    std::vector<float> color;
};
