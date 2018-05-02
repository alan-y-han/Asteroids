#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <functional>
#include <vector>

#include "Config.h"
#include "GameObject.h"


class Particle : public GameObject
{
public:
    Particle
    (
        std::function<void(GameObject* gameObject)>& removeGOFunc,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity
    );
    ~Particle();

private:
    const int lifetime;
    int lifetimeRemaining;

    void tickFunction();
};
