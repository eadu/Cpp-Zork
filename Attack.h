#ifndef _ATTACK_H
#define _ATTACK_H

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

using namespace std;
using namespace rapidxml;

typedef struct _condition{
    string object;
    string status;
} Condition;

class Attack{
public:
    Condition condition;
	string print;
	vector<string> action;

    bool triggerCondition;
    bool triggerPrint;
    bool triggerAction;

    Attack(xml_node<>* node);
    virtual ~Attack(){};
private:
    void setupAttack(xml_node<>* node);
};

#endif
