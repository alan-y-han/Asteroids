#include "Particle.h"

// TODO: clean up
std::vector<glm::vec3> particleVertices =
{
    glm::vec3(3.0f, 3.0f, 0.0f),
    glm::vec3(-3.0f, 3.0f, 0.0f),
    glm::vec3(-3.0f, -3.0f, 0.0f),
    glm::vec3(3.0f, -3.0f, 0.0f)
};

glm::vec3 particleColor(1.0f, 0.5f, 0.0f);


Particle::Particle
(
    std::function<void(GameObject* gameObject)>& removeGOFunc,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity
) :
    GameObject(removeGOFunc, position, velocity, angle, rVelocity, particleVertices, particleColor),
    lifetime(10),
    lifetimeRemaining(lifetime)
{
}

Particle::~Particle()
{
}

void Particle::tickFunction()
{
    lifetimeRemaining--;
    alpha = static_cast<float>(lifetimeRemaining) / static_cast<float>(lifetime);
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
