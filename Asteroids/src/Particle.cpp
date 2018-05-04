#include "Particle.h"
#include "Models.h"

Particle::Particle
(
    LevelManager& levelManager,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity
) :
    GameObject(levelManager, position, velocity, angle, rVelocity, models::particleVertices, models::particleColor),
    lifetime(10),
    lifetimeRemaining(lifetime)
{
}

Particle::~Particle()
{
}

void Particle::initialise()
{
}

void Particle::move()
{
    lifetimeRemaining--;
    alpha = static_cast<float>(lifetimeRemaining) / static_cast<float>(lifetime);
    if (lifetimeRemaining < 0)
    {
        levelManager.removeGameObject(this);
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
