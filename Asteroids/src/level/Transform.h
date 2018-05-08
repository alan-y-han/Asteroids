#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>


class Transform
{
public:
    Transform(glm::vec3 position, float angle);
    Transform(glm::vec3 position, float angle, glm::vec3 velocity, float aVelocity);

    void applyVelocities();
    glm::mat4 getModelMatrix(int x, int y);


    glm::vec3 position;
    float angle;

    glm::vec3 velocity;
    float aVelocity;

private:
    bool needsNewMatrix;
    glm::mat4 modelMatrix;
};
