#include <glm/gtc/type_ptr.hpp>

#include "GameObject.h"


namespace collision
{
    static bool testLineCollision(const glm::vec3& a1, const glm::vec3& a2, const glm::vec3& b1, const glm::vec3& b2)
    {
        // check if either line is of length zero
        if ((a1.x == a2.x && a1.y == a2.y) || (b1.x == b2.x && b1.y == b2.y))
        {
            return false;
        }

        float denominator = (((b2.y - b1.y) * (a2.x - a1.x)) - ((b2.x - b1.x) * (a2.y - a1.y)));
        if (denominator == 0)
        {
            return false;
        }

        float ma = (((b2.x - b1.x) * (a1.y - b1.y)) - ((b2.y - b1.y) * (a1.x - b1.x))) / denominator;
        float mb = (((a2.x - a1.x) * (a1.y - b1.y)) - ((a2.y - a1.y) * (a1.x - b1.x))) / denominator;

        return ((ma < 1) && (ma > 0)) && ((mb < 1) && (mb > 0));
    }

    static bool testGOcollision(const GameObject& a, const GameObject& b)
    {
        for (int i = 0; i < a.vertices.size(); i++)
        {
            for (int j = 0; j < b.vertices.size(); j++)
            {
                unsigned int a1 = i;
                unsigned int a2 = (i + 1) % a.vertices.size();
                unsigned int b1 = j;
                unsigned int b2 = (j + 1) % b.vertices.size();

                bool collision = testLineCollision(a.vertices[a1], a.vertices[a2], b.vertices[b1], b.vertices[b2]);
                if (collision)
                {
                    return true;
                }
            }
        }
        return false;
    }
}
