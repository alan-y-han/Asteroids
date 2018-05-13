#include "Asteroid.h"
#include "Models.h"
#include "Particle.h"
#include "GPUobjectManager.h"
#include <unordered_set>

// debug
#include <iostream>


Asteroid::Asteroid(LevelManager& levelManager, Transform& transform) :
    GameObject(levelManager, levelManager.gpuObjectManager.asteroid, transform)
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
            levelManager.addGameObject(new Particle
            (
                levelManager,
                Transform(
                    glm::vec3(collisionPoint, 12.0f),
                    0.0f,
                    glm::vec3(0),
                    0.0f
                )
            ));
        }
    }
}
