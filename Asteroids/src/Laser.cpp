#include "Laser.h"
#include "Collision.h"
#include "Models.h"


Laser::Laser(
    LevelManager& levelManager,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity
):
    GameObject(levelManager, position, velocity, angle, rVelocity, models::laserVertices, models::laserColor),
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

    // update collision mesh
    collisionObject.generateMesh(vertices, position, angle, levelManager.quadtree);
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
