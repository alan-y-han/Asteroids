#include "Particle.h"
#include "GPUobjectManager.h"
#include "Models.h"

Particle::Particle(LevelManager& levelManager, Transform& transform) :
    GameObject(levelManager, levelManager.gpuObjectManager.particle, transform),
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

    for (RenderObject& ro : renderObjects)
    {
        ro.instanceVAs.alpha = static_cast<float>(lifetimeRemaining) / static_cast<float>(lifetime);
    }

    if (lifetimeRemaining < 0)
    {
        levelManager.removeGameObject(this);
    }

    transform.applyVelocities();
    
    updateInstanceVAsModelMatrix();
}
