#include "Ship.h"

// TODO: clean up
float speed = 0.1f;

std::vector<glm::vec3> shipVertices =
{
    glm::vec3(0.0f, 50.0f, 0.0f),
    glm::vec3(-25.0f, -30.0f, 0.0f),
    glm::vec3(0.0f, -15.0f, 0.0f),
    glm::vec3(25.0f, -30.0f, 0.0f)
};

glm::vec3 shipColor(1.0f, 0.0f, 0.5f);

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

// end TODO


Ship::Ship
(
    TickEventManager& tickEventManager,
    EventManager<GLFWwindow*>& keyEventManager,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity,
    std::function<void(GameObject* gameObject)>& addGOFunc,
    std::function<void(GameObject* gameObject)>& removeGOFunc
) :
    GameObject(tickEventManager, removeGOFunc, position, velocity, angle, rVelocity, shipVertices, shipColor),
    keyEventManager(keyEventManager),
    tickFunc(std::bind(&Ship::tickFunction, this)),
    keyFunc(std::bind(&Ship::keyFunction, this, std::placeholders::_1)),
    addGOFunc(addGOFunc)
{
}

Ship::~Ship()
{
    tickEventManager.unsubscribe(&tickFunc);
    keyEventManager.unsubscribe(&keyFunc);
}

void Ship::initialise()
{
    tickEventManager.subscribe(&tickFunc);
    keyEventManager.subscribe(&keyFunc);
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

void Ship::keyFunction(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        velocity.x -= sin(glm::radians(angle)) * speed;
        velocity.y += cos(glm::radians(angle)) * speed;
        generateEngineParticle();
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        velocity.x += sin(glm::radians(angle)) * speed;
        velocity.y -= cos(glm::radians(angle)) * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        angle += 3.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        angle -= 3.0f;
    }
}

void Ship::generateEngineParticle()
{
    glm::vec3 particlePos = rotate2D(0 + shipRandFloat(-5, 5), -20, angle);

    float dvx_abs = 0.8f;
    float dvy_abs = 2.0f;
    float dvx = shipRandFloat(-dvx_abs, dvx_abs);
    float dvy = shipRandFloat(-dvy_abs, dvy_abs) - 5.0f;

    glm::vec3 particleVelRand = rotate2D(dvx, dvy, angle);
    
    addGOFunc(new Particle
    (
        tickEventManager,
        removeGOFunc,
        position + particlePos,
        velocity + particleVelRand,
        shipRandFloat(0, 360),
        shipRandFloat(-4, 4)
    ));
}
