#include <glad\glad.h> // include this before GLFW
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "EventManager.h"
#include "LevelManager.h"
#include "Renderer.h"

#include <cstdlib>
#include <iostream>


// settings
const double SPF(1.0 / 60.0); // seconds per frame
unsigned int SCR_WIDTH(800);
unsigned int SCR_HEIGHT(600);

// Function prototypes
void processInput(GLFWwindow* window, KeyEventManager keyEventManager);


int main(int argc, char const *argv[])
{
    Renderer renderer("Asteroids", 800, 600, "src/vs.glsl", "src/fs.glsl");

    GLFWwindow* window = renderer.initialise();
    if (!window)
    {
        std::cerr << "Failed to initialise GLFW window, exiting" << std::endl;
        return EXIT_FAILURE;
    }

    LevelManager levelManager;
    levelManager.initialiseLevel();

    double previous = glfwGetTime();
    double lag = 0.0;

    while (!glfwWindowShouldClose(window))
    {
        // timing
        double current = glfwGetTime();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        bool ticked = false;

        while (lag >= SPF)
        {
            // process input
            glfwPollEvents();
            processInput(window, levelManager.keyEventManager);

            // update game state
            levelManager.tick();

            ticked = true;
            lag -= SPF;
        }

        // render
        if (ticked)
        {
            renderer.draw(levelManager.gameObjects);
        }
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void processInput(GLFWwindow* window, KeyEventManager keyEventManager)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        keyEventManager.trigger(GLFW_KEY_W);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        keyEventManager.trigger(GLFW_KEY_S);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        keyEventManager.trigger(GLFW_KEY_A);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        keyEventManager.trigger(GLFW_KEY_D);
    }
}
