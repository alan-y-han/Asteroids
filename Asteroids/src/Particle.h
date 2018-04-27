#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <vector>

#include "Config.h"
#include "GameObject.h"
#include "EventManager.h"


class Particle : public GameObject
{
public:
    Particle
    (
        TickEventManager& tickEventManager,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity
    );
    ~Particle();

private:
    void tickFunction();
};
