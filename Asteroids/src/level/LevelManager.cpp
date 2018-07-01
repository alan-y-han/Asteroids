#include "LevelManager.h"

#include "Asteroid.h"
#include "GameObject.h"
#include "Models.h"
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
            glm::vec2(config::SCR_WIDTH / 2 + 200, config::SCR_HEIGHT / 2),
            180.0f,
            glm::vec2(0.0f, 0.0f),
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
    GOsToAdd.insert(gameObject);
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

//// N.B. this allows removing the same object twice
//// this is ok because the object removal queue is a set (which enforces uniqueness)
//// TODO: this is kinda hacky, maybe stop doing this?
void LevelManager::removeGameObject(GameObject* gameObject)
{
    GOsToRemove.insert(gameObject);
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
            glm::vec2(config::SCR_WIDTH / 2, config::SCR_HEIGHT / 2),
            0,
            glm::vec2(0, 0),
            0.3f
        ),
        models::testCubeVertices
    ));
}
