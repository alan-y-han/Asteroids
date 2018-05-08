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

    void registerGPUobject(GPUobject* gpuObject);

    InstanceVAs instanceVAs;


private:
    GPUobject* gpuObject;
};
