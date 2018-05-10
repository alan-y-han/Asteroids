#pragma once

#include <glm\gtc\type_ptr.hpp>

#include <vector>

#include "Line.h"
#include "Transform.h"


// forward declarations
class Quadtree;

// Collision mesh of lines is regenerated every frame, and then stuffed into a quadtree
class CollisionObject
{
public:
    CollisionObject();

    void generateMesh(const std::vector<glm::vec3>& vertices, Transform& transform, Quadtree& quadtree);


private:
    void addLineToMesh(int i);
    void addMotionLineToMesh(glm::vec2 vertex, Transform& transform);
    
    void splitLines(std::vector<Line>& unsplitLines);
    void splitLineX(const Line& inputLine);
    void splitLineY(const Line& inputLine);

    glm::vec2 getX(const Line& line, const float x);
    glm::vec2 getY(const Line& line, const float y);

    std::vector<glm::vec2> worldVertices; // persistent memory for vertices transformed to world space
    std::vector<Line> unsplitCollisionMesh; // persistent memory for temporary unsplit lines
    std::vector<Line> collisionMesh; // lines used for collision detection
};
