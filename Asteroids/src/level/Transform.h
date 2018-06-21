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
    glm::mat4 getRotationMatrix();


    glm::vec2 position;
    float angle;

    glm::vec2 velocity;
    float aVelocity;

    bool needsNewMatrix;
private:
    glm::mat4 modelMatrix;
};
