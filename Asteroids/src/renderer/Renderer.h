#pragma once

#include <glad\glad.h> // include this before GLFW
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_set>

#include "Config.h"
#include "GPUobjectManager.h"
#include "Shader.h"

#include <functional>

// debug
#include "RenderObjectOri.h"


class Renderer
{
public:
    Renderer(GLFWwindow* window, std::string vertexPath, std::string fragmentPath);
    ~Renderer();
    
    void clear();
    void draw();
    void draw(std::vector<GPUobject*> gpuObjects);
    void swapBuffers();

    // debug
    void draw(std::vector<RenderObjectOri*> renderObjects);


    GPUobjectManager gpuObjectManager;


private:
    GLFWwindow* window;

    glm::mat4 view;
    glm::mat4 projection;

    Shader shader;
    Shader shaderNew;
};
