#include "GameObject.h"


GameObject::GameObject(LevelManager& levelManager, GPUobject* gpuObject, Transform transform) :
    levelManager(levelManager),
    transform(transform)
{
    for (int i = 0; i < 9; i++)
    {
        renderObjects[i].registerGPUobject(gpuObject);
    }
    updateInstanceVAsModelMatrix();
}

//GameObject::GameObject(LevelManager & levelManager, Transform transform) :
//    levelManager(levelManager),
//    transform(transform)
//{
//    updateInstanceVAsModelMatrix();
//}

GameObject::~GameObject()
{
}

void GameObject::initialise()
{
}

void GameObject::move()
{
}

void GameObject::collisionCheck()
{
}

void GameObject::hit(CollisionObject* collisionObject, glm::vec2 point)
{
}

void GameObject::updateInstanceVAsModelMatrix()
{
    int count = 0;
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            renderObjects[count].instanceVAs.modelMatrix = transform.getModelMatrix(x, y);
            count++;
        }
    }
}
