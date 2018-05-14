#include "Asteroid.h"
#include "Models.h"
#include "Particle.h"
#include "GPUobjectManager.h"
#include "RNG.h"
#include <unordered_set>


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
            generateHitParticle(glm::vec3(collisionPoint, 0.0f), -(objectCollisionList.first->gameObject.transform.velocity * glm::vec3(0.2)));
            objectCollisionList.first->gameObject.hit(&collisionObject, collisionPoint);
            break; // only hit object once
        }
    }
}

void Asteroid::generateHitParticle(glm::vec3 hitPosition, glm::vec3 velocity)
{
    glm::vec3 particlePos(RNG::randFloat(-1.0f, 1.0f), RNG::randFloat(-1.0f, 1.0f), 0.0f);
    float dvx = RNG::randFloat(-2, 2);
    float dvy = -RNG::randFloat(-2, 2);

    glm::vec3 particleVelRand(dvx, dvy, 0.0f);

    levelManager.addGameObject(new Particle
    (
        levelManager,
        Transform(
            hitPosition + particlePos,
            RNG::randFloat(0, 360),
            transform.velocity + velocity + particleVelRand,
            RNG::randFloat(-2, 2)
        ),
        15
    ));
}
