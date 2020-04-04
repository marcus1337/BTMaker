#pragma once
#include <vector>
#include <numeric>
#include <algorithm>

struct FitnessInfo {
    int highest;
    int lowest;
    float average;
    std::vector<float> fitnessValues;

    void calculateAverageFitness() {
        average = 0.0f;
        if (!fitnessValues.empty())
            average = accumulate(fitnessValues.begin(), fitnessValues.end(), 0.0) / fitnessValues.size();
    }

    void calculateFitness() {
        calculateAverageFitness();
        lowest = *std::min_element(fitnessValues.begin(), fitnessValues.end());
        highest = *std::max_element(fitnessValues.begin(), fitnessValues.end());
    }
};