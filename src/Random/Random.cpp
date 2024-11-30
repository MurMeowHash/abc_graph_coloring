#include "Random.h"

std::random_device Random::rd;
std::mt19937 Random::mt(rd());

int Random::range(int lowerLimit, int upperLimit) {
    std::uniform_int_distribution<int> dist{lowerLimit, upperLimit};
    return dist(mt);
}

double Random::genProbability() {
    std::uniform_real_distribution<double> dist{0.0, 1.0};
    return dist(mt);
}