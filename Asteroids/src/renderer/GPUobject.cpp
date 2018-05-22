#include "GPUobject.h"
#include <iostream>


GPUobject::GPUobject(std::vector<glm::vec2> vertices, glm::vec3 color) :
    noOfVertices(vertices.size())
{
    // Assemble vertex data and color
    std::vector<glm::vec3> VBOtemp;

    int vertexDataSize = vertices.size() * 2;
    VBOtemp.reserve(vertexDataSize);

    for (glm::vec2& vertex : vertices)
    {
        VBOtemp.push_back(glm::vec3(vertex, 0.0f));
        VBOtemp.push_back(color);
    }

    // Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Upload data
    glBufferData(GL_ARRAY_BUFFER, VBOtemp.size() * sizeof(glm::vec3), VBOtemp.data(), GL_STATIC_DRAW);

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
    // column 1
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceVAs), (void*)(offsetof(struct InstanceVAs, modelMatrix)));
    glVertexAttribDivisor(3, 1);
    // column 2
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceVAs), (void*)(offsetof(struct InstanceVAs, modelMatrix) + sizeof(glm::vec4)));
    glVertexAttribDivisor(4, 1);
    // column 3
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceVAs), (void*)(offsetof(struct InstanceVAs, modelMatrix) + (2 * sizeof(glm::vec4))));
    glVertexAttribDivisor(5, 1);
    // column 4
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceVAs), (void*)(offsetof(struct InstanceVAs, modelMatrix) + (3 * sizeof(glm::vec4))));
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

    // debug
    if (instances.size())
    {
        std::cerr << "Warning: deleting GPUobject which still has instances" << std::endl;
    }
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
