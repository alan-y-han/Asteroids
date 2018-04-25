#include "Ship.h"

std::vector<float> ship =
{
    0.0f, 0.5f, 0.0f,
    -0.25f, -0.5f, 0.0f,
    0.0f, -0.25f, 0.0f,
    0.25f, -0.5f, 0.0f
};

glm::vec3 color(1.0f, 0.0f, 0.5f);


Ship::Ship(
    TickEventManager& tickEvent,
    KeyEventManager& keyEventManager,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity
) :
    ro(position, velocity, angle, rVelocity, ship, color)
{
    std::function<void()> tickFunc = std::bind(&Ship::tickFunction, this);
    tickEvent.subscribe(tickFunc);

    std::function<void(int)> keyFunc = std::bind(&Ship::keyFunction, this, std::placeholders::_1);
    keyEventManager.subscribe(keyFunc);
}

void Ship::tickFunction()
{
    ro.position += ro.velocity;
    ro.angle += ro.rVelocity;
    //std::cout << ro.velocity.x << ", " << ro.velocity.y << ", " << ro.velocity.z << std::endl;
}

float speed = 0.001f;

void Ship::keyFunction(int keycode)
{
    switch (keycode)
    {
    case GLFW_KEY_W:
        ro.velocity.x -= sin(glm::radians(ro.angle)) * speed;
        ro.velocity.y += cos(glm::radians(ro.angle)) * speed;
        break;
    case GLFW_KEY_S:
        ro.velocity.x += sin(glm::radians(ro.angle)) * speed;
        ro.velocity.y -= cos(glm::radians(ro.angle)) * speed;
        break;
    case GLFW_KEY_A:
        ro.angle += 4.0f;
        break;
    case GLFW_KEY_D:
        ro.angle -= 4.0f;
        break;
    default:
        break;
    }
}
