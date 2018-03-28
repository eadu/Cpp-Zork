#include "Item.h"
using namespace std;
using namespace rapidxml;

Item::Item(xml_node<>* node){
	setupItem(node);
}

void Item::setupItem(xml_node<>* node){
    canTurnOn = false;
	xml_node<>* child = node -> first_node();
	while(child) {
		if(!strcmp(child->name(), "name")){
			name = child -> value();
		}
		if(!strcmp(child->name(), "status")){
			status = child -> value();
		}
		if(!strcmp(child->name(), "description")){
			description = child -> value();
		}
		if(!strcmp(child->name(), "writing")){
			writing = child -> value();
		}
        if(!strcmp(child->name(), "turnon")){
            canTurnOn = true;
            string printmsg, actionmsg;
			xml_node<>* child2 = child -> first_node();
            while(child2) {
                if(!strcmp(child2->name(), "print")){
                    printmsg = child2 -> value();
                }
                if(!strcmp(child2->name(), "action")){
                    actionmsg = child2->value();
                }
				child2 = child2 -> next_sibling();
            }
            turnon.print = printmsg;
            turnon.action = actionmsg;
        }
        if(!strcmp(child->name(), "trigger")){
            Trigger * t = new Trigger(child);
            trigger.push_back(t);
        }
		child = child -> next_sibling();
	}
}
