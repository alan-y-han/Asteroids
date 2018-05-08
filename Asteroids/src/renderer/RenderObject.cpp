#include "RenderObject.h"


RenderObject::RenderObject() :
    gpuObject(NULL)
{
}

RenderObject::RenderObject(GPUobject* gpuObject) :
    gpuObject(gpuObject)
{
    gpuObject->addInstance(&instanceVAs);
}

RenderObject::~RenderObject()
{
    if (gpuObject != NULL)
    {
        gpuObject->removeInstance(&instanceVAs);
    }
}

void RenderObject::registerGPUobject(GPUobject * gpuObject)
{
    if (gpuObject != NULL)
    {
        gpuObject->removeInstance(&instanceVAs);
    }

    this->gpuObject = gpuObject;
    gpuObject->addInstance(&instanceVAs);
}
