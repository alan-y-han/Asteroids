#include <glad\glad.h> // include this before GLFW
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "LevelManager.h"
#include "Models.h"
#include "Renderer.h"

#include <cstdlib>
#include <iostream>


// settings
const double SPF(1.0 / 60.0); // seconds per frame
unsigned int SCR_WIDTH(800);
unsigned int SCR_HEIGHT(600);

// Function prototypes
void processInput(GLFWwindow* window);


int main(int argc, char const *argv[])
{
    LevelManager levelManager;

    Renderer renderer("Asteroids", 800, 600, "src/vs.glsl", "src/fs.glsl", levelManager.renderObjects);
    GLFWwindow* window = renderer.initialise();
    if (!window)
    {
        std::cerr << "Failed to initialise GLFW window, exiting" << std::endl;
        return EXIT_FAILURE;
    }

    RenderObject ship(glm::vec3(4, 3, 0), glm::vec3(0, 0, 0), models::ship, std::vector<float>({ 1.0f, 0.0f, 0.5f }));
    levelManager.addRenderObject(ship);

    RenderObject cube(glm::vec3(5, 5, 0), glm::vec3(0.0f, -0.02f, 0.0f), models::testSquare, std::vector<float>({ 1.0f, 0.0f, 0.5f }));
    levelManager.addRenderObject(cube);


    double previous = glfwGetTime();
    double lag = 0.0;

    while (!glfwWindowShouldClose(window))
    {
        // timing
        double current = glfwGetTime();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        // process input
        glfwPollEvents();
        processInput(window);

        bool ticked = false;

        while (lag >= SPF)
        {
            // update game state
            levelManager.tick();

            ticked = true;
            lag -= SPF;
        }

        // render
        if (ticked)
        {
            renderer.draw();
        }
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
