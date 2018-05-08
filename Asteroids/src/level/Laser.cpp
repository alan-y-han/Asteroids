#include "Laser.h"
#include "Collision.h"
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

    // update collision mesh
    collisionObject.generateMesh(models::laserVertices, transform.position, transform.angle, levelManager.quadtree);
}

void Laser::collisionCheck()
{
    //for (GameObject* laser : levelManager.lasers)
    //{
    //    bool hasCollided = collision::testGOcollision(*this, *laser);
    //    if (hasCollided)
    //    {
    //        std::cout << "Collision!\n";
    //    }
    //}

    //collision::testCollision()
}
