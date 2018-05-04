#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <memory>
#include <unordered_set>

#include "Config.h"


// forward declarations
class GameObject;
class Ship;


class LevelManager
{
public:
    std::unordered_set<GameObject*> gameObjects;
    
    LevelManager();
    ~LevelManager();
    void initialiseLevel();
    void processInput(GLFWwindow* window);
    void tick();

    Ship* playerShip;
    std::unordered_set<GameObject*> lasers;
    std::unordered_set<GameObject*> asteroids;

    void addGameObject(GameObject* gameObject);
    void removeGameObject(GameObject* gameObject);

private:
    std::vector<GameObject*> GOsToAdd;
    std::vector<GameObject*> GOsToRemove;

    // disable copying to prevent LevelManager class misuse
    LevelManager(const LevelManager&) = delete;
    LevelManager& operator=(const LevelManager&) = delete;

    void addGameObjects();
    void removeGameObjects();

    void createAsteroid();
};
