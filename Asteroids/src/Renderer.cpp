#include "Renderer.h"


Renderer::Renderer(std::string windowName, std::string vertexPath, std::string fragmentPath) :
    name(windowName),
    vertexPath(vertexPath),
    fragmentPath(fragmentPath)
{
}

GLFWwindow* Renderer::initialise()
{
    // Initialise GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(config::SCR_WIDTH, config::SCR_HEIGHT, name.c_str(), NULL, NULL);
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

    projection = glm::ortho(0.0f, config::SCR_WIDTH, 0.0f, config::SCR_HEIGHT, 0.1f, 100.0f);

    // Initialise shader
    shader.initialiseShader(vertexPath, fragmentPath);
    shader.use();
    shader.setViewMatrix(view);
    shader.setProjectionMatrix(projection);

    return window;
}

void Renderer::draw(std::unordered_set<std::unique_ptr<GameObject>>& gameObjects)
{
    shader.use();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const std::unique_ptr<GameObject>& go : gameObjects)
    {
        // create model matrix and pass to shader
        glm::mat4 model;
        // rotation
        float rad = glm::radians(go->angle);
        model[0][0] = cos(rad);
        model[1][0] = -sin(rad);
        model[0][1] = sin(rad);
        model[1][1] = cos(rad);
        // translation
        model[3][0] = go->position.x;
        model[3][1] = go->position.y;
        model[3][2] = go->position.z;

        shader.setModelMatrix(model);

        glBindVertexArray(go->VAO);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }

    // swap buffers
    glfwSwapBuffers(window);
}

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
