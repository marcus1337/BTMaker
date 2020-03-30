#pragma once
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ExpLib3.h"
#include "Leaves.h"
#include "BTMaker.h"
#include <iostream>

#include "boost/algorithm/sequence/edit_distance.hpp"

using namespace std;
using boost::algorithm::sequence::edit_distance;
using namespace boost::algorithm::sequence::parameter;

int main()
{
    init(10, 10, 10);

    Leaves leaves;
    BTMaker btMaker;
    auto factory = leaves.getTreeWithRegisteredNodes();

    auto tree = factory.createTreeFromText(btMaker.getTreeXML(getOutput(0)));

    leaves.tickResult.clear();
    tree.root_node->executeTick();
    std::cout << "RESULT: |" << leaves.tickResult << "|\n";


    char const* str1 = "abc";
    char const* str2 = "abC";
    int dist = edit_distance(str1, str2, _substitution = true);
    std::cout << "The edit distance be twee \"" << str1 << "\" and \"" << str2 << "\" = " << dist << "\n";

    return 0;
}

