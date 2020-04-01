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

    std::vector<NodeType> convertStackNodesToTypeVector(std::stack<Node> st);

    std::vector<std::set<int>> getEdges();

    void initTreeDataStructures(std::stack<Node> st);

    int countLeavesWithLimitedActionNodes(std::stack<Node> st);

    int rateTreeTopology(std::stack<Node> st);

};