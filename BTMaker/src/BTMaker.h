#pragma once
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include "NodeInfo.h"

class BTMaker {
public:
    const int maxNodes;
    BTMaker(int _maxNodes) : maxNodes(_maxNodes) {
    }

    std::vector<std::string> interiorNodes = { "Sequence" , "Fallback" };
    std::vector<std::string> decoratorNodes = { "Inverter" };
    std::vector<std::string> actionNodes = { "action1", "action2", "action3",
    "action4", "action5", "action6", "action7", "action8", "action9",
    "action10", "action11", "action12" };

    std::string xml_text = "<root main_tree_to_execute = \"MainTree\" >"
        "<BehaviorTree ID=\"MainTree\">"
        "<Sequence>"
        "<action1/>"
        "<action2/>"
        "</Sequence>"
        "</BehaviorTree>"
        "</root>";

    void beginning(std::string& str) {
        str += "<root main_tree_to_execute = \"MainTree\" >"
            "<BehaviorTree ID=\"MainTree\">";
    }

    void ending(std::string& str) {
        str += "</BehaviorTree>"
            "</root>";
    }

    void startInterior(std::string& str, std::string interiorID) {
        str += "<" + interiorID + ">";
    }

    void endInterior(std::string& str, std::string interiorID) {
        str += "</" + interiorID + ">";
    }

    void action(std::string& str, std::string actionID) {
        str += "<" + actionID + "/>";
    }

    std::string getSampleTree() {
        std::string tmpText;
        beginning(tmpText);
        startInterior(tmpText, interiorNodes[0]);
        action(tmpText, actionNodes[0]);
        action(tmpText, actionNodes[1]);
        endInterior(tmpText, interiorNodes[0]);
        ending(tmpText);
        return tmpText;
    }

    void standardStart(std::string& str) {
        beginning(str);
        startInterior(str, interiorNodes[0]);
    }
    void standardEnd(std::string& str) {
        endInterior(str, interiorNodes[0]);
        ending(str);
    }

    std::string getTreeXML(std::stack<Node> st) {
        std::string result;
        standardStart(result);
        int level = 0;
        std::stack<std::string> unclosedInteriors;
        while (!st.empty() && level >= 0) {
            NodeType type = st.top().type;
            int IDNum = st.top().IDNumber;
            if (type == NodeType::NONE) {
                level--;
                if (level >= 0) {
                    endInterior(result, unclosedInteriors.top());
                    unclosedInteriors.pop();
                }
            }
            if (type == NodeType::ACTION)
                action(result, actionNodes[IDNum]);
            if (type == NodeType::INTERIOR) {
                startInterior(result, interiorNodes[IDNum]);
                unclosedInteriors.push(interiorNodes[IDNum]);
                level++;
            }
            st.pop();
        }
        while (!unclosedInteriors.empty()) {
            endInterior(result, unclosedInteriors.top());
            unclosedInteriors.pop();
        }

        standardEnd(result);
        return result;
    }

    NodeType classifyNodeType(float value) {
        if (value < 0.33)
            return NodeType::NONE;
        if (value < 0.66)
            return NodeType::ACTION;
        return NodeType::INTERIOR;
    }

    int classifyNodeID(float value, NodeType nodeType) {
        float result = 0;
        value = std::clamp(value, 0.f, 0.99f);
        if (nodeType == NodeType::ACTION)
            result = value * actionNodes.size();
        if (nodeType == NodeType::INTERIOR)
            result = value * interiorNodes.size();
        return result;
    }

    std::stack<Node> getTreeStack(float* NNOutput) {
        std::stack<Node> result;
        for (int i = 0; i < maxNodes; i += 2) {
            NodeType nodeType = classifyNodeType(NNOutput[i]);
            int IDNum = classifyNodeID(NNOutput[i+1], nodeType);
            result.push(Node(nodeType,IDNum));
        }
        return result;
    }

    std::string getTreeXML(float* NNOutput) {
        std::string result;
        beginning(result);
        startInterior(result, interiorNodes[0]);
        action(result, "action0");
        action(result, "action0");
        endInterior(result, interiorNodes[0]);
        ending(result);
        return result;
    }


};