#ifndef _HEADER_H
#define _HEADER_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <list>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "Room.h"
#include "Container.h"
#include "Item.h"
#include "Creature.h"

using namespace std;
using namespace rapidxml;

vector<Room*> room_list;
vector<Container*> container_list;
vector<Item*> item_list;
vector<Creature*> creature_list;

vector<string> inventory;
bool endGame = false;
Room * currentRoom;
void parse_input(string);
string get_objType(string);
void Add(string obj){
    string objName, objLocation;
	objName = obj.substr(0, obj.find(" to "));
    objLocation = obj.substr(obj.find(" to ") + 4);
    int i = 0;
    string objType = get_objType(objName);
    if(objType == "Item"){
		while(i < room_list.size()) {
            if(room_list[i]->name == objLocation){
                room_list[i]->item.push_back(objName);
                return;
            }
			i++;
		}
		i = 0;
		while(i < container_list.size()) {
            if(container_list[i]->name == objLocation){
                container_list[i]->item.push_back(objName);
                return;
            }
			i++;
		}
    }
    if(objType == "Creature"){
		i = 0;
		while(i < room_list.size()) {
            if(room_list[i]->name == objLocation){
                room_list[i]->creature.push_back(objName);
                return;
            }
			i++;
		}
    }
    if(objType == "Container"){
		i = 0;
		while(i < room_list.size()) {
            if(room_list[i]->name == objLocation){
                room_list[i]->container.push_back(objName);
                return;
            }
			i++;
		}
    }
}
void Delete(string objName){
    int i,j,k;
    for(i = 0; i < room_list.size(); i++){
        if(room_list[i]->name == objName){
            for(j = 0; j < currentRoom -> border.size(); j++){
                if(currentRoom -> border[j] -> name == objName){
                    currentRoom->border.erase(currentRoom->border.begin()+j);
                    return;
                }
            }
        }
    }
    for(i = 0; i < container_list.size(); i++){
        if(container_list[i]->name == objName){
            for(j = 0; j < room_list.size(); j++){
                for(k = 0; k < room_list[j] -> container.size(); k++){
                    if(room_list[j] -> container[k] == objName){
                        room_list[j] -> container.erase(room_list[j]->container.begin()+k);
                        return;
                    }
                }
            }
        }
    }
    for(i = 0; i < item_list.size(); i++){
        if(item_list[i]->name == objName){
            for(j = 0; j < room_list.size(); j++){
                for(k = 0; k < room_list[j] -> item.size(); k++){
                    if(room_list[j] -> item[k] == objName){
                        room_list[j] -> item.erase(room_list[j]->item.begin()+k);
                        return;
                    }
                }
            }
        }
    }
    for(i = 0; i < creature_list.size(); i++){
        if(creature_list[i]->name == objName){
            for(j = 0; j < room_list.size(); j++){
                for(k = 0; k < room_list[j] -> creature.size(); k++){
                    if(room_list[j] -> creature[k] == objName){
                        room_list[j] -> creature.erase(room_list[j]->creature.begin()+k);
                        return;
                    }
                }
            }
        }
    }
}
void Update(string obj){
    string objName, nextStatus;
    objName = obj.substr(0, obj.find(" to "));
    nextStatus = obj.substr(obj.find(" to ") + 4);
    int i = 0;
	while(i < room_list.size()) {
        if(room_list[i]->name == objName){
            room_list[i]->status = nextStatus;
            return;
        }
		i++;
	}
	i = 0;
	while(i < container_list.size()) {
        if(container_list[i]->name == objName){
            container_list[i]->status = nextStatus;
            return;
        }
		i++;
	}
	i = 0;
	while(i < item_list.size()) {
        if(item_list[i]->name == objName){
            item_list[i]->status = nextStatus;
            return;
        }
		i++;
	}
	i = 0;
	while(i < creature_list.size()) {
        if(creature_list[i]->name == objName){
            creature_list[i]->status = nextStatus;
            return;
        }
		i++;
	}
}

void GameOver(){
    endGame = true;
    cout << "Victory!" << endl;
    cout << "Game Over" << endl;
}

