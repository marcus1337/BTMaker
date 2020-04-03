#include "Evaluator.h"
#include "boost/algorithm/sequence/edit_distance.hpp"

#include <numeric>

int Evaluator::getReward(std::string newSentence) {
    using boost::algorithm::sequence::edit_distance;
    using namespace boost::algorithm::sequence::parameter;
    return maxReward - edit_distance(sentence, newSentence, _substitution = true);
}

std::vector<NodeType> Evaluator::convertNodesToTypes(std::vector<Node> tmpNodes) {
    std::vector<NodeType> tmpNodeVec;
    for (int i = 0; i < tmpNodes.size(); i++)
        tmpNodeVec.push_back(tmpNodes[i].type);
    return tmpNodeVec;
}

std::vector<std::set<int>> Evaluator::getEdges() {
    std::vector<std::set<int>> abstractNodes;

    return abstractNodes;
}

void Evaluator::initTreeDataStructures(std::vector<Node> st) {
    allNodes = convertNodesToTypes(st);
}

int Evaluator::countLeavesWithLimitedActionNodes(std::stack<Node> st) {
    int res = 0;

    return res;
}

int Evaluator::rateTreeTopology(std::vector<Node> st) {
    int score = 0;

    return score;
}