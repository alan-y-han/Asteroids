#pragma once

#include "GPUobject.h"
#include "LevelManager.h"
#include "RenderObject.h"
#include "Transform.h"

// forward declarations
class CollisionObject;


class GameObject
{
public:
    GameObject(LevelManager& levelManager, GPUobject* gpuObject, Transform transform);
    //GameObject(LevelManager& levelManager, Transform transform);
    virtual ~GameObject();

    // public GameObject functions, to be overriden in derived classes
    virtual void initialise();
    virtual void move();
    virtual void collisionCheck();
    virtual void hit(CollisionObject* collisionObject, glm::vec2 point);

    
    Transform transform;


protected:
    void updateInstanceVAsModelMatrix();

    LevelManager& levelManager;
    RenderObject renderObjects[9];
};

