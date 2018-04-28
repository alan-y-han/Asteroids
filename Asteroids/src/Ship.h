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
        EventManager<GLFWwindow*>& keyEventManager,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity,
        std::function<void(GameObject* gameObject)>& addGOFunc,
        std::function<void(GameObject* gameObject)>& removeGOFunc
    );
    ~Ship();

private:
    EventManager<GLFWwindow*>& keyEventManager;
    std::function<void(GameObject* gameObject)>& addGOFunc;
    std::function<void()> tickFunc;
    std::function<void(GLFWwindow*)> keyFunc;

    virtual void initialise();
    void tickFunction();
    void keyFunction(GLFWwindow* window);

    void generateEngineParticle();
};
