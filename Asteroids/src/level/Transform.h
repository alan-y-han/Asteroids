#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


class Transform
{
public:
    Transform(glm::vec2 position, float angle);
    Transform(glm::vec2 position, float angle, glm::vec2 velocity, float aVelocity);

    void applyVelocities();
    glm::mat4 getModelMatrix(int x, int y);


    glm::vec2 position;
    float angle;

    glm::vec2 velocity;
    float aVelocity;

private:
    bool needsNewMatrix;
    glm::mat4 modelMatrix;
};
