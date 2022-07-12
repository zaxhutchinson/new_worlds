#pragma once

#include<random>

using RNG = std::mt19937_64;

namespace rnd {

    inline RNG rng;

    void InitRandom();

    int64_t d0N(int64_t N, int64_t num_dice=1);
    int64_t d1N(int64_t N, int64_t num_dice=1);
}