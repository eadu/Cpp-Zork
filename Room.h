#ifndef _ROOM_H
#define _ROOM_H

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
#include "Trigger.h"
using namespace std;
using namespace rapidxml;

typedef struct _border {
    string name;
    string direction;
} Border;

class Room{
public:
    string description;
    string type;
    string status;
    string name;
    vector<Border*> border;
    vector<string> item;
    vector<string> container;
    vector<string> creature;
    vector<Trigger*> trigger;

    Room(xml_node<>* node);
    virtual ~Room(){};

private:
    void makeRoom(xml_node<>* room);
};

#endif
