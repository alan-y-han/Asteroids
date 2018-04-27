#include "Particle.h"

std::vector<float> particleVertices =
{
    3.0f, 3.0f, 0.0f,
    -3.0f, 3.0f, 0.0f,
    -3.0f, -3.0f, 0.0f,
    3.0f, -3.0f, 0.0f
};

glm::vec3 particleColor(1.0f, 0.5f, 0.0f);


Particle::Particle
(
    TickEventManager& tickEventManager,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity
) :
    GameObject(tickEventManager, position, velocity, angle, rVelocity, particleVertices, particleColor),
    tickFunc(std::bind(&Particle::tickFunction, this))
{
    this->tickEventManager.subscribe(&tickFunc);
}

Particle::~Particle()
{
    tickEventManager.unsubscribe(&tickFunc);
}

int life = 0;

void Particle::tickFunction()
{
    life++;
    if (life > 120)
    {
        //tickEventManager.unsubscribe(&tickFunc);
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
