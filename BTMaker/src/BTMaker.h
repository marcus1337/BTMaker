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

    bool handleEmptyNode(Node node, std::string& result, std::stack<std::string>& unclosedInteriors) {
        if (node.type == NodeType::NONE) {
            if (unclosedInteriors.empty())
                return false;
            endInterior(result, unclosedInteriors.top());
            unclosedInteriors.pop();
        }
        return true;
    }

    bool handleStackNode(Node node, std::string& result, std::stack<std::string>& unclosedInteriors) {
        if (!handleEmptyNode(node, result, unclosedInteriors))
            return false;
        if (node.type == NodeType::ACTION)
            action(result, actionNodes[node.IDNumber]);
        if (node.type == NodeType::INTERIOR) {
            startInterior(result, interiorNodes[node.IDNumber]);
            unclosedInteriors.push(interiorNodes[node.IDNumber]);
        }
        return true;
    }

    void addRemainingCloseTags(std::string& result, std::stack<std::string>& unclosedInteriors) {
        while (!unclosedInteriors.empty()) {
            endInterior(result, unclosedInteriors.top());
            unclosedInteriors.pop();
        }
    }

    std::string getStringFromNodes(std::stack<Node> st) {
        std::string result;
        std::stack<std::string> unclosedInteriors;
        while (!st.empty() && handleStackNode(st.top(), result, unclosedInteriors))
            st.pop();
        addRemainingCloseTags(result, unclosedInteriors);
        return result;
    }

    bool hasRemainingEmptyInterior(std::stack<bool>& actionAtLevel) {
        while (!actionAtLevel.empty()) {
            if (!actionAtLevel.top())
                return true;
            actionAtLevel.pop();
        }
        return false;
    }

    void markInteriorsOccupied(std::stack<bool>& actionAtLevel) {
        std::stack<bool> tmpActionLevels;
        for (int i = 0; i < actionAtLevel.size(); i++)
            tmpActionLevels.push(true);
        actionAtLevel = tmpActionLevels;
    }

    bool interiorClosingEmpty(std::stack<bool>& actionAtLevel) {
        if (!actionAtLevel.top())
            return true;
        actionAtLevel.pop();
        return false;
    }

    bool checkNodeForEmptyClosing(NodeType type, std::stack<bool>& actionAtLevel) {
        if (type == NodeType::NONE && interiorClosingEmpty(actionAtLevel))
            return true;
        if (type == NodeType::INTERIOR)
            actionAtLevel.push(false);
        if (type == NodeType::ACTION)
            markInteriorsOccupied(actionAtLevel);
        return false;
    }

    bool checkEmptyInteriorNode(std::stack<Node> st) {
        std::stack<bool> actionLevel;
        actionLevel.push(false);
        while (!st.empty() && !actionLevel.empty()) {
            if (checkNodeForEmptyClosing(st.top().type, actionLevel))
                return true;
            st.pop();
        }
        return hasRemainingEmptyInterior(actionLevel);
    }

    bool checkValidTreeTopology(std::stack<Node> st) {
        if (checkEmptyInteriorNode(st))
            return false;
        return true;
    }

    std::string getTreeXML(std::stack<Node> st) {
        std::string result;
        standardStart(result);
        result += getStringFromNodes(st);
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
            int IDNum = classifyNodeID(NNOutput[i + 1], nodeType);
            result.push(Node(nodeType, IDNum));
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