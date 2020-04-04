#include "Evaluator.h"
#include "boost/algorithm/sequence/edit_distance.hpp"

#include <numeric>
#include <iostream>

int Evaluator::getReward(std::string newSentence) {
    using boost::algorithm::sequence::edit_distance;
    using namespace boost::algorithm::sequence::parameter;
    return maxReward - edit_distance(sentence, newSentence, _substitution = true);
}

std::vector<NodeType> Evaluator::getNodeTypes(std::vector<Node> tmpNodes) {
    std::vector<NodeType> tmpNodeVec;
    for (int i = 0; i < tmpNodes.size(); i++)
        tmpNodeVec.push_back(tmpNodes[i].type);
    return tmpNodeVec;
}

std::vector<std::vector<Node>> Evaluator::getInteriors(std::vector<Node> nodes) {
    std::vector<std::vector<Node>> result;
    std::stack<std::vector<Node>> st;
    st.push(std::vector<Node>());
    st.top().push_back(nodes[0]);

    for (int i = 1; i < nodes.size(); i++) {
        if (nodes[i].type == NodeType::INTERIOR) {
            st.top().push_back(nodes[i]);
            st.push(std::vector<Node>());
        }
        if (nodes[i].type == NodeType::ACTION) {
            st.top().push_back(nodes[i]);
        }
        if (nodes[i].type == NodeType::NONE) {
            result.push_back(st.top());
            st.pop();
        }
    }

    return result;
}

int Evaluator::rateTreeTopology(std::vector<Node> nodes) {
    int score = 10;
    auto interiors = getInteriors(nodes);
    for (const auto& interior : interiors) {
        if (interior.size() == 1 && interior[0].type == NodeType::INTERIOR)
            score -= 7;
    }
    if (interiors.size() >= 2)
        score += 5;

    return score;
}