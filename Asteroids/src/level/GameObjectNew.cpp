#include "GameObjectNew.h"


GameObjectNew::GameObjectNew(LevelManager& levelManager, GPUobject* gpuObject, Transform transform) :
    levelManager(levelManager),
    transform(transform)
{
    for (int i = 0; i < 9; i++)
    {
        renderObjects[i].registerGPUobject(gpuObject);
    }
}

GameObjectNew::~GameObjectNew()
{
}

void GameObjectNew::initialise()
{
}

void GameObjectNew::move()
{
}

void GameObjectNew::collisionCheck()
{
}
