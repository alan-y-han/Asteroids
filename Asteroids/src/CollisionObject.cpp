#include "CollisionObject.h"
#include "Config.h"
#include "Quadtree.h"


CollisionObject::CollisionObject()
{
}

//bool CollisionObject::testObjectCollision(CollisionObject& b)
//{
//
//    for (int i = 0; i < a.vertices.size(); i++)
//    {
//        for (int j = 0; j < b.vertices.size(); j++)
//        {
//            unsigned int a1 = i;
//            unsigned int a2 = (i + 1) % a.vertices.size();
//            unsigned int b1 = j;
//            unsigned int b2 = (j + 1) % b.vertices.size();
//
//            bool collision = testLineCollision(a.vertices[a1], a.vertices[a2], b.vertices[b1], b.vertices[b2]);
//            if (collision)
//            {
//                return true;
//            }
//        }
//    }
//    return false;
//}
//
//bool CollisionObject::testLineCollision(Line& a, Line& b)
//{
//    glm::vec3& a1 = a.p1;
//    glm::vec3& a2 = a.p2;
//    glm::vec3& b1 = b.p1;
//    glm::vec3& b2 = b.p2;
//
//    // check if either line is of length zero
//    if ((a1.x == a2.x && a1.y == a2.y) || (b1.x == b2.x && b1.y == b2.y))
//    {
//        return false;
//    }
//
//    float denominator = (((b2.y - b1.y) * (a2.x - a1.x)) - ((b2.x - b1.x) * (a2.y - a1.y)));
//    if (denominator == 0)
//    {
//        return false;
//    }
//
//    float ma = (((b2.x - b1.x) * (a1.y - b1.y)) - ((b2.y - b1.y) * (a1.x - b1.x))) / denominator;
//    float mb = (((a2.x - a1.x) * (a1.y - b1.y)) - ((a2.y - a1.y) * (a1.x - b1.x))) / denominator;
//
//    return ((ma < 1) && (ma > 0)) && ((mb < 1) && (mb > 0));
//}


// TODO: maybe generate model matrix once in gameObject, remove from Renderer.cpp
void CollisionObject::generateMesh(std::vector<glm::vec3>& vertices, glm::vec3& position, float angle, Quadtree& quadtree)
{
    //collisionMesh.clear();

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

    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            for (int i = 0; i < transformed.size(); i++)
            {
                unsigned int i1 = i;
                unsigned int i2 = (i + 1) % transformed.size();

                glm::vec3& t1 = transformed[i1];
                glm::vec3& t2 = transformed[i2];

                glm::vec3 offset(x * config::SCR_WIDTH, y * config::SCR_HEIGHT, 0.0f);

                //collisionMesh.emplace_back();
                quadtree.insert(Line(glm::vec2(t1 + offset), glm::vec2(t2 + offset), this));
            }
        }
    }
}
