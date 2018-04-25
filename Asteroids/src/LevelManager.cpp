#include "LevelManager.h"

#include "Models.h"

LevelManager::LevelManager(Renderer& renderer) :
    renderer(renderer),
    ship(tickEventManager, keyEventManager, glm::vec3(4.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f))
{
}

void LevelManager::initialiseLevel()
{
    renderer.registerRO(&ship.ro);
}

void LevelManager::tick()
{
    tickEventManager.trigger();
}
