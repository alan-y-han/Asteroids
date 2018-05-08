#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Config.h"
#include "GameObject.h"
#include "LevelManager.h"


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
    virtual void initialise();
    virtual void move();


    const int lifetime;
    int lifetimeRemaining;
};
