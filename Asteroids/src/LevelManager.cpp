#include "LevelManager.h"

LevelManager::LevelManager()
{
}

void LevelManager::addRenderObject(RenderObject renderObject)
{
    renderObjects.push_back(renderObject);
}

void LevelManager::tick()
{
    for (RenderObject& ro : renderObjects)
    {
        ro.position += ro.velocity;
    }
}
