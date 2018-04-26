#pragma once

#include <glad\glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdlib>
#include <iostream>
#include <vector>


class GameObject
{
public:
    unsigned int VAO;
    glm::vec3 position;
    glm::vec3 velocity;
    float angle;
    float rVelocity;

    GameObject
    (
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity,
        std::vector<float> vertices,
        glm::vec3 color
    );
private:
    glm::vec3 color;
    unsigned int VBO;
    std::vector<float> vertices;
};
