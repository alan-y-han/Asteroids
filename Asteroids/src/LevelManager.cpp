#include "LevelManager.h"

#include "Models.h"

float randFloat(float min, float max)
{
    float range = max - min;
    return min + (((float)rand() / RAND_MAX) * range);
}

LevelManager::LevelManager()
{
}

void LevelManager::initialiseLevel()
{

    //ship(tickEventManager, keyEventManager, glm::vec3(4.0f, 3.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f)

    int noParticles = 0;

    while (noParticles < 7000)
    {
        gameObjects.emplace(new Particle
        (
            tickEventManager,
            glm::vec3(randFloat(0, 8), randFloat(0, 8), 0),
            glm::vec3(randFloat(-0.008f, 0.008f), randFloat(-0.008f, 0.008f), 0),
            randFloat(0, 360),
            randFloat(-4, 4)
        ));

        noParticles++;
    }
}


void LevelManager::tick()
{
    tickEventManager.trigger();
}
