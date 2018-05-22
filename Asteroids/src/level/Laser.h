#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "CollisionObject.h"
#include "Config.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "RenderObject.h"
#include "Transform.h"


class Laser : public GameObject
{
public:
    Laser(LevelManager& levelManager, Transform& transform);
    ~Laser();


private:
    virtual void initialise();
    virtual void move();
    virtual void collisionCheck();
    void hit(CollisionObject* collisionObject, glm::vec2 point);


    CollisionObject collisionObject;

    int lifetimeRemaining;
};
