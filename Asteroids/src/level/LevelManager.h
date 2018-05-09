#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <memory>
#include <unordered_set>

#include "Config.h"
#include "Quadtree.h"


// forward declarations
class GameObject;
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
    std::unordered_set<GameObject*> asteroids;

    // N.B. a quadtree this size doesn't quite fit objects at the very edge of the virtual 3x3 screen.
    // Such objects will be added incorrectly into the quadtree nodes on the very edge,
    // but this shouldn't matter as they shouldn't ever be used for collision detection,
    // unless you have an object the length of a screen edge.
    // If this becomes a problem, simply increase the quadtree bounds
    Quadtree quadtree;


private:
    // disable copying class
    LevelManager(const LevelManager&) = delete;
    LevelManager& operator=(const LevelManager&) = delete;

    void addGameObjects();
    void removeGameObjects();

    void createAsteroid();

    std::vector<GameObject*> GOsToAdd;
    std::vector<GameObject*> GOsToRemove;
};
