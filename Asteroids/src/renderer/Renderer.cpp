#include "Renderer.h"


Renderer::Renderer(GLFWwindow* window, std::string vertexPath, std::string fragmentPath) :
    window(window),
    shader("src/renderer/vsInstanced.glsl", "src/renderer/fsInstanced.glsl")
{
    // OpenGL options
    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(1);

    // Initialise camera
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -32.0f));

    float scrWidth = static_cast<float>(config::SCR_WIDTH);
    float scrHeight = static_cast<float>(config::SCR_HEIGHT);

    projection = glm::ortho(0.0f, scrWidth, 0.0f, scrHeight, 0.1f, 100.0f);
    //projection = glm::ortho((-scrWidth) * 0.1f, scrWidth * 1.1f, (-scrHeight) * 0.1f, scrHeight * 1.1f, 0.1f, 100.0f);
    //projection = glm::ortho(-scrWidth, scrWidth * 2, -scrHeight, scrHeight * 2, 0.1f, 100.0f);

    // Send matrices to shader
    shader.use();
    shader.setViewMatrix(view);
    shader.setProjectionMatrix(projection);
}

Renderer::~Renderer()
{
}

void Renderer::clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw()
{
    shader.use();
    gpuObjectManager.drawAllObjects();
}

void Renderer::draw(std::vector<GPUobject*> gpuObjects)
{
    for (GPUobject* gpuObject : gpuObjects)
    {
        gpuObject->draw();
    }
}

void Renderer::swapBuffers()
{
    glfwSwapBuffers(window);
}
