#include <glm/glm.hpp>

#include <vector>
#include <unordered_set>

#include "RNG.h"

// debug
#include <iostream>


// Forward-facing direction is along X axis

// N.B. all model vertices must be defined clockwise
// (requried for mesh cutting function to work)

namespace models
{
    static const std::vector<glm::vec2> shipVertices =
    {
        glm::vec2(50.0f, 0.0f),
        glm::vec2(-30.0f, 25.0f),
        glm::vec2(-15.0f, 0.0f),
        glm::vec2(-30.0f, -25.0f)
    };
    static const glm::vec3 shipColor(1.0f, 1.0f, 1.0f);


    static const std::vector<glm::vec2> particleVertices =
    {
        glm::vec2(3.0f, 3.0f),
        glm::vec2(3.0f, -3.0f),
        glm::vec2(-3.0f, -3.0f),
        glm::vec2(-3.0f, 3.0f)
    };
    static const glm::vec3 particleColor(1.0f, 0.5f, 0.0f);


    static const std::vector<glm::vec2> laserVertices =
    {
        glm::vec2(0.0f, 0.0f),
        glm::vec2(15.0f, 0.0f)
    };
    static const glm::vec3 laserColor(0.3f, 0.8f, 1.0f);


    static const std::vector<glm::vec2> asteroidVertices =
    {
        glm::vec2(0, 80),
        glm::vec2(40, 80),
        glm::vec2(80, 40),
        glm::vec2(80, 0),
        glm::vec2(80, -40),
        glm::vec2(40, -80),
        glm::vec2(-40, -80),
        glm::vec2(-80, -40),
        glm::vec2(-80, 40),
        glm::vec2(-40, 80)
    };
    static const glm::vec3 asteroidColor(1.0f, 1.0f, 0.0f);


    static const std::vector<glm::vec2> testCubeVertices =
    {
        glm::vec2(-200, -200),
        glm::vec2(-200, 200),
        glm::vec2(200, 200),
        glm::vec2(200, -200)
    };


    static std::vector<glm::vec2> randomAsteroid()
    {
        std::vector<glm::vec2> vertices;

        //for (int targetIntPointIndex = 0; targetIntPointIndex < 10; targetIntPointIndex++)
        //{
        //    float angle = RNG::randFloat()
        //}
    }

    static std::vector<std::vector<glm::vec2>> cutMesh(
        std::vector<glm::vec2> target,
        std::vector<int> targetToClip,
        std::vector<glm::vec2> clip,
        std::vector<int> clipToTarget
    )
    {
        std::vector<std::vector<glm::vec2>> newPolygons;

        // Part 1 - find inbound vertices
        // (these are intersections which point into the clip polygon)

        std::unordered_set<int> targetInbound_is;

        for (int i = 0; i < static_cast<int>(targetToClip.size()); i++)
        {
            if (targetToClip[i] != -1)
            {
                glm::vec2 target1 = target[i];
                glm::vec2 target2 = target[(i + 1) % target.size()];
                glm::vec2 targetLine = target2 - target1;

                // corresponding intersection vertex in clip
                int clip_i = targetToClip[i];

                glm::vec2 clip1 = clip[clip_i];
                glm::vec2 clip2 = clip[(clip_i + 1) % clip.size()];
                glm::vec2 clipLine = clip2 - clip1;

                glm::vec2 clipLineInvNormal(clipLine.y, -clipLine.x);

                // if target line is pointing into clip polygon
                if (glm::dot(targetLine, clipLineInvNormal) > 0.0f)
                {
                    targetInbound_is.insert(i);
                }
            }
        }

        if (!targetInbound_is.size())
        {
            newPolygons.push_back(target);
            return newPolygons;
        }


        // Part 2 - generate new polygons
        
        // while there are inbound vertices
        while (targetInbound_is.size())
        {
            std::vector<glm::vec2> newPolygon;

            // get A vertex from the inbound vertex set
            int targetInboundStart_i = *targetInbound_is.begin();
            int target_i = targetInboundStart_i;

            do
            {
                // get the corresponding clip vertex index
                int clip_i = targetToClip[target_i];

                // add vertex to newPolygon
                // then break if vertex is intersection point
                do
                {
                    clip_i--;

                    if (clip_i < 0)
                    {
                        clip_i += clip.size();
                    }

                    newPolygon.push_back(clip[clip_i]);
                } while (clipToTarget[clip_i] == -1);


                target_i = clipToTarget[clip_i];

                do
                {
                    target_i++;

                    if (target_i == target.size())
                    {
                        target_i -= target.size();
                    }

                    newPolygon.push_back(target[target_i]);
                } while (targetToClip[target_i] == -1);

                // remove from the list of inbound vertices
                // the target intersection vertex we just reached
                // (and just added to newPolygon)

                targetInbound_is.erase(target_i);

            } while (targetInboundStart_i != target_i);

            newPolygons.push_back(newPolygon);
        }

        return newPolygons;
    }

    static glm::vec2 getCentroid(std::vector<glm::vec2> v, float& A)
    {
        float cx = 0;
        float cy = 0;
        //float A = 0;

        for (int i = 0; i < v.size(); ++i)
        {
            glm::vec2& v1 = v[i];
            glm::vec2& v2 = v[(i + 1) % v.size()];
            float almostA = ((v1.x * v2.y) - (v2.x * v1.y));
            A += almostA;
            cx += (v1.x + v2.x) * almostA;
            cy += (v1.y + v2.y) * almostA;
        }

        A /= 2;
        cx /= 6 * A;
        cy /= 6 * A;

        return glm::vec2(cx, cy);
    }
}
