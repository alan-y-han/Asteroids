#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <functional>
#include <vector>

#include "Config.h"
#include "EventManager.h"
#include "GameObject.h"


class Asteroid : public GameObject
{
public:
    Asteroid(
        TickEventManager& tickEventManager,
        std::function<void(GameObject* gameObject)>& removeGOFunc,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity
    );
    ~Asteroid();

private:
    std::function<void()> tickFunc;

    virtual void initialise();
    void tickFunction();
};
