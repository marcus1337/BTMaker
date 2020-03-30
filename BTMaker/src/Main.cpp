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
    init(10, 10, 10);

    Leaves leaves;
    BTMaker btMaker;
    Evaluator evaluator;
    auto factory = leaves.getTreeWithRegisteredNodes();
    
    std::string xml_text = btMaker.getTreeXML(getOutput(0));
    auto tree = factory.createTreeFromText(xml_text);

    leaves.tickResult.clear();
    tree.root_node->executeTick();
    std::cout << "RESULT: " << evaluator.getReward(leaves.tickResult) << "\n"
        << " _" << leaves.tickResult << "_\n";

    return 0;
}

