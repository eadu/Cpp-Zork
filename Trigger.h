#ifndef _TRIGGER_H
#define _TRIGGER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <list>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

typedef struct _status{
    string object;
    string status;
} Status;

typedef struct _owner{
    string has;
    string owner;
    string object;
} Owner;

class Trigger {
public:
    string print;
    string command;
    string type;
    vector<string> action;
    bool triggerPrint; //has_print
    bool triggerAction; //has_action
    bool triggerCommand; //has_command
    int condition;

    Owner owner;
    Status status;
    int times;

    Trigger(xml_node<>* node);
    virtual ~Trigger(){};

private:
    void setupTrigger(xml_node<>* node);
    int condition_count(xml_node<>* node);
    void setupOwner(xml_node<>* node);
    void setupStatus(xml_node<>* node);
};

#endif
