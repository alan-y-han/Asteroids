#pragma once

#include <glm/gtc/type_ptr.hpp>

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
    CollisionObject collisionObject;
};
