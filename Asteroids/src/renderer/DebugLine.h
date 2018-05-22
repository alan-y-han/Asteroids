#pragma once

#include <glad\glad.h>
#include <glm/glm.hpp>

#include <vector>
#include <unordered_set>

#include "InstanceVertexAttributes.h"


// Hacky simple class which just draws lines for debugging
class DebugLine
{
public:
    DebugLine();
    ~DebugLine();

    void draw(glm::vec2 p1, glm::vec2 p2, glm::vec3 color);


    unsigned int VAO;


private:
    unsigned int VBO;
    unsigned int instanceVBO;

    InstanceVAs instance;
    std::vector<glm::vec3> VBOtemp;
};
