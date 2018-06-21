#pragma once

#include <glm\glm.hpp>

#include <vector>
#include <unordered_set>

#include "GPUobject.h"


// creates and stores all GPUobjects
// creates objects for existing models on construction
// allows creating custom objects through createObject
class GPUobjectManager
{
public:
    GPUobjectManager();
    ~GPUobjectManager();

    GPUobject* ship;
    GPUobject* particle;
    GPUobject* laser;
    GPUobject* asteroid;

    GPUobject* createObject(std::vector<glm::vec2> vertices, glm::vec3 color);
    void deleteObject(GPUobject* object);

    void drawAllObjects();


private:
    // disable copying class
    GPUobjectManager(const GPUobjectManager&) = delete;
    GPUobjectManager& operator=(const GPUobjectManager&) = delete;

    std::unordered_set<GPUobject*> allObjects;

};
