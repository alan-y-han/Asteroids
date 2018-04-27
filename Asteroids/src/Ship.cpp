#include "Ship.h"


std::vector<float> shipVertices =
{
    0.0f, 40.0f, 0.0f,
    -25.0f, -40.0f, 0.0f,
    0.0f, -25.0f, 0.0f,
    25.0f, -40.0f, 0.0f
};

glm::vec3 shipColor(1.0f, 0.0f, 0.5f);


Ship::Ship
(
    TickEventManager& tickEventManager,
    KeyEventManager& keyEventManager,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity,
    std::function<void(GameObject* gameObject)> addGOFunc
) :
    tickEventManager(tickEventManager),
    GameObject(position, velocity, angle, rVelocity, shipVertices, shipColor),
    addGOFunc(addGOFunc)
{
    std::function<void()> tickFunc = std::bind(&Ship::tickFunction, this);
    tickEventManager.subscribe(tickFunc);

    std::function<void(int)> keyFunc = std::bind(&Ship::keyFunction, this, std::placeholders::_1);
    keyEventManager.subscribe(keyFunc);
}

void Ship::tickFunction()
{
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


// TODO: clean up
float speed = 0.1f;

float shipRandFloat(float min, float max)
{
    float range = max - min;
    return min + (((float)rand() / RAND_MAX) * range);
}

glm::vec3 rotate2D(float x, float y, float angle)
{
    float dx = cos(glm::radians(angle)) * x - sin(glm::radians(angle)) * y;
    float dy = sin(glm::radians(angle)) * x + cos(glm::radians(angle)) * y;
    return glm::vec3(dx, dy, 0.0f);
}

void Ship::keyFunction(int keycode)
{
    glm::vec3 particlePos = rotate2D(0 + shipRandFloat(-5, 5), -30, angle);

    float dvx_abs = 1.0f;
    float dvy_abs = 2.0f;
    float dvx = shipRandFloat(-dvx_abs, dvx_abs);
    float dvy = shipRandFloat(-dvy_abs, dvy_abs) - 5.0f;

    glm::vec3 particleVelRand = rotate2D(dvx, dvy, angle);

    switch (keycode)
    {
    case GLFW_KEY_W:
        velocity.x -= sin(glm::radians(angle)) * speed;
        velocity.y += cos(glm::radians(angle)) * speed;

        

        addGOFunc(new Particle
        (
            tickEventManager,
            position + particlePos,
            velocity + particleVelRand,
            shipRandFloat(0, 360),
            shipRandFloat(-4, 4)
        ));
        break;
    case GLFW_KEY_S:
        velocity.x += sin(glm::radians(angle)) * speed;
        velocity.y -= cos(glm::radians(angle)) * speed;
        break;
    case GLFW_KEY_A:
        angle += 4.0f;
        break;
    case GLFW_KEY_D:
        angle -= 4.0f;
        break;
    default:
        break;
    }
}
