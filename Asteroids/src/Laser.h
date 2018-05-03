#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Config.h"
#include "GameObject.h"


class LevelManager;

class Laser : public GameObject
{
public:
    Laser
    (
        LevelManager& levelManager,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity
    );
    ~Laser();

private:
    int lifetimeRemaining;

    virtual void initialise();
    virtual void tickFunction();
};
