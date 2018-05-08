#pragma once

#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Config.h"
#include "GameObjectNew.h"
#include "GPUobject.h"
#include "LevelManager.h"
#include "Transform.h"


class Asteroid : public GameObjectNew
{
public:
    Asteroid(
        LevelManager& levelManager,
        Transform& transform
    );
    ~Asteroid();

    virtual void initialise();
    virtual void move();
};
