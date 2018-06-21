#include "Transform.h"
#include "Config.h"

Transform::Transform(glm::vec2 position, float angle) :
    Transform(position, angle, glm::vec2(0.0f, 0.0f), 0.0f)
{
}

Transform::Transform(glm::vec2 position, float angle, glm::vec2 velocity, float aVelocity) :
    position(position),
    angle(angle),
    velocity(velocity),
    aVelocity(aVelocity),
    needsNewMatrix(true)
{
}

void Transform::applyVelocities()
{
    position += velocity;
    angle += aVelocity;

    if (position.x > config::SCR_WIDTH)
    {
        position.x -= config::SCR_WIDTH;
    }
    else if (position.x < 0)
    {
        position.x += config::SCR_WIDTH;
    }
    if (position.y > config::SCR_HEIGHT)
    {
        position.y -= config::SCR_HEIGHT;
    }
    else if (position.y < 0)
    {
        position.y += config::SCR_HEIGHT;
    }

    needsNewMatrix = true;
}

glm::mat4 Transform::getModelMatrix(int x, int y)
{
    if (needsNewMatrix)
    {
        // update matrix with new position/rotation
        float rad = glm::radians(angle);
        modelMatrix[0][0] = cos(rad);
        modelMatrix[1][0] = -sin(rad);
        modelMatrix[0][1] = sin(rad);
        modelMatrix[1][1] = cos(rad);
        // translation
        modelMatrix[3][0] = position.x;
        modelMatrix[3][1] = position.y;
        modelMatrix[3][2] = 0.0f;

        needsNewMatrix = false;
    }

    glm::mat4 returnModel(modelMatrix);

    // translate to offset
    returnModel[3][0] += x * config::SCR_WIDTH;
    returnModel[3][1] += y * config::SCR_HEIGHT;

    return returnModel;
}

glm::mat4 Transform::getRotationMatrix()
{
    glm::mat4 rotMatrix;

    float rad = glm::radians(angle);
    rotMatrix[0][0] = cos(rad);
    rotMatrix[1][0] = -sin(rad);
    rotMatrix[0][1] = sin(rad);
    rotMatrix[1][1] = cos(rad);
    // translation
    rotMatrix[3][0] = 0.0f;
    rotMatrix[3][1] = 0.0f;
    rotMatrix[3][2] = 0.0f;

    return rotMatrix;
}