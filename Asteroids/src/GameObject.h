#pragma once

#include <glad\glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdlib>
#include <iostream>
#include <functional>
#include <vector>


class GameObject
{
public:
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
        std::function<void(GameObject* gameObject)>& removeGOFunc,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity,
        std::vector<glm::vec3> vertices,
        glm::vec3 color
    );
    virtual ~GameObject();

    // public GameObject functions, to be overriden in derived classes
    virtual void tickFunction();

private:
    // OpenGL rendering
    unsigned int VBO;
};
