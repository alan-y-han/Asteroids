#include <glad\glad.h> // include this before GLFW
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include "Config.h"
#include "GLinitialiser.h"
#include "LevelManager.h"
#include "Renderer.h"

#include <cstdlib>
#include <iostream>

// debug
#include <vector>
#include "DebugLine.h"
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
    bool qReleased(true);
    bool drawQuadtrees(false);

    DebugLine dLine;


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
            glfwPollEvents();
            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            {
                if (qReleased)
                {
                    drawQuadtrees = !drawQuadtrees;
                    qReleased = false;
                }
            }
            else
            {
                qReleased = true;
            }
            // end debug

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

            // draw
            renderer.draw();

            // debug
            std::cerr << levelManager.gameObjects.size() << std::endl;

            if (drawQuadtrees)
            {
                levelManager.laserQuadtree.draw();

                //std::vector<Line*> quadtreeLines(levelManager.laserQuadtree.retrieveAll());

                //for (Line* line : quadtreeLines)
                //{
                //    dLine.draw(glm::vec3(line->p1, 2), glm::vec3(line->p2, 2), glm::vec3(1, 0, 0));
                //}
            }

            // swap buffers
            renderer.swapBuffers();
        }
    }

    return EXIT_SUCCESS;
}
