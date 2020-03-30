#pragma once
#include <string>
#include "boost/algorithm/sequence/edit_distance.hpp"

class Evaluator {
public:
    std::string sentence = "This is a perfect sentence. This sentence should be in this order.";
    int maxReward = 200;

    int getReward(std::string newSentence) {
        using boost::algorithm::sequence::edit_distance;
        using namespace boost::algorithm::sequence::parameter;
        return maxReward - edit_distance(sentence, newSentence, _substitution = true);
    }

};