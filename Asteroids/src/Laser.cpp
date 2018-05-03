#include "Laser.h"

#include "LevelManager.h"

// TODO: clean up
std::vector<glm::vec3> laserVertices =
{
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 15.0f, 0.0f)
};

glm::vec3 laserColor(0.3f, 0.8f, 1.0f);


Laser::Laser(
    LevelManager& levelManager,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity
):
    GameObject(levelManager, position, velocity, angle, rVelocity, laserVertices, laserColor),
    lifetimeRemaining(120)
{
}

Laser::~Laser()
{
    levelManager.lasers.erase(this);
}

void Laser::initialise()
{
    levelManager.lasers.insert(this);
}

void Laser::tickFunction()
{
    lifetimeRemaining--;
    if (lifetimeRemaining < 0)
    {
        levelManager.removeGameObject(this);
    }

    // movement

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
