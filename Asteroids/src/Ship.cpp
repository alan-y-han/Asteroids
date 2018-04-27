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
    TickEventManager& tickEventManager,
    KeyEventManager& keyEventManager,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity,
    std::function<void(GameObject* gameObject)> addGOFunc
) :
    tickEventManager(tickEventManager),
    GameObject(position, velocity, angle, rVelocity, shipVertices, shipColor),
    addGOFunc(addGOFunc)
{
    std::function<void()> tickFunc = std::bind(&Ship::tickFunction, this);
    tickEventManager.subscribe(tickFunc);

    std::function<void(int)> keyFunc = std::bind(&Ship::keyFunction, this, std::placeholders::_1);
    keyEventManager.subscribe(keyFunc);
}

void Ship::tickFunction()
{
    position += velocity;
    angle += rVelocity;
    if (position.x > 8.0f)
    {
        position.x -= 8.0f;
    }
    else if (position.x < 0.0f)
    {
        position.x += 8.0f;
    }
    if (position.y > 6.0f)
    {
        position.y -= 6.0f;
    }
    else if (position.y < 0.0f)
    {
        position.y += 6.0f;
    }
}


// TODO: clean up
float speed = 0.001f;

float shipRandFloat(float min, float max)
{
    float range = max - min;
    return min + (((float)rand() / RAND_MAX) * range);
}

void Ship::keyFunction(int keycode)
{
    float dx = cos(glm::radians(angle)) * 0.0f - sin(glm::radians(angle)) * (-0.3f);
    float dy = sin(glm::radians(angle)) * 0.0f + cos(glm::radians(angle)) * (-0.3f);


    switch (keycode)
    {
    case GLFW_KEY_W:
        velocity.x -= sin(glm::radians(angle)) * speed;
        velocity.y += cos(glm::radians(angle)) * speed;

        

        addGOFunc(new Particle
        (
            tickEventManager,
            glm::vec3(position.x + dx, position.y + dy, 0.0f),
            glm::vec3(sin(glm::radians(angle)) * 0.05f + shipRandFloat(-0.005f, 0.005f), -cos(glm::radians(angle)) * 0.05f + shipRandFloat(-0.005f, 0.005f), 0.0f) + velocity,
            shipRandFloat(0, 360),
            shipRandFloat(-4, 4)
        ));
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
