#pragma once

#include <functional>
#include <memory>
#include <unordered_set>

#include "EventManager.h"
#include "GameObject.h"
#include "Ship.h"
#include "Particle.h"


class LevelManager
{
public:
    KeyEventManager keyEventManager;
    std::unordered_set<std::unique_ptr<GameObject>> gameObjects;
    
    LevelManager();
    void initialiseLevel();
    void tick();

private:
    TickEventManager tickEventManager;

    void addGameObject(GameObject* gameObject);
};
