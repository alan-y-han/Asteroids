#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <vector>

#include "RenderObject.h"
#include "EventManager.h"


class Particle
{
public:
    RenderObject ro;

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
