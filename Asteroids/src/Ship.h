#pragma once

#include <vector>

#include "RenderObject.h"
#include "EventManager.h"


class Ship
{
public:
    RenderObject ro;

    Ship(TickEventManager& tickEventManager, glm::vec3 position, glm::vec3 velocity);

private:
    void tickFunction();
};
