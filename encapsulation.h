#ifndef ENCAPSULATION_H
#define ENCAPSULATION_H

#include "tinyxml2.h"

#include <iostream>

namespace encap {

using namespace tinyxml2;

enum class NodeType {
    name = 0,
    attr
};

// add
bool insertChild(XMLNode *parent, XMLNode *child, uint index = 1);


// delete
void delChild(XMLNode *parent, uint index);

// modify
bool replaceChildNode(XMLDocument &src, XMLDocument &tar, std::string node);

bool replaceChildNode(XMLNode *parent, XMLNode *child, NodeType type, std::string name, std::string value="");


// find

XMLElement * findChild(XMLNode *parent, NodeType type, std::string name, std::string value="");

XMLElement * findChild(XMLNode *parent, uint index);

}

#endif
