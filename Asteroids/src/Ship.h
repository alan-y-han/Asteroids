#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <vector>

#include "RenderObject.h"
#include "EventManager.h"


class Ship
{
public:
    RenderObject ro;

    Ship
    (
        TickEventManager& tickEventManager,
        KeyEventManager& keyEventManager,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity
    );

private:
    void tickFunction();
    void keyFunction(int keycode);
};
