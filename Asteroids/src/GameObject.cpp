#include "GameObject.h"

GameObject::GameObject(
    TickEventManager& tickEventManager,
    std::function<void(GameObject* gameObject)>& removeGOFunc,
    glm::vec3 position,
    glm::vec3 velocity,
    float angle,
    float rVelocity,
    std::vector<glm::vec3> vertices,
    glm::vec3 color
) :
    tickEventManager(tickEventManager),
    removeGOFunc(removeGOFunc),
    position(position),
    velocity(velocity),
    angle(angle),
    rVelocity(rVelocity),
    alpha(1.0f),
    vertices(vertices),
    color(color)
{
    // assemble vertex buffer array from vertexData and color

    int vertexDataSize = vertices.size() * 3 * 2; // 6 floats per vertex

    float* vertexData = (float*)malloc(vertexDataSize * sizeof(float)); // X, Y, Z, R, G, B
    if (vertexData == NULL)
    {
        std::cerr << "malloc failed in GameObject" << std::endl;
    }

    for (int i = 0; i < vertices.size(); i++)
    {
        vertexData[(i * 6) + 0] = vertices[i].x;
        vertexData[(i * 6) + 1] = vertices[i].y;
        vertexData[(i * 6) + 2] = vertices[i].z;
        vertexData[(i * 6) + 3] = color.r;
        vertexData[(i * 6) + 4] = color.g;
        vertexData[(i * 6) + 5] = color.b;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexDataSize * sizeof(float), vertexData, GL_STATIC_DRAW);
    free(vertexData);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

GameObject::~GameObject()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
