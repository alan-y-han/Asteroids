#include "Renderer.h"


int Renderer::SCR_WIDTH;
int Renderer::SCR_HEIGHT;

Renderer::Renderer(std::string name, int width, int height) :
    name(name)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

GLFWwindow* Renderer::initialise()
{
    // Initialise GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, name.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    return window;
}

void Renderer::addRenderObject(RenderObject* renderObject)
{
    renderObjects.push_back(renderObject);
}

void Renderer::draw()
{
    // render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < renderObjects.size(); i++)
    {
        glBindVertexArray(renderObjects[i]->VAO);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }

    // swap buffers
    glfwSwapBuffers(window);
}

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport(0, 0, width, height);
}
