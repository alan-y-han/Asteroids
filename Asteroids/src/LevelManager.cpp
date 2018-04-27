#include "LevelManager.h"


LevelManager::LevelManager()
{
}

void LevelManager::initialiseLevel()
{
    std::function<void(GameObject* gameObject)> addGOFunc = std::bind(&LevelManager::addGameObject, this, std::placeholders::_1);

    addGameObject(new Ship(
        tickEventManager,
        keyEventManager,
        glm::vec3(config::SCR_WIDTH / 2, config::SCR_HEIGHT / 2, 1.0f),
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
