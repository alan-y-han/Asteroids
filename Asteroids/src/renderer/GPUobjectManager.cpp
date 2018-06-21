#include "GPUobjectManager.h"
#include "Models.h"


GPUobjectManager::GPUobjectManager() :
    ship(new GPUobject(models::shipVertices, models::shipColor)),
    particle(new GPUobject(models::particleVertices, models::particleColor)),
    laser(new GPUobject(models::laserVertices, models::laserColor)),
    asteroid(new GPUobject(models::asteroidVertices, models::asteroidColor))
{
    allObjects.insert(ship);
    allObjects.insert(particle);
    allObjects.insert(laser);
    allObjects.insert(asteroid);
}

GPUobjectManager::~GPUobjectManager()
{
    // clean up remaining objects
    for (GPUobject* object : allObjects)
    {
        delete object;
    }
}

GPUobject* GPUobjectManager::createObject(std::vector<glm::vec2> vertices, glm::vec3 color)
{
    GPUobject* newObject = new GPUobject(vertices, color);
    allObjects.insert(newObject);
    return newObject;
}

void GPUobjectManager::deleteObject(GPUobject* object)
{
    allObjects.erase(object);
    delete object;
}

void GPUobjectManager::drawAllObjects()
{
    for (GPUobject* object : allObjects)
    {
        object->draw();
    }
}
