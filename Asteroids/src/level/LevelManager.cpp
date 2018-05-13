#include "LevelManager.h"

#include "Asteroid.h"
#include "GameObject.h"
#include "Ship.h"
#include "Transform.h"


LevelManager::LevelManager(GPUobjectManager& gpuObjectManager) :
    gpuObjectManager(gpuObjectManager),
    laserQuadtree(iRectangle(0, 0, config::SCR_WIDTH, config::SCR_HEIGHT)),
    asteroidQuadtree(iRectangle(0, 0, config::SCR_WIDTH, config::SCR_HEIGHT))
{
}

LevelManager::~LevelManager()
{
    for (GameObject* go : gameObjects)
    {
        removeGameObject(go);
    }
    removeGameObjects();
}

void LevelManager::initialiseLevel()
{
    playerShip = new Ship(
        *this,
        Transform(
            //glm::vec3(config::SCR_WIDTH / 2, config::SCR_HEIGHT / 2, 1.0f),
            //glm::vec3(115, 115 / 2, 1.0f), // causes problems 1
            glm::vec3(115, 57, 1.0f), // causes problems 2
            //126.8f,// causes problems 1
            117.8f,
            glm::vec3(0.0f, 0.0f, 0.0f),
            0.0f
        )
    );
    addGameObject(playerShip);
    
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

    playerShip->keymap.accel = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS);
    playerShip->keymap.decel = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS);
    playerShip->keymap.left = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS);
    playerShip->keymap.right = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS);
    playerShip->keymap.fireLaser = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
}

void LevelManager::tick()
{
    // calculate movement
    laserQuadtree.clear();
    asteroidQuadtree.clear();

    for (GameObject* go : gameObjects)
    {
        go->move();
    }

    // calculate physics (i.e. collisions)
    for (GameObject* go : gameObjects)
    {
        go->collisionCheck();
    }

    // add/remove gameobjects
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

void LevelManager::removeGameObject(GameObject* gameObject)
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
        *this,
        Transform(
            glm::vec3(100, 100, 0),
            //20,
            0,
            //glm::vec3(2, -0.5, 0),
            glm::vec3(0, 0, 0),
            -2
        )
    ));
}
