#pragma once

#include <vector>

#include "EventManager.h"
#include "Renderer.h"
#include "RenderObject.h"
#include "Ship.h"


class LevelManager
{
public:
    KeyEventManager keyEventManager;
    
    LevelManager(Renderer& renderer);
    void initialiseLevel();
    void tick();



private:
    Renderer& renderer;
    TickEventManager tickEventManager;
    Ship ship;
};
