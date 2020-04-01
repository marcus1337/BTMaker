#include "Evaluator.h"
#include "boost/algorithm/sequence/edit_distance.hpp"

#include <numeric>

int Evaluator::getReward(std::string newSentence) {
    using boost::algorithm::sequence::edit_distance;
    using namespace boost::algorithm::sequence::parameter;
    return maxReward - edit_distance(sentence, newSentence, _substitution = true);
}

void Evaluator::addMissingNoneNodes() {
    int numInterior = 0;
    int numNone = 0;
    for (const auto& n : allNodes) {
        if (n == NodeType::INTERIOR)
            numInterior++;
        if (n == NodeType::NONE)
            numNone++;
    }
}

std::vector<NodeType> Evaluator::convertStackNodesToTypeVector(std::stack<Node> st) {
    std::vector<NodeType> tmpNodeVec;
    Node* endPoint = &st.top() + 1;
    std::vector<Node> tmpNodes = std::vector<Node>(endPoint - st.size(), endPoint);
    for (int i = 0; i < tmpNodes.size(); i++) {
        tmpNodeVec.push_back(tmpNodes[i].type);
    }
    return tmpNodeVec;
}

std::vector<std::set<int>> Evaluator::getEdges() {
    std::vector<std::set<int>> abstractNodes;

    return abstractNodes;
}

void Evaluator::initTreeDataStructures(std::stack<Node> st) {
    allNodes = convertStackNodesToTypeVector(st);
}

int Evaluator::countLeavesWithLimitedActionNodes(std::stack<Node> st) {
    int res = 0;

    return res;
}

int Evaluator::rateTreeTopology(std::stack<Node> st) {
    int score = 0;

    return score;
}