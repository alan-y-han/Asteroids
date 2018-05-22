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
    std::unordered_map<CollisionObject*, std::vector<glm::vec2>> collisions = collisionObject.getCollisions(levelManager.laserQuadtree);

    std::vector<glm::vec2> hitPolyLocations;

    for (std::pair<CollisionObject*, std::vector<glm::vec2>> objectCollisionList : collisions)
    {
        std::vector<glm::vec2>& collisionPoints = objectCollisionList.second;

        for (glm::vec2& collisionPoint : collisionPoints)
        {
            generateHitParticle(collisionPoint, -(objectCollisionList.first->gameObject.transform.velocity * glm::vec2(0.2)));
            objectCollisionList.first->gameObject.hit(&collisionObject, collisionPoint);

            hitPolyLocations.push_back(collisionPoint);

            break; // only hit object once
        }
    }

    //std::unordered_set<std::vector<glm::vec2>> asteroidPolys;
    ////asteroidPolys.insert(models::asteroidVertices);

    //for (glm::vec2& hitPolyLocation : hitPolyLocations)
    //{

    //}
}

void Asteroid::generateHitParticle(glm::vec2 hitPosition, glm::vec2 velocity)
{
    glm::vec2 particlePos(RNG::randFloat(-1.0f, 1.0f), RNG::randFloat(-1.0f, 1.0f));
    float dvx = RNG::randFloat(-2, 2);
    float dvy = -RNG::randFloat(-2, 2);

    glm::vec2 particleVelRand(dvx, dvy);

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
