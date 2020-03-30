#pragma once
#include "behaviortree_cpp_v3/behavior_tree.h"
#include <string>
#include <iostream>

class Leaves {
public:
    std::string tickResult;

    BT::NodeStatus action1() {
        tickResult += "This";
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus action2() {
        tickResult += " ";
        return BT::NodeStatus::SUCCESS;
    }

    BT::BehaviorTreeFactory getTreeWithRegisteredNodes() {
        BT::BehaviorTreeFactory factory;
        factory.registerSimpleAction("action1", std::bind(&Leaves::action1, this));
        factory.registerSimpleAction("action2", std::bind(&Leaves::action2, this));
        return factory;
    }


};