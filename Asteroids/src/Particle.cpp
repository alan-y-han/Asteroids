#include "Particle.h"

std::vector<float> particleVertices =
{
    0.05f, 0.05f, 0.0f,
    -0.05f, 0.05f, 0.0f,
    -0.05f, -0.05f, 0.0f,
    0.05f, -0.05f, 0.0f
};

glm::vec3 particleColor(1.0f, 0.5f, 0.0f);


Particle::Particle
(
    TickEventManager& tickEvent,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity
) :
    GameObject(position, velocity, angle, rVelocity, particleVertices, particleColor)
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
    position += velocity;
    angle += rVelocity;
}
