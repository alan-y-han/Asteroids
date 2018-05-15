#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "RNG.h"


// Forward-facing direction is along X axis

// N.B. all model vertices must be defined clockwise
// (requried for mesh cutting function to work)

namespace models
{
    static const std::vector<glm::vec3> shipVertices =
    {
        glm::vec3(50.0f, 0.0f, 0.0f),
        glm::vec3(-30.0f, 25.0f, 0.0f),
        glm::vec3(-15.0f, 0.0f, 0.0f),
        glm::vec3(-30.0f, -25.0f, 0.0f)
    };
    static const glm::vec3 shipColor(1.0f, 1.0f, 1.0f);


    static const std::vector<glm::vec3> particleVertices =
    {
        glm::vec3(3.0f, 3.0f, 0.0f),
        glm::vec3(3.0f, -3.0f, 0.0f),
        glm::vec3(-3.0f, -3.0f, 0.0f),
        glm::vec3(-3.0f, 3.0f, 0.0f)
    };
    static const glm::vec3 particleColor(1.0f, 0.5f, 0.0f);


    static const std::vector<glm::vec3> laserVertices =
    {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(15.0f, 0.0f, 0.0f)
    };
    static const glm::vec3 laserColor(0.3f, 0.8f, 1.0f);


    static const std::vector<glm::vec3> asteroidVertices =
    {
        glm::vec3(0, 80, 0),
        glm::vec3(40, 80, 0),
        glm::vec3(80, 40, 0),
        glm::vec3(80, 0, 0),
        glm::vec3(80, -40, 0),
        glm::vec3(40, -80, 0),
        glm::vec3(-40, -80, 0),
        glm::vec3(-80, -40, 0),
        glm::vec3(-80, 40, 0),
        glm::vec3(-40, 80, 0)
    };
    static const glm::vec3 asteroidColor(1.0f, 1.0f, 0.0f);
}
