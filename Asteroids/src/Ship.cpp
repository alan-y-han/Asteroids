#include "Ship.h"

std::vector<float> ship =
{
    0.0f, 0.5f, 0.0f,
    -0.25f, -0.5f, 0.0f,
    0.0f, -0.25f, 0.0f,
    0.25f, -0.5f, 0.0f
};

glm::vec3 color(1.0f, 0.0f, 0.5f);


Ship::Ship(TickEventManager& tickEvent, glm::vec3 position, glm::vec3 velocity) :
    ro(position, velocity, ship, color)
{
    std::function<void()> tickFunc = std::bind(&Ship::tickFunction, this);

    tickEvent.subscribe(tickFunc);
}

void Ship::tickFunction()
{
    ro.position += ro.velocity;
}
