#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <functional>
#include <vector>

#include "Config.h"
#include "EventManager.h"
#include "GameObject.h"


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
    const int lifetime;
    int lifetimeRemaining;

    virtual void initialise();
    void tickFunction();
};
