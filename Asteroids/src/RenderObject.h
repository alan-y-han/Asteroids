#pragma once

#include <glad\glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>


class RenderObject
{
public:
    RenderObject
    (
        glm::vec3 position,
        float angle,
        //std::vector<glm::vec3> vertices,
        std::vector<glm::vec3> vertices,
        glm::vec3 color
    );
    ~RenderObject();



    glm::vec3 position;
    float angle;
    float alpha;
    std::vector<glm::vec3> vertices;
    glm::vec3 color;

    // OpenGL
    unsigned int VAO;


private:
    // OpenGL
    unsigned int VBO;
};
