#pragma once

#include "GPUobject.h"
#include "LevelManager.h"
#include "RenderObject.h"
#include "Transform.h"


class GameObjectNew
{
public:
    GameObjectNew(LevelManager& levelManager, GPUobject* gpuObject, Transform transform);
    virtual ~GameObjectNew();

    // public GameObject functions, to be overriden in derived classes
    virtual void initialise();
    virtual void move();
    virtual void collisionCheck();

protected:
    LevelManager& levelManager;
    RenderObject renderObjects[9];

    Transform transform;
};

