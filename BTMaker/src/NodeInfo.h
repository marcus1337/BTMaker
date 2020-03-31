#pragma once
#include <string>

enum NodeType { NONE = 0, ACTION, INTERIOR, CONDITION };

class Node {
public:
    static std::string getTypeStr(NodeType nodtype) {
        if (nodtype == NodeType::ACTION)
            return "<ACTION>";
        if (nodtype == NodeType::INTERIOR)
            return "<INTERIOR>";
        if (nodtype == NodeType::CONDITION)
            return "<CONDITION>";
        return "<NONE>";
    }

    NodeType type;
    int IDNumber;
    Node(NodeType _type, int _IDNumber) : type(_type), IDNumber(_IDNumber) {
    }
};