#ifndef _CONTAINER_H
#define _CONTAINER_H

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

class Container {
public:
    string description;
    string status;
    string name;
    vector<Trigger*> trigger;
    vector<string> item;
    vector<string> acceptElement;

    Container(xml_node<>* node);
    virtual ~Container(){}

private:
    void makeContainer(xml_node<>* node);
};

#endif
