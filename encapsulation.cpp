#include "encapsulation.h"

namespace encap {

using namespace tinyxml2;

// add
bool insertChild(XMLNode *parent, XMLNode *child, uint index) {
    if (index == 1)
        parent->InsertFirstChild(child);
    else {
        auto cl = findChild(parent, index - 1);
        if (cl != NULL)
            parent->InsertAfterChild(cl, parent);
        else
            return false;
    }

    return true;
}


// delete
void delChild(XMLNode *parent, uint index) {
    parent->DeleteChild(findChild(parent, index));
}


// modify
bool replaceChildNode(XMLDocument &src, XMLDocument &tar, std::string node) {
    auto src_root = src.RootElement();
    auto tar_root = tar.RootElement();

    // replace node
    XMLElement *src_re = findChild(src_root, NodeType::name, node);
    XMLElement *tar_re = findChild(tar_root, NodeType::name, node);

    if (src_re != NULL) {
        // delete origin
        if (tar_re != NULL) {
            auto temp = tar_re->PreviousSiblingElement();
            tar_root->DeleteChild(tar_re);

            // add new
            if (temp != NULL)
                tar_root->InsertAfterChild(temp, src_re->DeepClone(&tar));
            else
                tar_root->InsertFirstChild(src_re->DeepClone(&tar));
        }
        else
            return false;
    }
    else
        return false;

    return true;
}

bool replaceChildNode(XMLNode *parent, XMLNode *child, NodeType type, std::string name, std::string value) {
    XMLElement *tar = findChild(parent, type, name, value);

    if (tar != NULL) {
        auto temp = tar->PreviousSiblingElement();
        parent->DeleteChild(tar);

        if (temp != NULL)
            parent->InsertAfterChild(temp, child);
        else
            parent->InsertFirstChild(child);
    }
    else
        return false;

    return true;
}


// find
XMLElement * findChild(XMLNode *parent, NodeType type, std::string name, std::string value) {
    if (parent->NoChildren())
        return NULL;

    auto cl = parent->FirstChildElement();
    switch (type) {
    case NodeType::name :
    {
        while (std::string(cl->Name()) != name) {
            cl = cl->NextSiblingElement();

            if (cl == NULL)
                return NULL;
        }
        break;
    }
    case NodeType::attr :
    {
        while (std::string(cl->Attribute(name.c_str())) != value) {
            cl = cl->NextSiblingElement();

            if (cl == NULL)
                return NULL;
        }
        break;
    }
    }

    return cl;
}

XMLElement * findChild(XMLNode *parent, uint index) {
    auto cl = parent->FirstChildElement();
    uint i = 1;
    while (i != index) {
        cl = cl ->NextSiblingElement();
        i = i+1;

        if (cl == NULL)
            return NULL;
    }

    return cl;
}

}
