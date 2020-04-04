#pragma once
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ExpLib3.h"
#include "Leaves.h"
#include "BTMaker.h"
#include <iostream>
#include "Evaluator.h"

using namespace std;


void printTree(std::vector<Node> treeVec) {
    for (const auto& n : treeVec) {
        std::cout << Node::getTypeStr(n.type) << "\n";
    }
}

int main()
{
    int maxTreeNodes = 20;

    init(1, maxTreeNodes*2, 50);
    float tmpVal = 1.0f;
    float* tmpVals = &tmpVal;
    calcAll(tmpVals);

    Leaves leaves;
    BTMaker btMaker(maxTreeNodes);

    auto treeVec = btMaker.getTreeVector(getOutput(0));
    bool validTree = btMaker.checkValidTreeTopology(treeVec);
    std::cout << "VALID? " << validTree << "\n";

    Evaluator evaluator;
    if (validTree) {
        int treeScore = evaluator.rateTreeTopology(treeVec);
        printTree(treeVec);
    }

    return 0;
}

