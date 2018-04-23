#pragma once

#include <glad\glad.h> // include this before GLFW
#include <GLFW\glfw3.h>

#include <iostream>
#include <string>
#include <vector>

#include "RenderObject.h"


class Renderer
{
public:    
    Renderer(std::string name, int width, int height);
    GLFWwindow* initialise();
    void addRenderObject(RenderObject* renderObject);
    void draw();
private:
    GLFWwindow* window;
    std::string name;
    static int SCR_WIDTH;
    static int SCR_HEIGHT;

    std::vector<RenderObject*> renderObjects;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
