#pragma once

#include <vector>
#include <array>

#include "EventManager.h"
#include "Renderer.h"
#include "RenderObject.h"
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
    //std::vector<Particle> particles;
    Particle* particles[10000];
};
