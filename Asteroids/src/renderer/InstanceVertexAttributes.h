#pragma once
#include <glm/gtc/type_ptr.hpp>


// stores vertex attributes pertaining to a particular instance of GPUobject
// N.B. beware of padding
struct InstanceVAs
{
    glm::mat4 modelMatrix;
    float alpha = 1.0f;
};
