#pragma once

#include <random>
#include "../utils/utils.h"

class Random {
private:
    static std::random_device rd;
    static std::mt19937 mt;
public:
    NODISCARD static int range(int lowerLimit, int upperLimit);
    NODISCARD static double genProbability();
};