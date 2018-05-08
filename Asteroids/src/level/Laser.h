#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "CollisionObject.h"
#include "Config.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "RenderObject.h"


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


    //RenderObject renderObject;

    int lifetimeRemaining;
    CollisionObject collisionObject;
};
