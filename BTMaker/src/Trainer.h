#pragma once
#include "FitnessInfo.h"
#include "BTMaker.h"
#include "Evaluator.h"
#include "ExpLib3.h"
#include <iostream>

class Trainer {
public:

    std::vector<FitnessInfo> allFitnessValues;

    void testTrees(BTMaker& btMaker, Evaluator& evaluator, float* someInput, int numAI) {
        allFitnessValues.push_back(FitnessInfo());
        calcAll(someInput);
        for (int i = 0; i < numAI; i++) {
            auto treeVec = btMaker.getTreeVector(getOutput(i));
            bool validTree = btMaker.checkValidTreeTopology(treeVec);
            int treeScore = 0;
            if (validTree)
                treeScore += evaluator.rateTreeTopology(treeVec);
            else
                treeScore -= 20;
            setFitness(i, treeScore);
            allFitnessValues[allFitnessValues.size() - 1].fitnessValues.push_back(treeScore);
        }
        evolve();
        allFitnessValues[allFitnessValues.size() - 1].calculateFitness();
    }

    void printAllFitness() {
        for (int i = 0; i < allFitnessValues.size(); i++) {
            std::cout << allFitnessValues[i].average << " [" << allFitnessValues[i].lowest << "," <<
                allFitnessValues[i].highest << "] \n";
        }
    }

};