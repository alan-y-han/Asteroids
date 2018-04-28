#pragma once

#include <glad\glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdlib>
#include <iostream>
#include <vector>

#include "EventManager.h"


class GameObject
{
public:
    TickEventManager& tickEventManager;
    std::function<void(GameObject* gameObject)>& removeGOFunc;
    glm::vec3 position;
    glm::vec3 velocity;
    float angle;
    float rVelocity;
    float alpha;
    // OpenGL rendering
    unsigned int VAO;

    GameObject
    (
        TickEventManager& tickEventManager,
        std::function<void(GameObject* gameObject)>& removeGOFunc,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity,
        std::vector<float> vertices,
        glm::vec3 color
    );
    virtual ~GameObject();

private:
    glm::vec3 color;
    std::vector<float> vertices;
    // OpenGL rendering
    unsigned int VBO;
};
