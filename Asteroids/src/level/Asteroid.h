#pragma once

#include <glm/glm.hpp>

#include <vector>

#include "CollisionObject.h"
#include "Config.h"
#include "GameObject.h"
#include "GPUobject.h"
#include "LevelManager.h"
#include "Transform.h"


class Asteroid : public GameObject
{
public:
    Asteroid(LevelManager& levelManager, Transform& transform, std::vector<glm::vec2> vertices);
    ~Asteroid();

    void initialise() override;
    void move() override;
    void collisionCheck() override;


private:
    void generateHitParticle(glm::vec2 hitPosition, glm::vec2 velocity);
    std::vector<glm::vec2> generateHitPoly(glm::vec2 location, glm::vec2 rotationDirection);


    std::vector<glm::vec2> vertices;

    CollisionObject collisionObject;
};
