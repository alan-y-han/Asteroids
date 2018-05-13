#include "Asteroid.h"
#include "Models.h"
#include "Particle.h"
#include "GPUobjectManager.h"
#include <unordered_set>

// debug
#include <iostream>


// TODO: clean up
static float randFloat(float min, float max)
{
    float range = max - min;
    return min + (((float)rand() / RAND_MAX) * range);
}


Asteroid::Asteroid(LevelManager& levelManager, Transform& transform) :
    GameObject(levelManager, levelManager.gpuObjectManager.asteroid, transform),
    collisionObject(*this)
{
}

Asteroid::~Asteroid()
{
    levelManager.asteroids.erase(this);
}

void Asteroid::initialise()
{
    levelManager.asteroids.insert(this);
}

void Asteroid::move()
{
    transform.applyVelocities();
    updateInstanceVAsModelMatrix();

    collisionObject.generateMesh(models::asteroidVertices, transform);
    collisionObject.addMeshToQuadtree(levelManager.asteroidQuadtree);
}

void Asteroid::collisionCheck()
{
    std::unordered_map<CollisionObject*, std::vector<glm::vec2>> collisions = collisionObject.checkCollisions(levelManager.laserQuadtree);

    for (std::pair<CollisionObject*, std::vector<glm::vec2>> objectCollisionList : collisions)
    {
        std::vector<glm::vec2>& collisionPoints = objectCollisionList.second;

        for (glm::vec2& collisionPoint : collisionPoints)
        {
            generateHitParticle(glm::vec3(collisionPoint, 0.0f), - (objectCollisionList.first->gameObject.transform.velocity * glm::vec3(0.2)));
        }

        // N.B. this can occasionally remove the same object twice
        // this is ok because the object removal queue is a set (enforces uniqueness)
        // TODO: this is kinda hacky, maybe stop doing this?
        levelManager.removeGameObject(&objectCollisionList.first->gameObject);
    }
}

void Asteroid::generateHitParticle(glm::vec3 hitPosition, glm::vec3 velocity)
{
    glm::vec3 particlePos(randFloat(-1.0f, 1.0f), randFloat(-1.0f, 1.0f), 0.0f);
    float dvx = randFloat(-2, 2);
    float dvy = -randFloat(-2, 2);

    glm::vec3 particleVelRand(dvx, dvy, 0.0f);

    levelManager.addGameObject(new Particle
    (
        levelManager,
        Transform(
            hitPosition + particlePos,
            randFloat(0, 360),
            transform.velocity + velocity + particleVelRand,
            randFloat(-2, 2)
        ),
        15
    ));
}
