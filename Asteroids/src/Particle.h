#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Config.h"
#include "GameObject.h"


class LevelManager;

class Particle : public GameObject
{
public:
    Particle
    (
        LevelManager& levelManager,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity
    );
    ~Particle();

private:
    const int lifetime;
    int lifetimeRemaining;

    virtual void initialise();
    virtual void tickFunction();
};
