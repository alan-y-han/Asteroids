#pragma once

#include <functional>
#include <vector>

#include "Config.h"
#include "GameObject.h"
#include "Laser.h"
#include "Particle.h"


class Ship : public GameObject
{
public:
    Ship
    (
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity,
        std::function<void(GameObject* gameObject)>& addGOFunc,
        std::function<void(GameObject* gameObject)>& removeGOFunc
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
    // constructor-related things
    std::function<void(GameObject* gameObject)>& addGOFunc;
    
    // other variables
    std::vector<glm::vec3> vertices;
    glm::vec3 color;

    float accel;
    float frictionFactor;
    float rSpeed;

    int laserCooldown;
    int laserCooldownTimer;

    // functions
    virtual void tickFunction();
    glm::vec3 rotate2D(float x, float y, float angle);
    void generateEngineParticle();
    void fireLaser();
};
