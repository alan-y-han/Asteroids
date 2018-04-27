#include "LevelManager.h"

#include "Models.h"


// TODO: clean up

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
    std::function<void(GameObject* gameObject)> addGOFunc = std::bind(&LevelManager::addGameObject, this, std::placeholders::_1);

    addGameObject(new Ship(
        tickEventManager,
        keyEventManager,
        glm::vec3(4.0f, 3.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.0f,
        0.0f,
        addGOFunc
    ));
}


void LevelManager::tick()
{
    tickEventManager.trigger();
}

void LevelManager::addGameObject(GameObject* gameObject)
{
    gameObjects.emplace(gameObject);
}
