#pragma once

#include <glad\glad.h> // include this before GLFW
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "RenderObject.h"
#include "Shader.h"


class Renderer
{
public:    
    Renderer(std::string windowName, int width, int height, std::string vertexPath, std::string fragmentPath, std::vector<RenderObject>& renderObjects);
    GLFWwindow* initialise();
    void draw();
private:
    GLFWwindow* window;
    std::string name;
    static int SCR_WIDTH;
    static int SCR_HEIGHT;
    glm::mat4 view;
    glm::mat4 projection;

    std::string vertexPath;
    std::string fragmentPath;
    Shader shader;

    std::vector<RenderObject>& renderObjects;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
