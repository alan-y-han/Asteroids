#include <glad\glad.h> // include this before GLFW
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Models.h"
#include "Renderer.h"

#include <iostream>


// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

// Function prototypes
void processInput(GLFWwindow* window);


int main(int argc, char const *argv[])
{
    Renderer renderer("Asteroids", 800, 600, "src/vs.glsl", "src/fs.glsl");
    GLFWwindow* window = renderer.initialise();
    if (!window)
    {
        std::cerr << "Failed to initialise GLFW window, exiting" << std::endl;
        return -1;
    }

    RenderObject ship(glm::vec3(4, 3, 0), glm::vec3(0, 0, 0), models::ship, std::vector<float>({ 1.0f, 0.0f, 0.5f }));
    renderer.addRenderObject(&ship);

    RenderObject cube(glm::vec3(5, 5, 0), glm::vec3(0, 0, 0), models::testSquare, std::vector<float>({ 1.0f, 0.0f, 0.5f }));
    renderer.addRenderObject(&cube);

    while (!glfwWindowShouldClose(window))
    {
        // process input
        glfwPollEvents();
        processInput(window);

        renderer.draw();
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
