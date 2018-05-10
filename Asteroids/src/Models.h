#include <glm/gtc/type_ptr.hpp>

#include <vector>


// maybe split into seperate .cpp file if too large

namespace models
{
    static const std::vector<glm::vec3> shipVertices =
    {
        glm::vec3(0.0f, 50.0f, 0.0f),
        glm::vec3(-25.0f, -30.0f, 0.0f),
        glm::vec3(0.0f, -15.0f, 0.0f),
        glm::vec3(25.0f, -30.0f, 0.0f)
    };
    static const glm::vec3 shipColor(1.0f, 1.0f, 1.0f);


    static const std::vector<glm::vec3> particleVertices =
    {
        glm::vec3(3.0f, 3.0f, 0.0f),
        glm::vec3(-3.0f, 3.0f, 0.0f),
        glm::vec3(-3.0f, -3.0f, 0.0f),
        glm::vec3(3.0f, -3.0f, 0.0f)
    };
    static const glm::vec3 particleColor(1.0f, 0.5f, 0.0f);


    static const std::vector<glm::vec3> laserVertices =
    {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 150.0f, 0.0f)
    };
    static const glm::vec3 laserColor(0.3f, 0.8f, 1.0f);


    static const std::vector<glm::vec3> asteroidVertices =
    {
        glm::vec3(0, 20, 0),
        glm::vec3(-20, 40, 0),
        glm::vec3(-40, 20, 0),
        glm::vec3(-40, -20, 0),
        glm::vec3(-20, -40, 0),
        glm::vec3(20, -40, 0),
        glm::vec3(40, -20, 0),
        glm::vec3(20, 0, 0),
        glm::vec3(40, 20, 0),
        glm::vec3(20, 40, 0)
    };
    static const glm::vec3 asteroidColor(1.0f, 1.0f, 0.0f);
}
