#pragma once

#include <functional>
#include <vector>
#include <utility>

#include "CollisionObject.h"
#include "Config.h"
#include "GameObject.h"
#include "Laser.h"
#include "LevelManager.h"
#include "Particle.h"
#include "Transform.h"


class Ship : public GameObject
{
public:
    Ship(LevelManager& levelManager, Transform& transform);
    ~Ship();

    struct keymap_type
    {
        bool accel = false;
        bool decel = false;
        bool left = false;
        bool right = false;
        bool fireLaser = false;
    } keymap;


private:
    virtual void initialise();
    virtual void move();
    virtual void collisionCheck();

    // time - time in seconds to reach ~63% of max velocity
    // maxV - maximum velocity
    std::pair<float, float> calcVelAndFriction(float time, float maxV);
    glm::vec2 rotate2D(float x, float y, float angle);
    void generateEngineParticle(bool accel);
    void fireLaser();


    CollisionObject collisionObject;

    float transDeltaVel;
    float transVelFriction;

    float aDeltaVel;
    float aVelFriction;

    int laserCooldown;
    int laserCooldownTimer;
};