void switchAck(string action){
    if(action.find("Add") != string::npos){
        Add(action.erase(0,4));
        return;
    }
    if(action.find("Delete") != string::npos){
        Delete(action.erase(0,7));
        return;
    }
    if(action.find("Update") != string::npos){
        Update(action.erase(0,7));
        return;
    }
	if(action == "Game Over") {
        GameOver();
        return;
    }
    parse_input(action);
}

void next_room(string input){
    int i = (currentRoom -> border).size();
    int ind = 0;
	while(ind < i) {
        if(currentRoom -> border[ind] -> direction == input){
            string newroom = currentRoom -> border[ind] -> name;
            int j = room_list.size();
			int ind2 = 0;
			while(ind2 < j) {
                if(room_list[ind2] -> name == newroom){
                    currentRoom = room_list[ind2];
                }
				ind2++;
			}
            break;
		}
        ind++;
 	}
    if(ind == i)
        cout << "Can't go that way" << endl;
    else
        cout << currentRoom -> description << endl;
}

void view_inventory(){
	int i = inventory.size();
	if(!i){
		cout << "Inventory: empty" << endl;
		return;
	}
	cout << "Inventory: ";
	int ind = 0;
	while(ind < i - 1) {
		cout << inventory[ind] << ", ";
		ind++;
	}
	cout << inventory[ind] << endl;
}

void take(string input){
    int i,j,k;
    for(i = 0; i < (currentRoom -> item).size(); i++){
        if(currentRoom -> item[i] == input){
            inventory.push_back(input);
            (currentRoom -> item).erase((currentRoom -> item).begin() + i);
            cout << "Item " << input << " added to inventory." << endl;
            return;
        }
    }

    for(i = 0; i < (currentRoom -> container).size(); i++){
        string container_name = currentRoom->container[i];
        for(j = 0; j < container_list.size(); j++){
            if(container_list[j]->name == container_name &&
               container_list[j]->status == "unlocked"){
                for(k = 0; k < container_list[j]->item.size();k++){
                    if(container_list[j]->item[k] == input){
                        (currentRoom -> item).push_back(container_list[j] -> item[k]);
                        container_list[j] -> item.erase(container_list[j]->item.begin()+k);
                        take(input);
                        return;
                    }
                }
            }
        }
    }
    cout << "Error" << endl;
}

void drop(string input){
	int i = 0;
	while(i < inventory.size()) {
        if(inventory[i] == input){
            (currentRoom -> item).push_back(input);
            inventory.erase(inventory.begin() + i);
            cout << input << " dropped." << endl;
            return;
        }
		i++;
	}
    cout << "Error" << endl;
}

void read(string input){
	int i = 0;
	int j;
	while(i < inventory.size()) {
        if(inventory[i] == input){
			j = 0;
			while(j < item_list.size()) {
                if(item_list[j] -> name == input){
                    if(item_list[j] -> writing.size() == 0)
                        cout << "Nothing written." << endl;
                    else
                        cout << item_list[j] -> writing << endl;
                }
				j++;
			}
            return;
        }
		i++;
	}
    cout << "Error" << endl;
}

void put(string a, string b){
    int i = 0;
	int j = 0;
	int k = 0;
	while(i < inventory.size()) {
        if(inventory[i] == a){
            if(currentRoom -> name == b){
                drop(a);
                return;
            }
			j = 0;
			while(j < currentRoom->container.size()) {
                if(currentRoom -> container[j] == b) { break; }
				j++;
			}
            if(j == currentRoom -> container.size()){
                cout<<"Error"<<endl;
                return;
            }
			j = 0;
			while(j < container_list.size()) {
                if(container_list[j] -> name == b){
                    if(container_list[j]->acceptElement.size() == 0){
                        container_list[j] -> item.push_back(a);
                        inventory.erase(inventory.begin() + i);
                        cout << "Item " << a << " added to "<< b << "." << endl;
                        if(container_list[j]->status == ""){
                            container_list[j]->status = "unlocked";
                        }
                        return;
                    }
					k = 0;
					while(k < container_list[j]->acceptElement.size()) {
                        if(container_list[j] -> acceptElement[k] == a){
                            container_list[j] -> item.push_back(a);
                            inventory.erase(inventory.begin() + i);
                            cout << "Item " << a << " added to "<< b << "." << endl;
                            if(container_list[j]->status == ""){
                                container_list[j]->status = "unlocked";
                            }
                            return;
                        }
						k++;
					}
                    cout << b << " doesn't accept " << a << endl;
                    return;
                }
				j++;
			}
            return;
        }
		i++;
	}
    cout << "Error"<<endl;
}

