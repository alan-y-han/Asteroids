#include "Asteroid.h"
#include <algorithm>
#include <cmath>
#include "GPUobjectManager.h"
#include "Models.h"
#include "RNG.h"
#include "Particle.h"
#include "SliceObject.h"
#include "Quadtree.h"
#include <unordered_set>


Asteroid::Asteroid(LevelManager & levelManager, Transform & transform, std::vector<glm::vec2> vertices) :
    GameObject(
        levelManager,
        levelManager.gpuObjectManager.createObject(vertices, models::asteroidColor),
        transform
    ),
    vertices(vertices),
    collisionObject(*this)
{
}

Asteroid::~Asteroid()
{
    GPUobject* toDelete = renderObjects[0].getGPUobject();
    for (int i = 0; i < 9; i++)
    {
        renderObjects[i].clearGPUobject();
    }
    levelManager.gpuObjectManager.deleteObject(toDelete);
    levelManager.asteroids.erase(this);
}

void Asteroid::initialise()
{
    levelManager.asteroids.insert(this);
}

void Asteroid::move()
{
    transform.applyVelocities();
    updateInstanceVAsModelMatrix();

    collisionObject.generateMesh(vertices, transform);
    collisionObject.addMeshToQuadtree(levelManager.asteroidQuadtree);
}

void Asteroid::collisionCheck()
{
    std::unordered_map<CollisionObject*, std::vector<glm::vec2>> collisions = collisionObject.getCollisions(levelManager.laserQuadtree);

    std::vector<std::pair<glm::vec2, glm::vec2>> chunkLocations;
    glm::mat4 modelInverse = glm::inverse(transform.getModelMatrix(0, 0));

    for (std::pair<CollisionObject*, std::vector<glm::vec2>> objectCollisionList : collisions)
    {
        std::vector<glm::vec2>& collisionPoints = objectCollisionList.second;

        for (glm::vec2& collisionPoint : collisionPoints)
        {
            generateHitParticle(collisionPoint, -(objectCollisionList.first->gameObject.transform.velocity * glm::vec2(0.2f)));
            objectCollisionList.first->gameObject.hit(&collisionObject, collisionPoint);

            // TODO: make neater
            glm::mat4 rotInverse = glm::inverse(transform.getRotationMatrix());

            chunkLocations.emplace_back(
                modelInverse * glm::vec4(collisionPoint, 0.0f, 1.0f),
                rotInverse * glm::vec4(objectCollisionList.first->gameObject.transform.velocity, 0.0f, 1.0f)
            );

            break; // only hit object once
        }
    }

    // return if no collisions
    if (!chunkLocations.size())
    {
        return;
    }

    std::vector<std::vector<glm::vec2>> asteroidPolys; // list of asteroid polygons to slice against
    std::vector<std::vector<glm::vec2>> newAsteroidPolys; // list of asteroid polygons generated during slicing
    newAsteroidPolys.push_back(vertices); // insert current asteroid

    Quadtree asteroidPolyQT{ iRectangle(-config::SCR_WIDTH, -config::SCR_HEIGHT, config::SCR_WIDTH, config::SCR_HEIGHT), 1, 1 }; // TODO: optimise

    // TODO: check for edge cases, where chunk edge exactly overlaps with asteroid edge

    // slice at each hit location
    for (std::pair<glm::vec2, glm::vec2>& chunkLocation : chunkLocations)
    {
        std::vector<glm::vec2> chunkVertices = generateHitPoly(chunkLocation.first, chunkLocation.second);
        SliceObject chunkSO(chunkVertices);

        asteroidPolys = newAsteroidPolys;
        newAsteroidPolys.clear();

        for (std::vector<glm::vec2>& asteroidPoly : asteroidPolys)
        {
            SliceObject asteroidPolySO(asteroidPoly);

            asteroidPolyQT.clear();
            asteroidPolySO.addMeshToQuadtree(asteroidPolyQT);

            std::unordered_map<Line*, std::vector<std::pair<glm::vec2, Line*>>> chunkAsteroidCollisions = chunkSO.getCollisions(asteroidPolyQT);

            // build list of target vertices

            std::vector<glm::vec2> target;
            std::unordered_map<Line*, std::vector<std::pair<glm::vec2, int>>> asteroidLinesTagged;

            for (Line& chunkSOline : chunkSO.collisionMesh)
            {
                // insert vertex
                glm::vec2 closestPoint = chunkSOline.p1;

                target.push_back(closestPoint);

                if (chunkAsteroidCollisions.count(&chunkSOline))
                {
                    // line has collisions, insert more vertices

                    // get collisions along line
                    std::vector<std::pair<glm::vec2, Line*>>& collisionPoints = chunkAsteroidCollisions[&chunkSOline];

                    // sort collisionPoints by distance to closestPoint
                    // TODO maybe optimise: speed up sorting by caching distance to closestPoint
                    auto compFunc = [&closestPoint](std::pair<glm::vec2, Line*> a, std::pair<glm::vec2, Line*> b)
                    {
                        glm::vec2 aVec = a.first - closestPoint;
                        glm::vec2 bVec = b.first - closestPoint;
                        float aDist = pow(aVec.x, 2) + pow(aVec.y, 2);
                        float bDist = pow(bVec.x, 2) + pow(bVec.y, 2);
                        return aDist < bDist;
                    };

                    std::sort(std::begin(collisionPoints), std::end(collisionPoints), compFunc);

                    for (std::pair<glm::vec2, Line*>& collisionPoint : collisionPoints)
                    {
                        target.push_back(collisionPoint.first);
                        asteroidLinesTagged[collisionPoint.second].emplace_back(collisionPoint.first, target.size() - 1);
                    }

                }
            }

            std::vector<int> targetToClip(target.size(), -1);

            // build list of clip vertices

            std::vector<glm::vec2> clip;
            std::vector<int> clipToTarget;

            for (Line& asteroidSOline : asteroidPolySO.collisionMesh)
            {
                glm::vec2 closestPoint = asteroidSOline.p1;

                clip.push_back(closestPoint);
                clipToTarget.push_back(-1);

                if (asteroidLinesTagged.count(&asteroidSOline))
                {
                    std::vector<std::pair<glm::vec2, int>>& asteroidLineTagged = asteroidLinesTagged[&asteroidSOline];

                    auto compFunc = [&closestPoint](std::pair<glm::vec2, int> a, std::pair<glm::vec2, int> b)
                    {
                        glm::vec2 aVec = a.first - closestPoint;
                        glm::vec2 bVec = b.first - closestPoint;
                        float aDist = pow(aVec.x, 2) + pow(aVec.y, 2);
                        float bDist = pow(bVec.x, 2) + pow(bVec.y, 2);
                        return aDist < bDist;
                    };
                    
                    std::sort(std::begin(asteroidLineTagged), std::end(asteroidLineTagged), compFunc);

                    for (std::pair<glm::vec2, int>& collisionPoint : asteroidLineTagged)
                    {
                        clip.push_back(collisionPoint.first);
                        clipToTarget.push_back(collisionPoint.second);
                        targetToClip[collisionPoint.second] = clip.size() - 1;
                    }
                }

            }




            std::vector<std::vector<glm::vec2>> asteroidFragments = models::cutMesh(clip, clipToTarget, target, targetToClip);

            newAsteroidPolys.insert(std::end(newAsteroidPolys), std::begin(asteroidFragments), std::end(asteroidFragments));
        }
    }

    // generate new asteroids from newAsteroidPolys

    for (std::vector<glm::vec2> newAsteroidPoly : newAsteroidPolys)
    {
        float area(0.0f);
        glm::vec2 centreOffset = models::getCentroid(newAsteroidPoly, area);

        if (abs(area) < 100)
        {
            continue;
        }

        glm::vec3 omega(0.0f, 0.0f, glm::radians(transform.aVelocity));

        // velocity obtained from rotational velocity
        glm::vec2 extraVelocity = glm::cross(omega, glm::vec3(centreOffset, 0.0f));

        for (glm::vec2& vertex : newAsteroidPoly)
        {
            vertex -= centreOffset;
        }


        Transform newTransform = transform;

        newTransform.position = transform.getModelMatrix(0, 0) * glm::vec4(centreOffset, 0.0f, 1.0f);
        newTransform.velocity += glm::vec2(transform.getRotationMatrix() * glm::vec4(extraVelocity, 0.0f, 1.0f));

        newTransform.needsNewMatrix = true;

        levelManager.addGameObject(new Asteroid
        (
            levelManager,
            newTransform,
            newAsteroidPoly
        ));
    }

    levelManager.removeGameObject(this);
}

