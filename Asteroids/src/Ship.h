#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <functional>
#include <vector>

#include "Config.h"
#include "EventManager.h"
#include "GameObject.h"
#include "Laser.h"
#include "Particle.h"


class Ship : public GameObject
{
public:
    Ship
    (
        TickEventManager& tickEventManager,
        EventManager<GLFWwindow*>& keyEventManager,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity,
        std::function<void(GameObject* gameObject)>& addGOFunc,
        std::function<void(GameObject* gameObject)>& removeGOFunc
    );
    ~Ship();

private:
    // constructor-related things
    EventManager<GLFWwindow*>& keyEventManager;
    std::function<void()> tickFunc;
    std::function<void(GLFWwindow*)> keyFunc;
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
    virtual void initialise();
    void tickFunction();
    void keyFunction(GLFWwindow* window);
    glm::vec3 rotate2D(float x, float y, float angle);
    void generateEngineParticle();
    void fireLaser();
};
