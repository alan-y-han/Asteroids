#include <glad\glad.h> // include this before GLFW
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Config.h"
#include "GLinitialiser.h"
#include "LevelManager.h"
#include "Renderer.h"

#include <cstdlib>
#include <iostream>

// debug
#include <vector>
#include "GPUobject.h"


int main(int argc, char const *argv[])
{
    GLinitialiser glInitialiser;
    GLFWwindow* window = glInitialiser.createWindow("Asteroids");

    if (!window)
    {
        std::cerr << "Failed to initialise GLFW window, exiting" << std::endl;
        return EXIT_FAILURE;
    }

    Renderer renderer(window, "src/renderer/vsInstanced.glsl", "src/renderer/fsInstanced.glsl");

    LevelManager levelManager(renderer.gpuObjectManager);
    levelManager.initialiseLevel();

    double previous = glfwGetTime();
    double lag = 0.0;

    // debug
    int frame(0);

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
            // debug
            std::cerr << "Begin tick" << std::endl;
            levelManager.quadtree.objs.clear();
            frame++;

            // process input
            levelManager.processInput(window);

            // update game state
            levelManager.tick();

            // debug
            std::vector<Line*>& lobjs = levelManager.quadtree.objs;
            std::cerr << "Main: quadtree insertions: " << lobjs.size() << std::endl;
            for (Line* line : lobjs)
            {
                std::cerr << line->p1.x << ", " << line->p1.y << std::endl;
            }

            ticked = true;
            lag -= config::SPF;
        }

        // render
        if (ticked)
        {
            renderer.clear();

            // debug
            std::cerr << levelManager.gameObjects.size() << std::endl;

            levelManager.quadtree.draw();

            // draw
            renderer.draw();

            // swap buffers
            renderer.swapBuffers();
        }
    }

    return EXIT_SUCCESS;
}
