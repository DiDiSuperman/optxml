#include "encapsulation.h"

#include <stdlib.h>
#include <iostream>
#include <vector>

std::string xmlpath = "/home/simon/Desktop/kaanh-project/kaanh.xml";
std::string temppath = "./kaanh.xml";

using namespace std;
using namespace tinyxml2;
using namespace encap;

// nodes of <shell> that you want to preserve after upgraded
std::vector<std::string> shell_node = {"UserManagement", "SystemSema", "FunctionGather", "ExternalAuto"
                                       "IoManager", "SemaManager", "PkgManager", "ModbusTcpServer"
                                       "AreaManager", "kaanh.motion.Motion", "RobotConfig"};

int main(int argc, char *argv[]){
    std::cout << "xmlpath:" << xmlpath << std::endl;
    std::cout << "temppath:" << temppath << std::endl;

    XMLDocument doc, temp;
    if (doc.LoadFile(xmlpath.c_str()) != XML_SUCCESS | temp.LoadFile(temppath.c_str()) != XML_SUCCESS) {
        std::cout << "load xml error: " << xmlpath << " & " << temppath << std::endl;
        return -1;
    }
    else {
        // replace model
        if ( !replaceChildNode(temp, doc, "MultiModel") ) {
            std::cout << "failed to replace node 'MultiModel'" << std::endl;
            return -1;
        }

        // replace ethercatmaster
        if ( !replaceChildNode(temp, doc, "EthercatMaster") ) {
            std::cout << "failed to replace node 'EthercatMaster'" << std::endl;
            return -1;
        }

        // replace controller
        if ( !replaceChildNode(temp, doc, "Controller") ) {
            std::cout << "failed to replace node 'Controller'" << std::endl;
            return -1;
        }

        // replace nodes of <shell>
        auto doc_root = doc.RootElement();
        auto temp_root = temp.RootElement();

        auto doc_mpo = findChild( findChild(doc_root, NodeType::name, "Shell"), NodeType::name, "ModulePoolObject" );
        auto temp_mpo = findChild( findChild(temp_root, NodeType::name, "Shell"), NodeType::name, "ModulePoolObject" );

        if (temp_mpo != NULL && doc_mpo != NULL) {
            for (int i=0; i<shell_node.size(); i++) {
                auto node = findChild(temp_mpo, NodeType::name, shell_node.at(i))->DeepClone(&doc);
                if (node != NULL) {
                    if ( !replaceChildNode(doc_mpo, node, NodeType::name, shell_node.at(i)) ) {
                        std::cout << "failed to replace node: " << shell_node.at(i) << std::endl;
                        return -1;
                    }
                }
                else {
                    std::cout << "failed to replace node: " << shell_node.at(i) << std::endl;
                    return -1;
                }
            }
        }
        else {
            std::cout << "failed to replace nodes of <shell>" << std::endl;
            return -1;
        }
    }

    doc.SaveFile(xmlpath.c_str());
    std::cout << "successfully executed!" << std::endl;

	return 0;
}
