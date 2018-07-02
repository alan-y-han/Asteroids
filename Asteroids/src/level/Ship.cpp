#include "Ship.h"
#include "Models.h"
#include "GPUobjectManager.h"
#include "RNG.h"


Ship::Ship(LevelManager& levelManager, Transform& transform) :
    GameObject(levelManager, levelManager.gpuObjectManager.ship, transform),
    collisionObject(*this)
{
}

Ship::~Ship()
{
    levelManager.playerShip = NULL;
}

void Ship::initialise()
{
    levelManager.playerShip = this;

    std::pair<float, float> transFricVel = calcVelAndFriction(1.0f, 30.0f);
    transVelFriction = transFricVel.first;
    transDeltaVel = transFricVel.second;

    std::pair<float, float> angFricVel = calcVelAndFriction(0.07f, 5.0f);
    aVelFriction = angFricVel.first;
    aDeltaVel = angFricVel.second;

    laserCooldown = 0;
    laserCooldownTimer = 0;
}

std::pair<float, float> Ship::calcVelAndFriction(float time, float vMax)
{
    float dt = config::SPF;

    float friction = 1.0f - (dt / time);

    float accel = vMax / (friction * time);
    float deltaV = accel * dt;

    return std::pair<float, float>(friction, deltaV);
}

void Ship::move()
{
    // check inputs and modify velocities

    // N.B. state is modified in the order defined below
    // i.e. velocity depends on angle
    // but angle (AD) is processed after velocity (WS)
    if (keymap.accel)
    {
        transform.velocity.x += cos(glm::radians(transform.angle)) * transDeltaVel;
        transform.velocity.y += sin(glm::radians(transform.angle)) * transDeltaVel;
    }
    if (keymap.decel)
    {
        transform.velocity.x -= cos(glm::radians(transform.angle)) * transDeltaVel;
        transform.velocity.y -= sin(glm::radians(transform.angle)) * transDeltaVel;
    }
    if (keymap.left)
    {
        transform.aVelocity += aDeltaVel;
    }
    if (keymap.right)
    {
        transform.aVelocity -= aDeltaVel;
    }

    // movement
    transform.velocity *= transVelFriction;
    transform.aVelocity *= aVelFriction;
    transform.applyVelocities();

    updateInstanceVAsModelMatrix();
    collisionObject.generateMesh(models::shipVertices, transform);

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
        for (int i = 0; i < 3; i++)
        {
            generateEngineParticle(true);
        }
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

void Ship::collisionCheck()
{
    std::unordered_map<CollisionObject*, std::vector<glm::vec2>> collisions = collisionObject.getCollisions(levelManager.asteroidQuadtree);

    for (std::pair<CollisionObject*, std::vector<glm::vec2>> objectCollisionList : collisions)
    {
        std::vector<glm::vec2>& collisionPoints = objectCollisionList.second;

        for (glm::vec2& collisionPoint : collisionPoints)
        {
            levelManager.addGameObject(new Particle
            (
                levelManager,
                Transform(
                    glm::vec2(collisionPoint),
                    0.0f,
                    glm::vec2(0.0f, 0.0f),
                    0.0f
                ),
                0
            ));
        }
    }
}

glm::vec2 Ship::rotate2D(float x, float y, float angle)
{
    float dx = cos(glm::radians(angle)) * x - sin(glm::radians(angle)) * y;
    float dy = sin(glm::radians(angle)) * x + cos(glm::radians(angle)) * y;
    return glm::vec2(dx, dy);
}

void Ship::generateEngineParticle(bool accel)
{
    const glm::vec2 enginePos(-28.0f, 0.0f);

    glm::vec2 particlePos;
    float dvx = 0.0f;
    float dvy = 0.0f;

    if (accel)
    {
        particlePos = rotate2D(enginePos.x + RNG::randFloat(0, 6), enginePos.y - RNG::randFloat(-5, 5), transform.angle);
        dvx = RNG::randFloat(-20.0f, -10.0f);
        dvy = RNG::randFloat(-2.0f, 2.0f);
    }
    else
    {
        particlePos = rotate2D(enginePos.x + RNG::randFloat(0, 2), enginePos.y + RNG::randFloat(-3.0f, 3.0f), transform.angle);
        dvx = -RNG::randFloat(0.5f, 1.0f);
        dvy = RNG::randFloat(-1.0f, 1.0f);
    }

    glm::vec2 particleVelRand = rotate2D(dvx, dvy, transform.angle);
    
    levelManager.addGameObject(new Particle
    (
        levelManager,
        Transform(
            transform.position + particlePos,
            RNG::randFloat(0, 360),
            transform.velocity + particleVelRand,
            RNG::randFloat(-4, 4)
        ),
        10
    ));
}

void Ship::fireLaser()
{
    glm::vec2 laserPos = rotate2D(50, 0, transform.angle);
    glm::vec2 laserVel = rotate2D(18, 0, transform.angle);

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
