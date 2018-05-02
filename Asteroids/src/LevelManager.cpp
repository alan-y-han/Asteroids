#include "LevelManager.h"


LevelManager::LevelManager() :
    addGOFunc(std::bind(&LevelManager::addGameObject, this, std::placeholders::_1)),
    removeGOFunc(std::bind(&LevelManager::removeGameObject, this, std::placeholders::_1))
{
}

void LevelManager::initialiseLevel()
{
    addGameObject(new Ship(
        tickEventManager,
        keyEventManager,
        glm::vec3(config::SCR_WIDTH / 2, config::SCR_HEIGHT / 2, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        0.0f,
        0.0f,
        addGOFunc,
        removeGOFunc
    ));
    createAsteroid();

    addGameObjects();
}

void LevelManager::processInput(GLFWwindow* window)
{
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    keyEventManager.trigger(window);
}

void LevelManager::tick()
{
    // tell each GameObject to update its state
    tickEventManager.trigger();

    removeGameObjects();

    addGameObjects();
}

void LevelManager::addGameObject(GameObject* gameObject)
{
    GOsToAdd.push_back(gameObject);
}

void LevelManager::addGameObjects()
{
    if (GOsToAdd.size())
    {
        for (GameObject* go : GOsToAdd)
        {
            gameObjects.insert(go);
            go->initialise();
        }
        GOsToAdd.clear();
    }
}

void LevelManager::removeGameObject(GameObject * gameObject)
{
    GOsToRemove.push_back(gameObject);
}

void LevelManager::removeGameObjects()
{
    if (GOsToRemove.size())
    {
        for (GameObject* go : GOsToRemove)
        {
            gameObjects.erase(go);
            delete go;
        }
        GOsToRemove.clear();
    }
}

void LevelManager::createAsteroid()
{
    addGameObject(new Asteroid(
        tickEventManager,
        removeGOFunc,
        glm::vec3(100, 100, 0),
        glm::vec3(2, -0.5, 0),
        20,
        -2
    ));
}
