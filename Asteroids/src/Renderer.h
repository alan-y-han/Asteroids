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

#include "GameObject.h"
#include "Config.h"
#include "Shader.h"

#include <functional>


class Renderer
{
public:
    Renderer(std::string windowName, std::string vertexPath, std::string fragmentPath);
    ~Renderer();
    GLFWwindow* initialise();
    void draw(std::unordered_set<GameObject*>& gameObjects);
private:
    // constructor arguments
    std::string name;
    std::string vertexPath;
    std::string fragmentPath;

    GLFWwindow* window;
    glm::mat4 view;
    glm::mat4 projection;

    Shader shader;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
