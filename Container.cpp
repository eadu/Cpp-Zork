#include "Container.h"
using namespace std;
using namespace rapidxml;

Container::Container(xml_node<>* node) {
    makeContainer(node);
}

void Container::makeContainer(xml_node<>* node) {
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
        if(!strcmp(child->name(), "trigger")) {
            Trigger* newTrigger = new Trigger(child);
            trigger.push_back(newTrigger);
        }
        if(!strcmp(child->name(), "item")) {
            item.push_back(child->value());
        }
        if(!strcmp(child->name(), "accept")) {
            acceptElement.push_back(child->value());
        }
        child = child->next_sibling();
    }
}
