#pragma once
#include <random>


class RNG
{
public:
    static float randFloat(float min, float max);


private:
    static std::random_device rd;
    static std::mt19937 random_engine;
};
