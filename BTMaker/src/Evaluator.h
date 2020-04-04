#pragma once

#include <stack>
#include <string>
#include <set>
#include "NodeInfo.h"
#include <vector>

class Evaluator {
public:
    std::string sentence = "This is a perfect sentence. This sentence should be in this order.";
    int maxReward = 200;

    int getReward(std::string newSentence);

    std::vector<NodeType> getNodeTypes(std::vector<Node> tmpNodes);
    std::vector<std::vector<Node>> getInteriors(std::vector<Node> tmpNodes);

    int rateTreeTopology(std::vector<Node> st);


};