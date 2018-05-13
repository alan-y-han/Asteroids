#pragma once

#include "GPUobject.h"
#include "LevelManager.h"
#include "RenderObject.h"
#include "Transform.h"


class GameObject
{
public:
    GameObject(LevelManager& levelManager, GPUobject* gpuObject, Transform transform);
    virtual ~GameObject();

    // public GameObject functions, to be overriden in derived classes
    virtual void initialise();
    virtual void move();
    virtual void collisionCheck();

    
    Transform transform;


protected:
    void updateInstanceVAsModelMatrix();


    LevelManager& levelManager;
    RenderObject renderObjects[9];
};

