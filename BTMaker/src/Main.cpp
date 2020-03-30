#pragma once
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ExpLib3.h"
#include "Leaves.h"
#include "BTMaker.h"
#include <iostream>

using namespace std;

int main()
{
    init(10, 10, 10);

    Leaves leaves;
    BTMaker btMaker;
    auto factory = leaves.getTreeWithRegisteredNodes();
    auto tree = factory.createTreeFromText(btMaker.getSampleTree());

    leaves.tickResult.clear();
    tree.root_node->executeTick();
    std::cout << "RESULT122: |" << leaves.tickResult << "|\n";

    return 0;
}

