#include "RNG.h"

std::random_device RNG::rd;
std::mt19937 RNG::random_engine(rd());


float RNG::randFloat(float min, float max)
{
    return std::uniform_real_distribution<float>{min, max}(random_engine);
}
