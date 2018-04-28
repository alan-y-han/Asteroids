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
    const std::vector<glm::vec3> vertices;
    const glm::vec3 color;
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
        std::vector<glm::vec3> vertices,
        glm::vec3 color
    );
    virtual ~GameObject();
    virtual void initialise(); // default does nothing by default, override in derived class

private:
    // OpenGL rendering
    unsigned int VBO;
};
