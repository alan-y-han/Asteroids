#pragma once
#include <glad\glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <unordered_set>

#include "InstanceVertexAttributes.h"


class GPUobject
{
public:
    GPUobject(std::vector<glm::vec3> vertices, glm::vec3 color);
    ~GPUobject();
    
    void addInstance(InstanceVAs* renderObject);
    void removeInstance(InstanceVAs* renderObject);
    void draw();


    unsigned int VAO;


private:
    unsigned int VBO;
    unsigned int instanceVBO;
    unsigned int noOfVertices;

    std::unordered_set<InstanceVAs*> instances;
    std::vector<InstanceVAs> instanceVAsTemp; // used to assemble instanceVAs data to upload to the GPU
};
