#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <functional>
#include <memory>
#include <unordered_set>

#include "Asteroid.h"
#include "Config.h"
#include "GameObject.h"
#include "Ship.h"
#include "Particle.h"


class LevelManager
{
public:
    std::unordered_set<GameObject*> gameObjects;
    
    LevelManager();
    void initialiseLevel();
    void processInput(GLFWwindow* window);
    void tick();

private:
    std::function<void(GameObject* gameObject)> addGOFunc;
    std::function<void(GameObject* gameObject)> removeGOFunc;

    std::vector<GameObject*> GOsToAdd;
    std::vector<GameObject*> GOsToRemove;

    Ship* playerShip;

    void addGameObject(GameObject* gameObject);
    void addGameObjects();
    void removeGameObject(GameObject* gameObject);
    void removeGameObjects();
    void createAsteroid();
};
