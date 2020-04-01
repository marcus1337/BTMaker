#include "Evaluator.h"
#include "boost/algorithm/sequence/edit_distance.hpp"


int Evaluator::getReward(std::string newSentence) {
    using boost::algorithm::sequence::edit_distance;
    using namespace boost::algorithm::sequence::parameter;
    return maxReward - edit_distance(sentence, newSentence, _substitution = true);
}