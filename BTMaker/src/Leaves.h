#pragma once
#include "behaviortree_cpp_v3/behavior_tree.h"
#include <string>
#include <iostream>

class Leaves {
public:
    std::string tickResult;
    //"This is a perfect sentence. This sentence should be in this order.";

    BT::NodeStatus action1() {
        tickResult += "This";
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus action2() {
        tickResult += " ";
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus action3() {
        tickResult += "a";
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus action4() {
        tickResult += "perfect";
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus action5() {
        tickResult += "sentence";
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus action6() {
        tickResult += "perfect";
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus action7() {
        tickResult += "be";
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus action8() {
        tickResult += "in";
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus action9() {
        tickResult += "this";
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus action10() {
        tickResult += "order";
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus action11() {
        tickResult += ".";
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus action12() {
        tickResult += "is";
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus action0() {
        return BT::NodeStatus::SUCCESS;
    }

    BT::BehaviorTreeFactory getFactoryWithNodes() {
        BT::BehaviorTreeFactory factory;
        factory.registerSimpleAction("action0", std::bind(&Leaves::action0, this));
        factory.registerSimpleAction("action1", std::bind(&Leaves::action1, this));
        factory.registerSimpleAction("action2", std::bind(&Leaves::action2, this));
        factory.registerSimpleAction("action3", std::bind(&Leaves::action3, this));
        factory.registerSimpleAction("action4", std::bind(&Leaves::action4, this));
        factory.registerSimpleAction("action5", std::bind(&Leaves::action5, this));
        factory.registerSimpleAction("action6", std::bind(&Leaves::action6, this));
        factory.registerSimpleAction("action7", std::bind(&Leaves::action7, this));
        factory.registerSimpleAction("action8", std::bind(&Leaves::action8, this));
        factory.registerSimpleAction("action9", std::bind(&Leaves::action9, this));
        factory.registerSimpleAction("action10", std::bind(&Leaves::action10, this));
        factory.registerSimpleAction("action11", std::bind(&Leaves::action11, this));
        factory.registerSimpleAction("action12", std::bind(&Leaves::action12, this));
        return factory;
    }


};