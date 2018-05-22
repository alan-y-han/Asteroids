#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "CollisionObject.h"
#include "Config.h"
#include "GameObject.h"
#include "GPUobject.h"
#include "LevelManager.h"
#include "Transform.h"


class Asteroid : public GameObject
{
public:
    Asteroid(LevelManager& levelManager, Transform& transform);
    ~Asteroid();

    virtual void initialise();
    virtual void move();
    virtual void collisionCheck();


private:
    void generateHitParticle(glm::vec2 hitPosition, glm::vec2 velocity);


    CollisionObject collisionObject;
};
