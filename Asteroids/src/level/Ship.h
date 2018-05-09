#pragma once

#include <functional>
#include <vector>

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

    glm::vec3 rotate2D(float x, float y, float angle);
    void generateEngineParticle(bool accel);
    void fireLaser();


    glm::vec3 color;

    float accel;
    float frictionFactor;
    float rSpeed;
    int laserCooldown;
    int laserCooldownTimer;
};
