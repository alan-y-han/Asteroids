#include "Laser.h"
#include "GPUobjectManager.h"
#include "Models.h"


Laser::Laser(LevelManager& levelManager, Transform& transform) :
    GameObject(levelManager, levelManager.gpuObjectManager.laser, transform),
    lifetimeRemaining(360)
{
}

Laser::~Laser()
{
    levelManager.lasers.erase(this);
}

void Laser::initialise()
{
    levelManager.lasers.insert(this);
}

void Laser::move()
{
    lifetimeRemaining--;
    if (lifetimeRemaining < 0)
    {
        levelManager.removeGameObject(this);
    }

    // movement
    transform.applyVelocities();

    updateInstanceVAsModelMatrix();

    // update collision mesh, add to quadtree
    collisionObject.generateMesh(models::laserVertices, transform);
    collisionObject.addMeshToQuadtree(levelManager.laserQuadtree);
}

void Laser::collisionCheck()
{
}
