#pragma once

#include <glm\glm.hpp>

#include <vector>
#include <unordered_map>

#include "Line.h"
#include "Transform.h"


// forward declarations
class Quadtree;

class SliceObject
{
public:
    SliceObject(std::vector<glm::vec2>& vertices);
    //SliceObject(std::vector<glm::vec2>& vertices, Transform& transform);

    void addMeshToQuadtree(Quadtree& quadtree);
    std::unordered_map<Line*, std::vector<std::pair<glm::vec2, Line*>>> getCollisions(Quadtree& quadtree);

    std::vector<Line> collisionMesh;


private:
    bool checkLineLineCollision(Line& a, Line& b, glm::vec2& inCollisionPoint);
    

};