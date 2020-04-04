#pragma once
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ExpLib3.h"
#include "Leaves.h"
#include "BTMaker.h"
#include <iostream>
#include "Evaluator.h"
#include <numeric>
#include "FitnessInfo.h"
#include "Trainer.h"

using namespace std;


void printTree(std::vector<Node> treeVec) {
    for (const auto& n : treeVec) {
        std::cout << Node::getTypeStr(n.type) << "\n";
    }
}

int main()
{
    float* someInput = new float[1]{ 1.0f };
    int numAI = 200;
    int maxTreeNodes = 20;

    init(1, maxTreeNodes*2, numAI);

    Leaves leaves;
    BTMaker btMaker(maxTreeNodes);
    Evaluator evaluator;
    Trainer trainer;

    for (int i = 0; i < 30; i++) {
        std::cout << "Generation: " << (i + 1) << "\n";
        trainer.testTrees(btMaker, evaluator, someInput, numAI);
    }

    trainer.printAllFitness();
    auto treeVec = btMaker.getTreeVector(getOutput(0));
    printTree(treeVec);
    return 0;
}

