#include "LevelManager.h"

#include "Models.h"

float randFloat(float min, float max)
{
    float range = max - min;
    return min + (((float)rand() / RAND_MAX) * range);
}

LevelManager::LevelManager(Renderer& renderer) :
    renderer(renderer),
    ship(tickEventManager, keyEventManager, glm::vec3(4.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f)
{
}

void LevelManager::initialiseLevel()
{
    renderer.registerRO(&ship.ro);

    int noParticles = 0;

    while (noParticles < 10000)
    {
        particles[noParticles] = new Particle
        (
            tickEventManager,
            glm::vec3(randFloat(0, 8), randFloat(0, 8), 0),
            glm::vec3(randFloat(-0.008f, 0.008f), randFloat(-0.008f, 0.008f), 0),
            randFloat(0, 360),
            randFloat(-4, 4)
        );

        RenderObject* lastParticleRO = &(particles[noParticles]->ro);
        renderer.registerRO(lastParticleRO);

        noParticles++;
        //std::cout << noParticles << std::endl;
    }
}


void LevelManager::tick()
{
    tickEventManager.trigger();

    
}
