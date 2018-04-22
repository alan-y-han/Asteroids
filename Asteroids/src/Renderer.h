#pragma once

#include <glad\glad.h> // include this before GLFW
#include <GLFW\glfw3.h>

#include <string>
#include <iostream>


class Renderer
{
public:    
    Renderer(std::string name, int width, int height);
    GLFWwindow* initialise();
    GLFWwindow* getWindow();
private:
    GLFWwindow* window;
    std::string name;
    static int SCR_WIDTH;
    static int SCR_HEIGHT;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
