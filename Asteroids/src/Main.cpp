#include <glad\glad.h> // include this before GLFW
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Config.h"
#include "LevelManager.h"
#include "Renderer.h"

#include <cstdlib>
#include <iostream>

// debug
#include <vector>
#include "RenderObject.h"


int main(int argc, char const *argv[])
{
    Renderer renderer("Asteroids", "src/vs.glsl", "src/fs.glsl");

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

        while (lag >= config::SPF)
        {
            // process input
            levelManager.processInput(window);

            // update game state
            levelManager.tick();

            ticked = true;
            lag -= config::SPF;
        }

        // render
        if (ticked)
        {
            renderer.clear();

            // draw debug
            std::cout << levelManager.gameObjects.size() << std::endl;

            std::vector<RenderObject*> boxList;
            levelManager.quadtree.getBoxes(boxList);
            renderer.draw(boxList);

            // draw
            renderer.draw(levelManager.gameObjects);

            // swap buffers
            renderer.swapBuffers();
        }
    }

    return EXIT_SUCCESS;
}