void Activate(string input){
	int i = 0;
	int j = 0;
	while(i < inventory.size()) {
        if(inventory[i] == input){
			j = 0;
			while(j < item_list.size()) {
                if(item_list[j] -> name == input){
                    if(item_list[j] -> canTurnOn == false){
                        cout<<"Item is not able to be turned on." << endl;
                    } else {
                        cout<<"You activate the "<< item_list[j]->name<<"."<<endl;
                        cout << item_list[j] -> turnon.print << endl;
                        switchAck(item_list[j] -> turnon.action);
                    }
                }
				j++;
			}
            return;
        }
		i++;
	}
    cout << "Error" << endl;
}

void open(string input){
    int var = 0;
	while(var < currentRoom->container.size()) {
        if(currentRoom -> container[var] == input){ break; }
		var++;
	}
    if(var == currentRoom -> container.size()){
        cout << "Error" << endl;
        return;
    }
	int i = 0;
	while(i < container_list.size()) {
        if(container_list[i] -> name == input){
            if(container_list[i] -> status == "locked"){
                cout << container_list[i] -> name << " is locked." << endl;
                return;
            }
            if((container_list[i] -> item).size() == 0){
                cout <<container_list[i] -> name << " is empty." << endl;
                return;
            }
            container_list[i] -> status = "unlocked";
            cout << container_list[i] -> name << " contains ";
            int j = 0;
			while(j < (container_list[i] -> item).size() - 1) {
                cout << container_list[i] -> item[j] << ", ";
				j++;
			}
            cout << container_list[i] -> item[j] << "." << endl;
            return;
        }
		i++;
	}
}

void exit() {
    if(currentRoom -> type == "exit"){
        GameOver();
        return;
    }
    cout << "Error" << endl;
}

void attack(string creature, string weapon){
	int i = 0;
	int j = 0;
	while(i < currentRoom->creature.size()) {
        if(currentRoom -> creature[i] == creature) { break; }
		i++;
	}
    if(i == currentRoom -> creature.size()){
        cout << "Error" << endl;
        return;
    }
	i = 0;
	while(i < inventory.size()) {
        if(inventory[i] == weapon) { break; }
		i++;
	}
    if(i == inventory.size()){
        cout << "Error" << endl;
        return;
    }
	i = 0;
	while(i < creature_list.size()) {
        if(creature_list[i]->name == creature){ break; }
		i++;
	}
	j = 0;
	while(j < creature_list[i]->vulnerability.size()) {
        if(creature_list[i]->vulnerability[j] == weapon){ 
            cout << "1You assault the " << creature << " with the " << weapon << "." << endl;
            break;
        }
		j++;
	}
    if(j == creature_list[i]->vulnerability.size()) {
        cout << "Error" << endl;
        return;
    }
    if(creature_list[i]->attack == NULL) {
        return;
    }
    if(creature_list[i]->attack->triggerCondition){
        string object = creature_list[i]->attack->condition.object;
        string status = creature_list[i]->attack->condition.status;
        bool itemFound = false;
        bool itemMatch = false;
		j = 0;
		while(j < item_list.size()) {
            if(item_list[j]->name == object){
                itemFound = true;
                itemMatch = item_list[j]->status == status;
                break;
            }
			j++;
		}
        if(!itemFound) {
			j = 0;
			while(j < room_list.size()) {
                if(room_list[j]->name == object){
                    itemFound = true;
                    itemMatch = room_list[j]->status == status;
                    break;
                }
				j++;
			}
        }
        if(!itemFound) {
			j = 0;
			while(j < container_list.size()) {
                if(container_list[j]->name == object){
                    itemFound = true;
                    itemMatch = container_list[j]->status == status;
                    break;
                }
				j++;
			}
        }
        if(!itemFound) {
			j = 0;
			while(j < creature_list.size()) {
                if(creature_list[j]->name == object){
                    itemFound = true;
                    itemMatch = creature_list[j]->status == status;
                    break;
                }
				j++;
			}
        }
        if(!itemMatch) {
            cout << "Error" << endl;
            return;
        }
    }
    if(creature_list[i]->attack->triggerPrint){
        cout << "2You assault the " << creature << " with the " << weapon << "." << endl;
        cout << creature_list[i]->attack->print<<endl;
    }
    if(creature_list[i]->attack->triggerAction){
        for(j = 0; j<creature_list[i]->attack->action.size();j++){
            switchAck(creature_list[i]->attack->action[j]);
        }
    }
}

