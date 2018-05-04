#include "Asteroid.h"
#include "Models.h"


Asteroid::Asteroid(
    LevelManager& levelManager,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity
) :
    GameObject(levelManager, position, velocity, angle, rVelocity, models::asteroidVertices, models::asteroidColor)
{
}

Asteroid::~Asteroid()
{
    levelManager.asteroids.erase(this);
}

void Asteroid::initialise()
{
    levelManager.asteroids.insert(this);
}

void Asteroid::move()
{
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
