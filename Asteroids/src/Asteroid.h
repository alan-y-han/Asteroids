#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <functional>
#include <vector>

#include "Config.h"
#include "GameObject.h"


class Asteroid : public GameObject
{
public:
    Asteroid(
        std::function<void(GameObject* gameObject)>& removeGOFunc,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity
    );
    ~Asteroid();

private:

    void tickFunction();
};
