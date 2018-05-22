#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "Config.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "Transform.h"


class Particle : public GameObject
{
public:
    Particle(LevelManager& levelManager, Transform& transform, int lifetime);
    ~Particle();


private:
    virtual void initialise();
    virtual void move();


    const int lifetime;
    int lifetimeRemaining;
};
