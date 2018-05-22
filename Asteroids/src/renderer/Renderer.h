#pragma once

#include <glad\glad.h> // include this before GLFW
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_set>

#include "Config.h"
#include "GPUobject.h"
#include "GPUobjectManager.h"
#include "Shader.h"


class Renderer
{
public:
    Renderer(GLFWwindow* window, std::string vertexPath, std::string fragmentPath);
    ~Renderer();
    
    void clear();
    void draw();
    void draw(std::vector<GPUobject*> gpuObjects);
    void swapBuffers();


    GPUobjectManager gpuObjectManager;


private:
    GLFWwindow* window;

    glm::mat4 view;
    glm::mat4 projection;

    Shader shader;
};
