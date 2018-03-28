#include "Creature.h"

using namespace std;
using namespace rapidxml;

Creature::Creature(xml_node<>* node) {
    makeCreature(node);
}

void Creature::makeCreature(xml_node<>* node) {
    xml_node<>* child = node->first_node();
    while(child) {
        if(!strcmp(child->name(), "description")) {
            description = child->value();
        }
        if(!strcmp(child->name(), "status")) {
            status = child->value();
        }
        if(!strcmp(child->name(), "name")) {
            name = child->value();
        }
        if(!strcmp(child->name(), "attack")) {
            attack = new Attack(child);
        }
        if(!strcmp(child->name(), "trigger")) {
            Trigger* newTrigger = new Trigger(child);
            trigger.push_back(newTrigger);
        }
        if(!strcmp(child->name(), "vulnerability")) {
            vulnerability.push_back(child->value());
        }
        child = child->next_sibling();
    }
}
