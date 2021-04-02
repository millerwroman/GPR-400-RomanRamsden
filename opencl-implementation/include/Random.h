#pragma once

// #include <random>

//static std::mt19937 s_mersenneTwisterRand(std::mt19937::default_seed);
//
//void SetRandomSeed(const unsigned int aSeed)
//{
//    s_mersenneTwisterRand.seed(static_cast<std::mt19937::result_type>(aSeed));
//}
//
//unsigned int GetRandomUInt32()
//{
//    return s_mersenneTwisterRand();
//}

inline float GetRandomFloat32()
{
    return (float)rand() / (float)0xFFFFFFFF;
    //return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

inline float GetRandomFloat32_Range(float aMin, float aMax)
{
    // unsigned int randomValue = GetRandomUInt32();
    return aMin + (float)rand() * (aMax - aMin) / 4294967295.0f;
}