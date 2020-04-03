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
    }

    printTree(treeVec);

    //std::string xmlTmp = btMaker.getTreeXML(st);
    //auto factory = leaves.getFactoryWithNodes();
  
    /*std::string xml_text = btMaker.getTreeXML(getOutput(0));
    auto tree = factory.createTreeFromText(xml_text);
    leaves.tickResult.clear();
    tree.root_node->executeTick();
    std::cout << "RESULT: " << evaluator.getReward(leaves.tickResult) << "\n"
        << " _" << leaves.tickResult << "_\n";*/

    return 0;
}

