#include "Ship.h"

std::vector<float> shipVertices =
{
    0.0f, 0.5f, 0.0f,
    -0.25f, -0.5f, 0.0f,
    0.0f, -0.25f, 0.0f,
    0.25f, -0.5f, 0.0f
};

glm::vec3 shipColor(1.0f, 0.0f, 0.5f);


Ship::Ship
(
    TickEventManager& tickEvent,
    KeyEventManager& keyEventManager,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity
) :
    GameObject(position, velocity, angle, rVelocity, shipVertices, shipColor)
{
    std::function<void()> tickFunc = std::bind(&Ship::tickFunction, this);
    tickEvent.subscribe(tickFunc);

    std::function<void(int)> keyFunc = std::bind(&Ship::keyFunction, this, std::placeholders::_1);
    keyEventManager.subscribe(keyFunc);
}

void Ship::tickFunction()
{
    position += velocity;
    angle += rVelocity;
}

float speed = 0.001f;

void Ship::keyFunction(int keycode)
{
    switch (keycode)
    {
    case GLFW_KEY_W:
        velocity.x -= sin(glm::radians(angle)) * speed;
        velocity.y += cos(glm::radians(angle)) * speed;
        break;
    case GLFW_KEY_S:
        velocity.x += sin(glm::radians(angle)) * speed;
        velocity.y -= cos(glm::radians(angle)) * speed;
        break;
    case GLFW_KEY_A:
        angle += 4.0f;
        break;
    case GLFW_KEY_D:
        angle -= 4.0f;
        break;
    default:
        break;
    }
}
