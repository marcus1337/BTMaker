#pragma once
#include <string>

class Evaluator {
public:
    std::string sentence = "This is a perfect sentence. This sentence should be in this order.";
    int maxReward = 200;

    int getReward(std::string newSentence);

};