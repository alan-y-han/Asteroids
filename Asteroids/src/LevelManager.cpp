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
}

void LevelManager::processInput(GLFWwindow * window)
{
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        keyEventManager.trigger(GLFW_KEY_W);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        keyEventManager.trigger(GLFW_KEY_S);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        keyEventManager.trigger(GLFW_KEY_A);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        keyEventManager.trigger(GLFW_KEY_D);
    }
}

void LevelManager::tick()
{
    tickEventManager.trigger();

    if (removalList.size())
    {
        for (GameObject* go : removalList)
        {
            gameObjects.erase(go);
            delete go;
        }
        removalList.clear();
    }
}

void LevelManager::addGameObject(GameObject* gameObject)
{
    gameObjects.insert(gameObject);
}

void LevelManager::removeGameObject(GameObject * gameObject)
{
    removalList.push_back(gameObject);
}
