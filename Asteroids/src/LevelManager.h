#pragma once

#include <functional>
#include <memory>
#include <unordered_set>

#include "Config.h"
#include "EventManager.h"
#include "GameObject.h"
#include "Ship.h"
#include "Particle.h"


class LevelManager
{
public:
    KeyEventManager keyEventManager;
    std::unordered_set<GameObject*> gameObjects;
    
    LevelManager();
    void initialiseLevel();
    void processInput(GLFWwindow* window);
    void tick();

private:
    TickEventManager tickEventManager;
    std::function<void(GameObject* gameObject)> addGOFunc;
    std::function<void(GameObject* gameObject)> removeGOFunc;
    std::vector<GameObject*> removalList;

    void addGameObject(GameObject* gameObject);
    void removeGameObject(GameObject* gameObject);
};
