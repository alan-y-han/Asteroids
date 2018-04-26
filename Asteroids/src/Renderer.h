#pragma once

#include <glad\glad.h> // include this before GLFW
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "GameObject.h"
#include "Shader.h"

#include <functional>


class Renderer
{
public:
    Renderer(std::string windowName, int width, int height, std::string vertexPath, std::string fragmentPath);
    GLFWwindow* initialise();
    void draw();
    void registerRO(GameObject* ro);

private:
    static int SCR_WIDTH;
    static int SCR_HEIGHT;

    // constructor arguments
    std::string name;
    std::string vertexPath;
    std::string fragmentPath;
    std::vector<GameObject*> renderObjects;

    GLFWwindow* window;
    glm::mat4 view;
    glm::mat4 projection;

    Shader shader;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
