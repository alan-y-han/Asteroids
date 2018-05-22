#pragma once

#include <glm\glm.hpp>

#include <vector>
#include <unordered_map>

#include "Line.h"
#include "Transform.h"


// forward declarations
class GameObject;
class Quadtree;

// Collision mesh of lines is regenerated every frame with generateMesh()
// and then stuffed into a quadtree with addMeshToQuadtree()
class CollisionObject
{
public:
    CollisionObject(GameObject& gameObject);

    void generateMesh(const std::vector<glm::vec2>& vertices, Transform& transform);
    void addMeshToQuadtree(Quadtree& quadtree);


    GameObject& gameObject;

    std::unordered_map<CollisionObject*, std::vector<glm::vec2>> getCollisions(Quadtree& quadtree);


private:
    void addLineToMesh(int i);
    void addMotionLineToMesh(glm::vec2 vertex, Transform& transform);
    
    void splitLines(const std::vector<Line>& unsplitLines);
    void splitLineX(const Line& inputLine);
    void splitLineY(const Line& inputLine);

    glm::vec2 getX(const Line& line, const float x);
    glm::vec2 getY(const Line& line, const float y);

    bool checkLineLineCollision(Line& a, Line& b, glm::vec2& inCollisionPoint);


    std::vector<glm::vec2> worldVertices; // persistent memory for vertices transformed to world space
    std::vector<Line> unsplitCollisionMesh; // persistent memory for temporary unsplit lines
    std::vector<Line> collisionMesh; // lines used for collision detection
};
