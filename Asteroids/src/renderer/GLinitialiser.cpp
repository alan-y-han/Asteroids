#include "GLinitialiser.h"
#include "Config.h"
#include <iostream>


GLinitialiser::GLinitialiser()
{
}

GLinitialiser::~GLinitialiser()
{
    glfwTerminate();
}

GLFWwindow* GLinitialiser::createWindow(std::string windowName)
{
    // Initialise GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(config::SCR_WIDTH, config::SCR_HEIGHT, windowName.c_str(), NULL, NULL);
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

    //// OpenGL options
    //glEnable(GL_DEPTH_TEST);
    //glfwSwapInterval(1);

    //// Initialise camera
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -32.0f));

    ////projection = glm::ortho(0.0f, config::SCR_WIDTH, 0.0f, config::SCR_HEIGHT, 0.1f, 100.0f);
    //projection = glm::ortho(-config::SCR_WIDTH, config::SCR_WIDTH * 2, -config::SCR_HEIGHT, config::SCR_HEIGHT * 2, 0.1f, 100.0f);

    //// Initialise shader
    //shader.initialiseShader(vertexPath, fragmentPath);
    //shader.use();
    //shader.setViewMatrix(view);
    //shader.setProjectionMatrix(projection);

    return window;
}

void GLinitialiser::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
