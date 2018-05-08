#include "GPUobject.h"
#include <iostream>


GPUobject::GPUobject(std::vector<glm::vec3> vertices, glm::vec3 color) :
    noOfVertices(vertices.size())
{
    // Assemble vertex data and color
    int vertexDataSize = vertices.size() * 3 * 2; // 6 floats per vertex

    float* vertexData = (float*)malloc(vertexDataSize * sizeof(float)); // X, Y, Z, R, G, B
    if (vertexData == NULL)
    {
        std::cerr << "malloc failed in GPUobject class" << std::endl;
    }

    for (int i = 0; i < vertices.size(); i++)
    {
        vertexData[(i * 6) + 0] = vertices[i].x;
        vertexData[(i * 6) + 1] = vertices[i].y;
        vertexData[(i * 6) + 2] = vertices[i].z;
        vertexData[(i * 6) + 3] = color.r;
        vertexData[(i * 6) + 4] = color.g;
        vertexData[(i * 6) + 5] = color.b;
    }

    // Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Upload data
    glBufferData(GL_ARRAY_BUFFER, vertexDataSize * sizeof(float), vertexData, GL_STATIC_DRAW);
    free(vertexData);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Setup instancing (N.B. instance data is uploaded in draw())
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

    // alpha attribute (instanced)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(InstanceVAs), (void*)(offsetof(struct InstanceVAs, alpha)));
    glVertexAttribDivisor(2, 1);
    // model matrix attribute (instanced) (N.B. using offsetof() in case of struct padding)
    GLsizei vec4Size = sizeof(glm::vec4);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceVAs), (void*)(offsetof(struct InstanceVAs, modelMatrix)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceVAs), (void*)(offsetof(struct InstanceVAs, modelMatrix) + vec4Size));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceVAs), (void*)(offsetof(struct InstanceVAs, modelMatrix) + (2 * vec4Size)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceVAs), (void*)(offsetof(struct InstanceVAs, modelMatrix) + (3 * vec4Size)));
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    // unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

GPUobject::~GPUobject()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &instanceVBO);
}

void GPUobject::addInstance(InstanceVAs* renderObject)
{
    instances.insert(renderObject);
}

void GPUobject::removeInstance(InstanceVAs* renderObject)
{
    instances.erase(renderObject);
}

void GPUobject::draw()
{
    if (instances.size())
    {
        // pull all instance vertex attributes from their RenderObjects
        // and stuff them into a temporary array
        instanceVAsTemp.clear();
        for (InstanceVAs* instance : instances)
        {
            instanceVAsTemp.push_back(*instance);
        }

        // upload instance vertex attributes to GPU buffer
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(InstanceVAs) * instanceVAsTemp.size(), instanceVAsTemp.data(), GL_DYNAMIC_DRAW);    

        // call instanced draw
        glBindVertexArray(VAO);
        glDrawArraysInstanced(GL_LINE_LOOP, 0, noOfVertices, instances.size());

        // unbind buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}
