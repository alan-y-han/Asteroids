#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <functional>
#include <vector>

#include "Config.h"
#include "GameObject.h"
#include "EventManager.h"


class Particle : public GameObject
{
public:
    Particle
    (
        TickEventManager& tickEventManager,
        std::function<void(GameObject* gameObject)>& removeGOFunc,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity
    );
    ~Particle();

private:
    std::function<void()> tickFunc;
    int lifetime;

    virtual void initialise();
    void tickFunction();
};
