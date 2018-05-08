#include "Asteroid.h"
#include "Models.h"
#include "GPUobjectManager.h"


Asteroid::Asteroid(LevelManager& levelManager, Transform& transform) :
    GameObject(levelManager, levelManager.gpuObjectManager.asteroid, transform)
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
    transform.applyVelocities();
    updateInstanceVAsModelMatrix();
}
