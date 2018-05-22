#include "DebugLine.h"
#include <iostream>


DebugLine::DebugLine()
{
    // Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

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

DebugLine::~DebugLine()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &instanceVBO);
}

void DebugLine::draw(glm::vec2 p1, glm::vec2 p2, glm::vec3 color)
{
    VBOtemp.clear();
    VBOtemp.push_back(glm::vec3(p1, 0.0f));
    VBOtemp.push_back(color);
    VBOtemp.push_back(glm::vec3(p2, 0.0f));
    VBOtemp.push_back(color);

    // Upload data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), VBOtemp.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(InstanceVAs), &instance, GL_DYNAMIC_DRAW);

    // draw
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_LOOP, 0, 2);

    // unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
