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

    //std::set<int> edges;
    std::vector<std::set<int>> interiors;
    std::vector<NodeType> allNodes;

    void addMissingNoneNodes();

    std::vector<NodeType> convertNodesToTypes(std::vector<Node> tmpNodes);

    std::vector<std::set<int>> getEdges();

    void initTreeDataStructures(std::vector<Node> st);

    int countLeavesWithLimitedActionNodes(std::stack<Node> st);

    int rateTreeTopology(std::vector<Node> st);

};