void parse_input(string input) {
	if(input == "s" || input == "w" || input == "n" || input == "e") {
        next_room(input);
        return;
	}
	if(input == "take") {
        cout<<"What do you want to take? ";
        getline(cin, input);
        take(input);
        return;
    }
	if(input == "i") {
        view_inventory();
        return;
    }
    if(input.find("take") != string::npos){
        input.erase(0,5);
        take(input);
        return;
    }
    if(input.find("drop") != string::npos){
        input.erase(0,5);
        drop(input);
        return;
    }

	if(input == "drop") {
        cout<<"What do you want to drop? ";
        getline(cin, input);
        drop(input);
        return;
    }
	if(input == "read") {
        cout<<"What do you want to read? ";
        getline(cin, input);
        read(input);
        return;
    }
    if(input.find("read") != string::npos){
        input.erase(0,5);
        read(input);
        return;
    }
	if(input == "open") {
        cout<<"What do you want to open? ";
        getline(cin, input);
        if(input == "exit"){
            exit();
            return;
        }
        open(input);
        return;
    }
    if(input.find("open") != string::npos){
        input.erase(0,5);
        if(input == "exit"){
            exit();
            return;
        }
        open(input);
        return;
    }
    if(input.find("put") != string::npos){
        input.erase(0,4);
        int space_pos = input.find(" ");
        string put_item = input.substr(0, space_pos);
        input.erase(0, space_pos + 4);
        string put_into = input;
        put(put_item, put_into);
        return;
    }
	if(input == "put") {
        cout << "What do you want to put? ";
        getline(cin, input);
        string put_item = input;
        cout << "Where do you want to put in? ";
        getline(cin, input);
        string put_into = input;
        put(put_item, put_into);
        return;
    }
	if(input == "turn on") {
        cout<<"What do you want to turn on? ";
        getline(cin, input);
        Activate(input);
        return;
    }
    if(input.find("turn on") != string::npos){
        input.erase(0,8);
        Activate(input);
        return;
    }
	if(input == "attack") {
        cout << "What do you want to attack? ";
        getline(cin, input);
        string monster = input;
        cout << "What do you want to attack with? ";
        getline(cin, input);
        string weapon = input;
        attack(monster, weapon);
        return;
    }
    if(input.find("attack") != string::npos){
        input.erase(0,7);
        int space_pos = input.find(" ");
        string monster = input.substr(0, space_pos);
        input.erase(0, space_pos + 6);
        string weapon = input;
        attack(monster, weapon);
        return;
    }
  cout << "Error" << endl;
}

