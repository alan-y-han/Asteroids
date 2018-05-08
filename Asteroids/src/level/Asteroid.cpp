#include "Asteroid.h"
#include "Models.h"
#include "GPUobjectManager.h"


Asteroid::Asteroid(
    LevelManager& levelManager,
    Transform& transform
) :
    GameObjectNew(levelManager, levelManager.gpuObjectManager.asteroid, transform)
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

    int count = 0;
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            renderObjects[count].instanceVAs.modelMatrix = transform.getModelMatrix(x, y);
            count++;
        }
    }
}
