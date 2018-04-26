#include "Renderer.h"


int Renderer::SCR_WIDTH;
int Renderer::SCR_HEIGHT;

Renderer::Renderer(std::string windowName, int width, int height, std::string vertexPath, std::string fragmentPath) :
    name(windowName),
    vertexPath(vertexPath),
    fragmentPath(fragmentPath)
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
    glfwSwapInterval(1);

    // Initialise camera
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -32.0f));

    projection = glm::ortho(0.0f, 8.0f, 0.0f, 6.0f, 0.1f, 100.0f);

    // Initialise shader
    shader.initialiseShader(vertexPath, fragmentPath);
    shader.use();
    shader.setViewMatrix(view);
    shader.setProjectionMatrix(projection);

    return window;
}

void Renderer::draw()
{
    // render
    shader.use();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (RenderObject* ro : renderObjects)
    {
        // pass model matrix to shader
        glm::mat4 model;
        model = glm::translate(model, ro->position);
        model = glm::rotate(model, glm::radians(ro->angle), glm::vec3(0.0f, 0.0f, 1.0f));
        shader.setModelMatrix(model);
        
        glBindVertexArray(ro->VAO);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }

    // swap buffers
    glfwSwapBuffers(window);
}

void Renderer::registerRO(RenderObject* ro)
{
    renderObjects.push_back(ro);
}

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport(0, 0, width, height);
}