string get_objType(string o){
    int i = 0;
    while(i < room_list.size()) {
        if(room_list[i] -> name == o){
            return "Room";
        }
        i++;
    }
    i = 0;
    while(i < item_list.size()) {
        if(item_list[i] -> name == o){
            return "Item";
        }
        i++;
    }
    i = 0;
    while(i < container_list.size()) {
        if(container_list[i] -> name == o){
            return "Container";
        }
        i++;
    }
    i = 0;
    while(i < creature_list.size()) {
        if(creature_list[i] -> name == o){
            return "Creature";
        }
        i++;
    }
    return NULL;
}
bool trig_own(Trigger * t){
    string owner = t -> owner.owner;
    string has = t -> owner.has;
    string object = t -> owner.object;
    int i,j,k;
    i = 0;
    if(owner == "inventory"){
        while(i < inventory.size()) {
            if(inventory[i] == object){
                if(has == "yes"){
                    if(t->triggerPrint){cout<<t->print<<endl;}
                    if(t->triggerAction){
                        k = 0;
                        while(k < t->action.size()) {
                            switchAck(t->action[k]);
                            k++;
                        }
                    }
                    return true;
                }else{return false;}
            }
            i++;
        }
        if(i == inventory.size()){
            if(has == "no"){
                if(t->triggerPrint){cout<<t->print<<endl;}
                if(t->triggerAction){
                    k = 0;
                    while(k < t->action.size()) {
                        switchAck(t->action[k]);
                        k++;
                    }
                }
                return true;
            }else{return false;}
        }
    }
    string owner_type = get_objType(owner);
    string objType = get_objType(object);
    if(owner_type == "Room"){
        i = 0;
        while(i < room_list.size()) {
            if(room_list[i] -> name == owner){
                if(objType == "Item"){
                    j = 0;
                    while(j < room_list[i] -> item.size()) {
                        if(room_list[i]->item[j] == object){
                            if(has == "yes"){
                                if(t->triggerPrint){cout<<t->print<<endl;}
                                if(t->triggerAction){
                                    k = 0;
                                    while(k < t->action.size()) {
                                        switchAck(t->action[k]);
                                        k++;
                                    }
                                }
                                return true;
                            }else{return false;}
                        }
                        j++;
                    }
                    if(j == room_list[i]->item.size()){
                        if(has == "no"){
                            if(t->triggerPrint){cout<<t->print<<endl;}
                            if(t->triggerAction){
                                k = 0;
                                while(k < t->action.size()) {
                                    switchAck(t->action[k]);
                                    k++;
                                }
                            }
                            return true;
                        }else{return false;}
                    }
                }
                if(objType == "Container"){
                    j = 0;
                    while(j < room_list[i] -> container.size()) {
                        if(room_list[i]->container[j]== object ){
                            if(has == "yes"){
                                if(t->triggerPrint){cout<<t->print<<endl;}
                                if(t->triggerAction){
                                    k = 0;
                                    while(k < t->action.size()) {
                                        switchAck(t->action[k]);
                                        k++;
                                    }
                                }
                                return true;
                            }else{return false;}
                        }
                        j++;
                    }
                    if(j == room_list[i]->container.size()){
                        if(has == "no"){
                            if(t->triggerPrint){cout<<t->print<<endl;}
                            if(t->triggerAction){
                                k = 0;
                                while(k < t->action.size()) {
                                    switchAck(t->action[k]);
                                    k++;
                                }
                            }
                            return true;
                        }else{return false;}
                    }
                }
                if(objType == "Creature"){
                    j = 0;
                    while(j < room_list[i] -> creature.size()) {
                        if(room_list[i]->creature[j]== object){
                            if(has == "yes"){
                                if(t->triggerPrint){cout<<t->print<<endl;}
                                if(t->triggerAction){
                                    k = 0;
                                    while(k < t->action.size()) {
                                        switchAck(t->action[k]);
                                        k++;
                                    }
                                }
                                return true;
                            }else{return false;}
                        }
                        j++;
                    }
                    if(j == room_list[i]->creature.size()){
                        if(has == "no"){
                            if(t->triggerPrint){cout<<t->print<<endl;}
                            if(t->triggerAction){
                                k = 0;
                                while(k < t->action.size()) {
                                    switchAck(t->action[k]);
                                    k++;
                                }
                            }
                            return true;
                        }else{return false;}
                    }
                }
            }
            i++;
        }
    }
    if(owner_type == "Container"){
        i = 0;
        while(i < container_list.size()) {
            if(container_list[i]->name == owner){
                j = 0;
                while(j < container_list[i] -> item.size()) {
                    if(container_list[i]->item[j]== object){
                        if(has == "yes"){
                            if(t->triggerPrint){cout<<t->print<<endl;}
                            if(t->triggerAction){
                                k = 0;
                                while(k < t->action.size()) {
                                    switchAck(t->action[k]);
                                    k++;
                                }
                            }
                            return true;
                        }else{return false;}
                    }
                    j++;
                }
                if(j == container_list[i]->item.size()){
                    if(has == "no"){
                        if(t->triggerPrint){cout<<t->print<<endl;}
                        if(t->triggerAction){
                            k = 0;
                            while(k < t->action.size()) {
                                switchAck(t->action[k]);
                                k++;
                            }
                        }
                        return true;
                    }else{return false;}
                }
            }
            i++;
        }
    }
    return false;
}
bool trig_stat(Trigger * t){
    string object = t -> status.object;
    string status = t -> status.status;
    int i,j;
    string objType = get_objType(object);
    if(objType == "Room"){
        i = 0;
        while(i < room_list.size()) {
            if(room_list[i] -> name == object){
                if(room_list[i] -> status == status){
                    if(t->triggerPrint){cout<<t->print<<endl;}
                    if(t->triggerAction){
                        j = 0;
                        while(j < t->action.size()) {
                            switchAck(t->action[j]);
                            j++;
                        }
                    }
                    return true;
                }
            }
            i++;
        }
    }
    if(objType == "Item"){
        i = 0;
        while(i < item_list.size()) {
            if(item_list[i] -> name == object){
                if(item_list[i] -> status == status){
                    if(t->triggerPrint){cout<<t->print<<endl;}
                    if(t->triggerAction){
                        j = 0;
                        while(j < t->action.size()) {
                            switchAck(t->action[j]);
                            j++;
                        }
                    }
                    return true;
                }
            }
            i++;
        }
    }
    if(objType == "Container"){
        i = 0;
        while(i < container_list.size()) {
            if(container_list[i] -> name == object){
                if(container_list[i] -> status == status){
                    if(t->triggerPrint){cout<<t->print<<endl;}
                    if(t->triggerAction){
                        j = 0;
                        while(j < t->action.size()) {
                            switchAck(t->action[j]);
                            j++;
                        }
                    }
                    return true;
                }
            }
            i++;
        }
    }
    if(objType == "Creature"){
        i = 0;
        while(i < creature_list.size()) {
            if(creature_list[i] -> name == object){
                if(creature_list[i] -> status == status){
                    if(t->triggerPrint){cout<<t->print<<endl;}
                    if(t->triggerAction){
                        j = 0;
                        while(j < t->action.size()) {
                            switchAck(t->action[j]);
                            j++;
                        }
                    }
                    return true;
                }
            }
            i++;
        }
    }
    return false;
}
bool checkTrig_no_arg(){
    int i,j,k;
    bool roomOut = false;
    bool itemOut = false;
    bool containerOut = false;
    bool creatureOut = false;
    Trigger *t;
    if(currentRoom -> trigger.size() != 0){
        j = 0;
        while(j < currentRoom->trigger.size()) {
            t = currentRoom->trigger[j];
            if(!t->triggerCommand){
                if(t->type == "permanent" || (t->type == "single" && t->times == 0)){
                    if(t->condition == 3){roomOut = trig_own(t);}
                    else if(t->condition == 2){roomOut = trig_stat(t);}
                    if(roomOut == true){t->times++;}
                }
            }
            j++;
        }
    }
    i = 0;
    while(i < currentRoom -> item.size()) {
        string target = currentRoom -> item[i];
        j = 0;
        while(j < item_list.size()) {
            if(item_list[j] -> name == target){
                k = 0;
                while(k < item_list[j] -> trigger.size()) {
                    t = item_list[j] -> trigger[k];
                    if(!t->triggerCommand){
                        if(t->type == "permanent" || (t->type == "single" && t->times == 0)){
                            if(t->condition == 3){itemOut = trig_own(t);}
                            else if(t->condition == 2){itemOut = trig_stat(t);}
                            if(itemOut == true){t->times++;}
                        }
                    }
                    k++;
                }
            }
            j++;
        }
        i++;
    }
    i = 0;
    while(i < currentRoom -> container.size()) {
        string target = currentRoom -> container[i];
        j = 0;
        while(j < container_list.size()) {
            if(container_list[j] -> name == target){
                k = 0;
                while(k < container_list[j] -> trigger.size()) {
                    t = container_list[j] -> trigger[k];
                    if(!t->triggerCommand){
                        if(t->type == "permanent" || (t->type == "single" && t->times == 0)){
                            if(t->condition == 3){containerOut = trig_own(t);}
                            else if(t->condition == 2){containerOut = trig_stat(t);}
                            if(containerOut == true){t->times++;}
                        }
                    }
                    k++;
                }
            }
            j++;
        }
        i++;
    }
    i = 0;
    while(i < currentRoom -> creature.size()) {
        string target = currentRoom -> creature[i];
        j = 0;
        while(j < creature_list.size()){
            if(creature_list[j] -> name == target){
                k = 0;
                while(k < creature_list[j] -> trigger.size()) {
                    t = creature_list[j] -> trigger[k];
                    if(!t->triggerCommand){
                        if(t->type == "permanent" || (t->type == "single" && t->times == 0)){
                            if(t->condition == 3){creatureOut = trig_own(t);}
                            else if(t->condition == 2){creatureOut = trig_stat(t);}
                            if(creatureOut == true){t->times++;}
                        }
                    }
                    k++;
                }
            }
            j++;
        }
        i++;
    }
    return (roomOut||itemOut||containerOut||creatureOut);
}
bool checkTrig_arg(string input){
    int i,j,k;
    bool roomOut = false;
    bool itemOut = false;
    bool containerOut = false;
    bool creatureOut = false;
    Trigger *t;
    if(currentRoom -> trigger.size() != 0){
        j = 0;
        while(j < currentRoom->trigger.size()) {
            t = currentRoom->trigger[j];
            if(t -> triggerCommand && input == t -> command){
                if(t->type == "permanent" || (t->type == "single" && t->times == 0)){
                    if(t->condition == 3){roomOut = trig_own(t);}
                    else if(t->condition == 2){roomOut = trig_stat(t);}
                    if(roomOut == true){t->times++;}
                }
            }
            j++;
        }
    }
    i = 0;
    while(i < inventory.size()) {
        string target = inventory[i];
        j = 0;
        while(j < item_list.size()) {
            if(item_list[j] -> name == target){
                k = 0;
                while(k < item_list[j] -> trigger.size()) {
                    t = item_list[j] -> trigger[k];
                    if(t -> triggerCommand && input == t -> command){
                        if(t->type == "permanent" || (t->type == "single" && t->times == 0)){
                            if(t->condition == 3){itemOut = trig_own(t);}
                            else if(t->condition == 2){itemOut = trig_stat(t);}
                            if(itemOut == true){t->times++;}
                        }
                    }
                    k++;
                }
            }
            j++;
        }
        i++;
    }
    i = 0;
    while(i < currentRoom -> container.size()) {
        string target = currentRoom -> container[i];
        j = 0;
        while(j < container_list.size()){
            if(container_list[j] -> name == target){
                k = 0;
                while(k < container_list[j] -> trigger.size()) {
                    t = container_list[j] -> trigger[k];
                    if(t -> triggerCommand && input == t -> command){
                        if(t->type == "permanent" || (t->type == "single" && t->times == 0)){
                            if(t->condition == 3){containerOut = trig_own(t);}
                            else if(t->condition == 2){containerOut = trig_stat(t);}
                            if(containerOut == true){t->times++;}
                        }
                    }
                    k++;
                }
            }
            j++;
        }
        i++;
    }
    i = 0;
    while(i < currentRoom -> creature.size()){
        string target = currentRoom -> creature[i];
        j = 0;
        while(j < creature_list.size()) {
            if(creature_list[j] -> name == target){
                k = 0;
                while(k < creature_list[j] -> trigger.size()) {
                    t = creature_list[j] -> trigger[k];
                    if(t -> triggerCommand && input == t -> command){
                        if(t->type == "permanent" || (t->type == "single" && t->times == 0)){
                            if(t->condition == 3){creatureOut = trig_own(t);}
                            else if(t->condition == 2){creatureOut = trig_stat(t);}
                            if(creatureOut == true){t->times++;}
                        }
                    }
                    k++;
                }
            }
            j++;
        }
        i++;

    }
    return (roomOut||itemOut||containerOut||creatureOut);
}
#endif
