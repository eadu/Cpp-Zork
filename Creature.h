#ifndef _CREATURE_H
#define _CREATURE_H

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
#include "Attack.h"
using namespace std;
using namespace rapidxml;

class Creature {
public:
    string description;
    string name;
    string status;
    Attack*  attack;
    vector<string> vulnerability;
    vector<Trigger*> trigger;

    Creature(xml_node<>* node);
    virtual ~Creature(){}

private:
        void makeCreature(xml_node<>* node);
};

#endif
