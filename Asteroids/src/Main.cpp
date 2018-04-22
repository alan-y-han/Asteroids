#include <glad\glad.h> // include this before GLFW
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Shader.h"
#include "Renderer.h"

#include <iostream>


// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

// Function prototypes
void processInput(GLFWwindow* window);


int main(int argc, char const *argv[])
{
    Renderer renderer("Asteroids", 800, 600);
    GLFWwindow* window = renderer.initialise();
    if (!window)
    {
        std::cerr << "Failed to initialise GLFW window, exiting" << std::endl;
        return -1;
    }

    Shader shader("src/vs.glsl", "src/fs.glsl");


    while (!glfwWindowShouldClose(window))
    {
        // process input
        glfwPollEvents();
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // swap buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
