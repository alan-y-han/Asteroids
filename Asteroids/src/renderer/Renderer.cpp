#include "Renderer.h"


Renderer::Renderer(GLFWwindow* window, std::string vertexPath, std::string fragmentPath) :
    window(window)
{
    // OpenGL options
    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(1);

    // Initialise camera
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -32.0f));

    projection = glm::ortho(0.0f, static_cast<float>(config::SCR_WIDTH), 0.0f, static_cast<float>(config::SCR_HEIGHT), 0.1f, 100.0f);
    //projection = glm::ortho(-config::SCR_WIDTH, config::SCR_WIDTH * 2, -config::SCR_HEIGHT, config::SCR_HEIGHT * 2, 0.1f, 100.0f);

    // Initialise shader
    shader.initialiseShader(vertexPath, fragmentPath);
    shader.use();
    shader.setViewMatrix(view);
    shader.setProjectionMatrix(projection);

    // Initialise shaderNew
    shaderNew.initialiseShader("src/renderer/vsInstanced.glsl", "src/renderer/fsInstanced.glsl");
    shaderNew.use();
    //shaderNew.setViewMatrix(view);
    //shaderNew.setProjectionMatrix(projection);
    glUniformMatrix4fv(glGetUniformLocation(shaderNew.ID, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderNew.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
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
    shaderNew.use();
    gpuObjectManager.drawAllObjects();
}

void Renderer::swapBuffers()
{
    glfwSwapBuffers(window);
}

void Renderer::draw(std::vector<RenderObjectOri*> renderObjects)
{
    shader.use();

    for (RenderObjectOri* go : renderObjects)
    {
        glBindVertexArray(go->VAO);

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

        shader.setAlpha(go->alpha);

        glDrawArrays(GL_LINE_LOOP, 0, go->vertices.size());

    }
}
