#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Config.h"
#include "GameObject.h"
#include "LevelManager.h"


class Asteroid : public GameObject
{
public:
    Asteroid(
        LevelManager& levelManager,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity
    );
    ~Asteroid();


private:
    virtual void initialise();
    virtual void move();
};
