#include "Asteroid.h"

// TODO: clean up
std::vector<glm::vec3> asteroidVertices =
{
    glm::vec3(0, 20, 0),
    glm::vec3(-20, 40, 0),
    glm::vec3(-40, 20, 0),
    glm::vec3(-40, -20, 0),
    glm::vec3(-20, -40, 0),
    glm::vec3(20, -40, 0),
    glm::vec3(40, -20, 0),
    glm::vec3(20, 0, 0),
    glm::vec3(40, 20, 0),
    glm::vec3(20, 40, 0)
};

glm::vec3 asteroidColor(1.0f, 1.0f, 0.0f);


Asteroid::Asteroid(
    std::function<void(GameObject* gameObject)>& removeGOFunc,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity
) :
    GameObject(removeGOFunc, position, velocity, angle, rVelocity, asteroidVertices, asteroidColor)
{
}

Asteroid::~Asteroid()
{
}

void Asteroid::tickFunction()
{
    // movement
    position += velocity;
    angle += rVelocity;

    if (position.x > config::SCR_WIDTH)
    {
        position.x -= config::SCR_WIDTH;
    }
    else if (position.x < 0)
    {
        position.x += config::SCR_WIDTH;
    }
    if (position.y > config::SCR_HEIGHT)
    {
        position.y -= config::SCR_HEIGHT;
    }
    else if (position.y < 0)
    {
        position.y += config::SCR_HEIGHT;
    }
}
