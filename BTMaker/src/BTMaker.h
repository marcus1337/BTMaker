#pragma once
#include <string>
#include <vector>
#include <stack>
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

    std::string getTreeXML(std::stack<Node> st) {
        std::string result;
        //standardStart(result);
        int level = 0;
        std::stack<std::string> endInteriors;
        while (!st.empty() && level >= 0) {
            if (st.top().type == NodeType::NONE) {
                level--;
                if (level >= 0) {
                    endInterior(result, endInteriors.top());
                    endInteriors.pop();
                }
            }
            if (st.top().type == NodeType::ACTION) {
                action(result, actionNodes[0]);
            }
            if (st.top().type == NodeType::INTERIOR) {
                startInterior(result, interiorNodes[0]);
                endInteriors.push(interiorNodes[0]);
                level++;
            }
            st.pop();
        }
        while (!endInteriors.empty()) {
            endInterior(result, endInteriors.top());
            endInteriors.pop();
        }

        //ending(result);
        return result;
    }

    std::stack<Node> getTreeStack(float* NNOutput) {
        std::stack<Node> result;
        for (int i = 0; i < maxNodes; i += 2) {
            NodeType nodeType;
            int IDNum = 0;
            if (NNOutput[i] < 0.33) {
                nodeType = NodeType::NONE;
            }else
            if (NNOutput[i] < 0.66) {
                nodeType = NodeType::ACTION;
                int IDNum = NNOutput[i + 1] * actionNodes.size();
                if (IDNum == actionNodes.size())
                    IDNum--;
            }
            else {
                nodeType = NodeType::INTERIOR;
                int IDNum = NNOutput[i + 1] * interiorNodes.size();
                if (IDNum == interiorNodes.size())
                    IDNum--;
            }
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