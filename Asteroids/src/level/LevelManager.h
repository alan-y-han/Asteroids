#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <memory>
#include <unordered_set>

#include "Config.h"
#include "Quadtree.h"

// debug
class Asteroid;


// forward declarations
class GameObject;
class GameObjectNew;
class GPUobjectManager;
class Ship;


class LevelManager
{
public:
    LevelManager(GPUobjectManager& gpuObjectManager);
    ~LevelManager();

    void initialiseLevel();
    void processInput(GLFWwindow* window);
    void tick();

    void addGameObject(GameObject* gameObject);
    void removeGameObject(GameObject* gameObject);

    GPUobjectManager& gpuObjectManager;

    std::unordered_set<GameObject*> gameObjects;
    Ship* playerShip;
    std::unordered_set<GameObject*> lasers;
    std::unordered_set<GameObjectNew*> asteroids;

    Quadtree quadtree;


private:
    // disable copying class
    LevelManager(const LevelManager&) = delete;
    LevelManager& operator=(const LevelManager&) = delete;

    void addGameObjects();
    void removeGameObjects();

    void createAsteroid();

    Asteroid* testAsteroid;

    std::vector<GameObject*> GOsToAdd;
    std::vector<GameObject*> GOsToRemove;
};
