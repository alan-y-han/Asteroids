#include "Particle.h"

std::vector<float> particle =
{
    0.05f, 0.05f, 0.0f,
    -0.05f, 0.05f, 0.0f,
    -0.05f, -0.05f, 0.0f,
    0.05f, -0.05f, 0.0f
};

glm::vec3 color(1.0f, 0.5f, 0.0f);


Particle::Particle
(
    TickEventManager& tickEvent,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity
) :
    ro(position, velocity, angle, rVelocity, particle, color)
{
    std::function<void()> tickFunc = std::bind(&Particle::tickFunction, this);
    tickEvent.subscribe(tickFunc);
}

Particle::~Particle()
{
    //tickEventManager.unsubscribe()
}

void Particle::tickFunction()
{
    ro.position += ro.velocity;
    ro.angle += ro.rVelocity;
}
