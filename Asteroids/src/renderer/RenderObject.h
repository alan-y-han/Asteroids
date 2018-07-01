#pragma once

#include "InstanceVertexAttributes.h"
#include "GPUobject.h"


// RenderObject class represents an instance of a GPUobject
class RenderObject
{
public:
    RenderObject();
    RenderObject(GPUobject* gpuObject);
    ~RenderObject();

    GPUobject* getGPUobject();
    void registerGPUobject(GPUobject* gpuObject);
    void clearGPUobject();

    InstanceVAs instanceVAs;


private:
    GPUobject* gpuObject;
};
