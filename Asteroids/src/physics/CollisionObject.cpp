#include "CollisionObject.h"
#include "Config.h"
#include "Quadtree.h"


CollisionObject::CollisionObject()
{
}


// TODO: maybe generate model matrix once in gameObject, remove from Renderer.cpp
void CollisionObject::generateMesh(std::vector<glm::vec3>& vertices, glm::vec3& position, float angle, Quadtree& quadtree)
{
    collisionMesh.clear();

    glm::mat4 model;
    // rotation
    float rad = glm::radians(angle);
    model[0][0] = cos(rad);
    model[1][0] = -sin(rad);
    model[0][1] = sin(rad);
    model[1][1] = cos(rad);
    // translation
    model[3][0] = position.x;
    model[3][1] = position.y;
    model[3][2] = position.z;

    std::vector<glm::vec3> transformed;
    for (glm::vec3& v : vertices)
    {
        transformed.push_back(model * glm::vec4(v, 1.0));
    }

    // put branch outside of double loop
    if (transformed.size() == 2)
    {
        for (int x = -1; x <= 1; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                addToMesh(x, y, 0, transformed);
            }
        }
    }
    else
    {
        for (int x = -1; x <= 1; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                for (int i = 0; i < transformed.size(); i++)
                {
                    addToMesh(x, y, 0, transformed);
                }
            }
        }
    }


    for (Line l : collisionMesh)
    {
        quadtree.insert(l);
    }
}

void CollisionObject::addToMesh(int x, int y, int i, std::vector<glm::vec3>& transformed)
{
    unsigned int i1 = i;
    unsigned int i2 = (i + 1) % transformed.size();

    glm::vec3& t1 = transformed[i1];
    glm::vec3& t2 = transformed[i2];

    glm::vec3 offset(x * config::SCR_WIDTH, y * config::SCR_HEIGHT, 0.0f);

    collisionMesh.emplace_back(glm::vec2(t1 + offset), glm::vec2(t2 + offset), this);
}