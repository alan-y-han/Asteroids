#include "Laser.h"

// TODO: clean up
std::vector<glm::vec3> laserVertices =
{
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 15.0f, 0.0f)
};

glm::vec3 laserColor(0.3f, 0.8f, 1.0f);


Laser::Laser(
    TickEventManager& tickEventManager,
    std::function<void(GameObject*gameObject)>& removeGOFunc,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity
):
    GameObject(tickEventManager, removeGOFunc, position, velocity, angle, rVelocity, laserVertices, laserColor),
    tickFunc(std::bind(&Laser::tickFunction, this)),
    lifetimeRemaining(120)
{
}

Laser::~Laser()
{
    tickEventManager.unsubscribe(&tickFunc);
}

void Laser::initialise()
{
    tickEventManager.subscribe(&tickFunc);
}

void Laser::tickFunction()
{
    lifetimeRemaining--;
    if (lifetimeRemaining < 0)
    {
        removeGOFunc(this);
    }

    position += velocity;
    angle += rVelocity;

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
}
