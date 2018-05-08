#pragma once

#include <glad\glad.h> // include this before GLFW
#include <GLFW\glfw3.h>

#include <string>


class GLinitialiser
{
public:
    GLinitialiser();
    ~GLinitialiser();

    GLFWwindow* createWindow(std::string windowName);

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
