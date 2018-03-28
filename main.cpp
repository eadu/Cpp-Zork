#include<iostream>
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<string>
#include<list>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "zork.h"

using namespace rapidxml;
using namespace std;

int main(int argc, char const *argv[])
{
	if(argc != 2) {
		cout << "Usage: ./zork <XMLFile>" << endl;
		return 1;
	}

	file<> xmlFile(argv[1]);

	xml_document<> document;
	document.parse<0>(xmlFile.data());

	xml_node<> *xmlNode = document.first_node();

	std::vector<xml_node<>*> roomx;
	std::vector<xml_node<>*> containerx;
	std::vector<xml_node<>*> itemx;
	std::vector<xml_node<>*> creaturex;

	xml_node<>* ct = xmlNode->first_node();
	while(ct) {
		if(!strcmp(ct->name(), "room")) {
			roomx.push_back(ct);
		}
		if(!strcmp(ct->name(), "container")) {
			containerx.push_back(ct);
		}
		if(!strcmp(ct->name(), "item")) {
			itemx.push_back(ct);
		}
		if(!strcmp(ct->name(), "creature")) {
			creaturex.push_back(ct);
		}
		ct = ct->next_sibling();
	}

	Room *room;
	int i = roomx.size();
	int pos;
	for(pos = 0; pos < i; pos++) {
		room = new Room(roomx[pos]);
		room_list.push_back(room);
	}

	i = containerx.size();
	Container* container;
	for(pos = 0; pos < i; pos++) {
		container = new Container(containerx[pos]);
		container_list.push_back(container);
	}

	i = itemx.size();
	Item* item;
	for(pos = 0; pos < i; pos++) {
		item = new Item(itemx[pos]);
		item_list.push_back(item);
	}

	i = creaturex.size();
	Creature* creature;
	for(pos = 0; pos < i; pos++) {
		creature = new Creature(creaturex[pos]);
		creature_list.push_back(creature);
	}

	string input;
	bool overridden = false;
	currentRoom = room_list[0];
	cout << currentRoom->description << endl;
	while(true) {
		overridden = checkTrig_no_arg();
		if(endGame) { break; }
		if(overridden) { continue; }
		getline(cin, input);
		if(string(input) == "q") { break; }
		overridden = checkTrig_arg(input);
		if(endGame) { break; }
		if(overridden) { continue; }
		parse_input(input);
		if(endGame) { break; }
	}

	return 0;
}
