#include "Ship.h"

// TODO: clean up

std::vector<glm::vec3> shipVertices =
{
    glm::vec3(0.0f, 50.0f, 0.0f),
    glm::vec3(-25.0f, -30.0f, 0.0f),
    glm::vec3(0.0f, -15.0f, 0.0f),
    glm::vec3(25.0f, -30.0f, 0.0f)
};

glm::vec3 shipColor(1.0f, 1.0f, 1.0f);

float shipRandFloat(float min, float max)
{
    float range = max - min;
    return min + (((float)rand() / RAND_MAX) * range);
}

// end TODO


Ship::Ship
(
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity,
    std::function<void(GameObject* gameObject)>& addGOFunc,
    std::function<void(GameObject* gameObject)>& removeGOFunc
) :
    GameObject(removeGOFunc, position, velocity, angle, rVelocity, shipVertices, shipColor),
    addGOFunc(addGOFunc)
{
    accel = 0.1f;
    frictionFactor = 0.995f;
    rSpeed = 3.0f;

    laserCooldown = 7;
    laserCooldownTimer = 0;
}

Ship::~Ship()
{
}

void Ship::tickFunction()
{
    // check inputs and modify velocities

    // N.B. state is modified in the order defined below
    // i.e. velocity depends on angle
    // but angle (AD) is processed after velocity (WS)
    if (keymap.accel)
    {
        velocity.x -= sin(glm::radians(angle)) * accel; // TODO: fix reversed sin/cos due to vertex coords
        velocity.y += cos(glm::radians(angle)) * accel;
    }
    if (keymap.decel)
    {
        velocity.x += sin(glm::radians(angle)) * accel;
        velocity.y -= cos(glm::radians(angle)) * accel;
    }
    if (keymap.left)
    {
        angle += rSpeed;
    }
    if (keymap.right)
    {
        angle -= rSpeed;
    }

    // movement

    position += velocity;
    angle += rVelocity;

    velocity *= frictionFactor;

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

    // other object state

    if (laserCooldownTimer > 0)
    {
        laserCooldownTimer--;
    }

    // spawn new objects

    // N.B. new GameObjects depend on ship position/velocity
    // therefore only spawn after these have been calculated

    if (keymap.accel)
    {
        generateEngineParticle(true);
        generateEngineParticle(true);
        generateEngineParticle(true);
    }
    else
    {
        //generateEngineParticle(false);
        //generateEngineParticle(false);
    }
    if (keymap.fireLaser)
    {
        if (laserCooldownTimer == 0)
        {
            fireLaser();
            laserCooldownTimer += laserCooldown;
        }
    }
}

glm::vec3 Ship::rotate2D(float x, float y, float angle)
{
    float dx = cos(glm::radians(angle)) * x - sin(glm::radians(angle)) * y;
    float dy = sin(glm::radians(angle)) * x + cos(glm::radians(angle)) * y;
    return glm::vec3(dx, dy, 0.0f);
}

void Ship::generateEngineParticle(bool accel)
{
    glm::vec3 particlePos;
    float dvx = 0.0f;
    float dvy = 0.0f;

    if (accel)
    {
        particlePos = rotate2D(0 + shipRandFloat(-5, 5), -25 - shipRandFloat(0, 6), angle);
        float dvx_abs = 2.0f;
        float dvy_abs = 5.0f;
        dvx = shipRandFloat(-dvx_abs, dvx_abs);
        dvy = shipRandFloat(-dvy_abs, dvy_abs) - 15.0f;
    }
    else
    {
        particlePos = rotate2D(0 + shipRandFloat(-3.0f, 3.0f), -25 + shipRandFloat(0, 2), angle);
        float dvx_abs = 1.0f;
        dvx = shipRandFloat(-dvx_abs, dvx_abs);
        dvy = -shipRandFloat(0.5f, 1.0f);
    }

    glm::vec3 particleVelRand = rotate2D(dvx, dvy, angle);
    
    addGOFunc(new Particle
    (
        removeGOFunc,
        position + particlePos,
        velocity + particleVelRand,
        shipRandFloat(0, 360),
        shipRandFloat(-4, 4)
    ));
}

void Ship::fireLaser()
{
    glm::vec3 laserPos = rotate2D(0, 45, angle);
    glm::vec3 laserVel = rotate2D(0, 12, angle);

    addGOFunc(new Laser
    (
        removeGOFunc,
        position + laserPos,
        velocity + laserVel,
        angle,
        0
    ));
}
