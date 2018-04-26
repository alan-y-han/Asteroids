#pragma once

#include <vector>
#include <array>

#include "EventManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Ship.h"
#include "Particle.h"


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
    Particle* particles[30000];
};
