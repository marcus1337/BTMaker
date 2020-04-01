#pragma once
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ExpLib3.h"
#include "Leaves.h"
#include "BTMaker.h"
#include <iostream>
#include "Evaluator.h"

using namespace std;


int main()
{
    int maxTreeNodes = 20;

    init(1, maxTreeNodes*2, 50);
    float tmpVal = 1.0f;
    float* tmpVals = &tmpVal;
    calcAll(tmpVals);

    Leaves leaves;
    BTMaker btMaker(maxTreeNodes);
    auto st = btMaker.getTreeStack(getOutput(0));
    std::string xmlTmp = btMaker.getTreeXML(st);
    cout << "OK? " << btMaker.checkValidTreeTopology(st) << ".\n\n";

    while (!st.empty()) {
        std::cout << Node::getTypeStr(st.top().type) << "\n";
        st.pop();
    }
    cout << "\n\n" << xmlTmp << "\n";

    Evaluator evaluator;
    auto factory = leaves.getFactoryWithNodes();
    
    /*std::string xml_text = btMaker.getTreeXML(getOutput(0));
    auto tree = factory.createTreeFromText(xml_text);
    leaves.tickResult.clear();
    tree.root_node->executeTick();
    std::cout << "RESULT: " << evaluator.getReward(leaves.tickResult) << "\n"
        << " _" << leaves.tickResult << "_\n";*/

    return 0;
}

