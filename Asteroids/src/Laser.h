#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Config.h"
#include "GameObject.h"
#include "LevelManager.h"


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
    virtual void initialise();
    virtual void move();
    virtual void collisionCheck();


    int lifetimeRemaining;
    CollisionObject collisionObject;
};