void Asteroid::generateHitParticle(glm::vec2 hitPosition, glm::vec2 velocity)
{
    glm::vec2 particlePos(RNG::randFloat(-1.0f, 1.0f), RNG::randFloat(-1.0f, 1.0f));
    float dvx = RNG::randFloat(-2, 2);
    float dvy = -RNG::randFloat(-2, 2);

    glm::vec2 particleVelRand(dvx, dvy);

    levelManager.addGameObject(new Particle
    (
        levelManager,
        Transform(
            hitPosition + particlePos,
            RNG::randFloat(0, 360),
            transform.velocity + velocity + particleVelRand,
            RNG::randFloat(-2, 2)
        ),
        15
    ));
}

// TODO: randomise
std::vector<glm::vec2> Asteroid::generateHitPoly(glm::vec2 location, glm::vec2 rotationDirection)
{
    //return std::vector<glm::vec2>{
    //    glm::vec2(location.x - 8, location.y - 180),
    //    glm::vec2(location.x - 8, location.y + 8),
    //    glm::vec2(location.x + 8, location.y + 8),
    //    glm::vec2(location.x + 8, location.y - 180),
    //};

    //std::vector<glm::vec2> vertices{
    //    glm::vec2(location.x - 8, location.y - 8),
    //    glm::vec2(location.x - 8, location.y + 8),
    //    glm::vec2(location.x + 8, location.y + 8),
    //    glm::vec2(location.x + 8, location.y - 8),
    //};

    //std::vector<glm::vec2> vertices{
    //    glm::vec2(300, 10),
    //    glm::vec2(300, -10),
    //    glm::vec2(-10, -10),
    //    glm::vec2(-10, 10)
    //};

    float minSize = 5.0f;
    float maxSize = 15.0f;

    std::vector<glm::vec2> vertices = {
        glm::vec2(- RNG::randFloat(minSize, maxSize), - RNG::randFloat(minSize, maxSize)),
        glm::vec2(- RNG::randFloat(minSize, maxSize), + RNG::randFloat(minSize, maxSize)),
        glm::vec2(+ RNG::randFloat(minSize, maxSize), + RNG::randFloat(minSize, maxSize)),
        glm::vec2(+ RNG::randFloat(minSize, maxSize), - RNG::randFloat(minSize, maxSize))
    };

    glm::vec2 normRot = glm::normalize(rotationDirection);

    glm::mat4 rotMatrix;

    rotMatrix[0][0] = normRot.x;
    rotMatrix[1][0] = -normRot.y;
    rotMatrix[0][1] = normRot.y;
    rotMatrix[1][1] = normRot.x;

    for (glm::vec2& vertex : vertices)
    {
        vertex = rotMatrix * glm::vec4(vertex, 0.0f, 1.0f);
        vertex += location;
    }

    return vertices;
}
