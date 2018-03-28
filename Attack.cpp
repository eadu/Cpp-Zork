#include "Attack.h"
using namespace std;

Attack::Attack(xml_node<>* node) {
    setupAttack(node);
}

void Attack::setupAttack(xml_node<>* node){
    triggerCondition = false;
    triggerPrint = false;
    triggerAction = false;

    xml_node<>* child = node->first_node();
    while(child) {
        if(!strcmp(child->name(), "condition")) {
            triggerCondition = true;
            xml_node<>* child2 = child->first_node();
            while(child2) {
                if(!strcmp(child2->name(),"object")) {
                    condition.object = child2->value();
                }
                if(!strcmp(child2->name(), "status")) {
                    condition.status = child2->value();
                }
                child2 = child2->next_sibling();
            }
        }
        if(!strcmp(child->name(), "print")) {
            triggerPrint = true;
            print = child -> value();
        }
        if(!strcmp(child->name(), "action")) {
            triggerAction = true;
            string buffer = child -> value();
            action.push_back(buffer);
        }
        child = child->next_sibling();
    }
}
