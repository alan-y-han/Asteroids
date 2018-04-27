#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <functional>
#include <vector>

#include "Config.h"
#include "GameObject.h"
#include "EventManager.h"
#include "Particle.h"


class Ship : public GameObject
{
public:
    Ship
    (
        TickEventManager& tickEventManager,
        KeyEventManager& keyEventManager,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity,
        std::function<void(GameObject* gameObject)> addGOFunc
    );

private:
    void tickFunction();
    void keyFunction(int keycode);
    std::function<void(GameObject* gameObject)> addGOFunc;

    void generateEngineParticle();
};
