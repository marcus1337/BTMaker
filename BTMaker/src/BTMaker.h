#pragma once
#include <string>
#include <vector>

class BTMaker {
public:

    std::vector<std::string> interiorNodes = { "Sequence" , "Fallback"};
    std::vector<std::string> decoratorNodes = { "Inverter" };
    std::vector<std::string> actionNodes = { "action1", "action2" };

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
       

};