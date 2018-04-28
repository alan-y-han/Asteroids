#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <functional>
#include <vector>

#include "Config.h"
#include "EventManager.h"
#include "GameObject.h"


class Laser : public GameObject
{
public:
    Laser
    (
        TickEventManager& tickEventManager,
        std::function<void(GameObject* gameObject)>& removeGOFunc,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity
    );
    ~Laser();

private:
    int lifetimeRemaining;
    std::function<void()> tickFunc;

    virtual void initialise();
    void tickFunction();
};
