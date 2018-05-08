#pragma once

#include <glad\glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdlib>
#include <iostream>
#include <vector>

#include "LevelManager.h"


class GameObject
{
public:
    GameObject
    (
        LevelManager& levelManager,
        glm::vec3 position,
        glm::vec3 velocity,
        float angle,
        float rVelocity,
        std::vector<glm::vec3> vertices,
        glm::vec3 color
    );
    virtual ~GameObject();

    // public GameObject functions, to be overriden in derived classes
    virtual void initialise();
    virtual void move();
    virtual void collisionCheck();


    LevelManager& levelManager;
    glm::vec3 position;
    glm::vec3 velocity;
    float angle;
    float rVelocity;
    float alpha;
    std::vector<glm::vec3> vertices;
    glm::vec3 color;

    // OpenGL
    unsigned int VAO;


private:
    // OpenGL
    unsigned int VBO;
};
