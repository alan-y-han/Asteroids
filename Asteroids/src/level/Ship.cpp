#include "Ship.h"
#include "Models.h"
#include "GPUobjectManager.h"

// TODO: clean up

float shipRandFloat(float min, float max)
{
    float range = max - min;
    return min + (((float)rand() / RAND_MAX) * range);
}


Ship::Ship(LevelManager& levelManager, Transform& transform) :
    GameObject(levelManager, levelManager.gpuObjectManager.ship, transform)
{
}

Ship::~Ship()
{
    levelManager.playerShip = NULL;
}

void Ship::initialise()
{
    levelManager.playerShip = this;

    accel = 0.1f;
    frictionFactor = 0.995f;
    rSpeed = 3.0f;
    laserCooldown = 7;
    laserCooldownTimer = 0;
}

void Ship::move()
{
    // check inputs and modify velocities

    // N.B. state is modified in the order defined below
    // i.e. velocity depends on angle
    // but angle (AD) is processed after velocity (WS)
    if (keymap.accel)
    {
        transform.velocity.x -= sin(glm::radians(transform.angle)) * accel; // TODO: fix reversed sin/cos due to vertex coords
        transform.velocity.y += cos(glm::radians(transform.angle)) * accel;
    }
    if (keymap.decel)
    {
        transform.velocity.x += sin(glm::radians(transform.angle)) * accel;
        transform.velocity.y -= cos(glm::radians(transform.angle)) * accel;
    }
    if (keymap.left)
    {
        transform.angle += rSpeed;
    }
    if (keymap.right)
    {
        transform.angle -= rSpeed;
    }

    // movement
    transform.velocity *= frictionFactor;
    transform.applyVelocities();

    updateInstanceVAsModelMatrix();

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
        particlePos = rotate2D(0 + shipRandFloat(-5, 5), -25 - shipRandFloat(0, 6), transform.angle);
        float dvx_abs = 2.0f;
        float dvy_abs = 5.0f;
        dvx = shipRandFloat(-dvx_abs, dvx_abs);
        dvy = shipRandFloat(-dvy_abs, dvy_abs) - 15.0f;
    }
    else
    {
        particlePos = rotate2D(0 + shipRandFloat(-3.0f, 3.0f), -25 + shipRandFloat(0, 2), transform.angle);
        float dvx_abs = 1.0f;
        dvx = shipRandFloat(-dvx_abs, dvx_abs);
        dvy = -shipRandFloat(0.5f, 1.0f);
    }

    glm::vec3 particleVelRand = rotate2D(dvx, dvy, transform.angle);
    
    levelManager.addGameObject(new Particle
    (
        levelManager,
        Transform(
            transform.position + particlePos,
            shipRandFloat(0, 360),
            transform.velocity + particleVelRand,
            shipRandFloat(-4, 4)
        )
    ));
}

void Ship::fireLaser()
{
    glm::vec3 laserPos = rotate2D(0, 45, transform.angle);
    glm::vec3 laserVel = rotate2D(0, 1, transform.angle);

    levelManager.addGameObject(new Laser
    (
        levelManager,
        Transform(
            transform.position + laserPos,
            transform.angle,
            transform.velocity + laserVel,
            0
        )
    ));
}
