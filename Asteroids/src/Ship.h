#pragma once

#include <functional>
#include <vector>

#include "Config.h"
#include "GameObject.h"
#include "Laser.h"
#include "LevelManager.h"
#include "Particle.h"


class Ship : public GameObject
{
public:
    Ship
    (
        LevelManager& levelManager,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity
    );
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


    std::vector<glm::vec3> vertices;
    glm::vec3 color;

    float accel;
    float frictionFactor;
    float rSpeed;
    int laserCooldown;
    int laserCooldownTimer;
};
