#include <glm/gtc/type_ptr.hpp>


namespace collision
{
    static bool testCollision(glm::vec3 a1, glm::vec3 a2, glm::vec3 b1, glm::vec3 b2)
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
}
