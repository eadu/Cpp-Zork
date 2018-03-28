#include "Room.h"

Room::Room(xml_node<>* node) {
        makeRoom(node);
}

void Room::makeRoom(xml_node<>* room) {
    xml_node<>* child = room -> first_node();
    while(child) {
        //if(string(child->name()) == "type")
        if(!strcmp(child->name(), "type")){
			type = child->value();
		}
        if(!strcmp(child->name(), "name")) {
            name = child->value();
        }
        if(!strcmp(child->name(), "description")){
			description = child->value();
		}
        if(!strcmp(child->name(), "status")){
			status = child->value();
		}
        if(!strcmp(child->name(), "border")) {
            Border* border1 = new Border();
            xml_node<>* child2 = child->first_node();
            while(child2) {
                if(!strcmp(child2->name(), "name")) {
                    border1->name = child2->value();
                }
                if(!strcmp(child2->name(), "direction")) {
                    border1->direction = child2->value();
                    if(border1->direction == "north") {
                        border1->direction = "n";
                    }
                    if(border1->direction == "east") {
                        border1->direction= "e";
                    }
                    if(border1->direction == "south") {
                        border1->direction = "s";
                    }
                    if(border1->direction == "west") {
                        border1->direction = "w";
                    }
                }
                child2 = child2 -> next_sibling();
            }
            border.push_back(border1);
        }
        if(!strcmp(child->name(), "container")) {
            container.push_back(child->value());
        }
        if(!strcmp(child->name(), "creature")) {
            creature.push_back(child->value());
        }
        if(!strcmp(child->name(), "item")) {
            item.push_back(child->value());
        }
        if(!strcmp(child->name(), "trigger")) {
            Trigger* trigger1 = new Trigger(child);
            trigger.push_back(trigger1);
        }
        child = child->next_sibling();
    }
}
