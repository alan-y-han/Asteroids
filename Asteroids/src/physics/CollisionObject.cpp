#include "CollisionObject.h"
#include "Config.h"
#include "Quadtree.h"


CollisionObject::CollisionObject()
{
}

void CollisionObject::generateMesh(const std::vector<glm::vec3>& vertices, Transform& transform, Quadtree& quadtree)
{
    collisionMesh.clear();

    glm::mat4 model = transform.getModelMatrix(0, 0);

    std::vector<glm::vec3> transformed;
    for (const glm::vec3& v : vertices)
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
                addLineToMesh(x, y, 0, transformed);
                addMotionLineToMesh(x, y, transformed[0], transform);
                addMotionLineToMesh(x, y, transformed[1], transform);

            }
        }
    }
    else
    {
        for (int x = -1; x <= 1; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                for (unsigned int i = 0; i < transformed.size(); i++)
                {
                    addLineToMesh(x, y, i, transformed);
                    addMotionLineToMesh(x, y, transformed[i], transform);
                }
            }
        }
    }

    for (Line& l : collisionMesh)
    {
        quadtree.insert(&l);
    }
}

void CollisionObject::addLineToMesh(int x, int y, int i, std::vector<glm::vec3>& transformed)
{
    unsigned int i1 = i;
    unsigned int i2 = (i + 1) % transformed.size();

    glm::vec2 t1(transformed[i1]);
    glm::vec2 t2(transformed[i2]);

    glm::vec2 offset(x * config::SCR_WIDTH, y * config::SCR_HEIGHT);

    // emplace actual line
    collisionMesh.emplace_back(t1 + offset, t2 + offset, this);

}

// add interpolated motion lines for each vertex (to prevent high speed objects going through each other)
void CollisionObject::addMotionLineToMesh(int x, int y, glm::vec2 vertex, Transform& transform)
{
    //glm::vec3 offset(x * config::SCR_WIDTH, y * config::SCR_HEIGHT, 0.0f);

    //collisionMesh.emplace_back(vertex, vertex - glm::vec2(transform.velocity), this);
}
