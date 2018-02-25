#include "Util.h"



Util::Util()
{
}


Util::~Util()
{
}

void Util::generatePNG(XMLParser * parser)
{
	std::ofstream dotFile;
	string exeDir = "E:\\硕士毕业设计\\代码\\ICIL\\graphviz-2.38\\bin\\dot.exe";
	string root = exeDir.substr(0, 2);
	const char *cmdExplore = root.c_str();

	int networkID = 0;
	for (LDNetworkTree* tree : parser->vecTree) {
		string dotpath = "network" + std::to_string(networkID) + ".gv";
		dotFile.open(dotpath);
		dotFile << "digraph network" << networkID << " {" << std::endl;
		dotFile << "label = network" << networkID << std::endl;
		// label the nodes
		for (LDNode* node : tree->vecTreeNode) {
			//dotFile << node->getID() << "[label = \"" << node->getID() << " "<<node->getVar()->getName() << "\"]" << std::endl;
			if (!node->isVirtualNode()) {
				dotFile << node->getID() << "[label = \"" << node->getVar()->getName() << "\"]" << std::endl;
			}
		}
		string nodeID;
		string inNodeID;
		for (LDNode* node : tree->vecTreeNode) {
			if (node->isVirtualNode()) {
				nodeID = "vn" + std::to_string(node->getVirtualNodeID());
			}
			else {
				nodeID = node->getID();
			}
			for (LDNode* inNode : node->inNodes) {
				if (inNode->isVirtualNode()) {
					inNodeID = "vn" + std::to_string(inNode->getVirtualNodeID());
				}
				else {
					inNodeID = inNode->getID();
				}
				dotFile << inNodeID << " -> " << nodeID << std::endl;
			}
		}

		// test out edges
		/*string outNodeID;
		for (LDNode* node : tree->vecTreeNode) {
			if (node->isVirtualNode()) {
				nodeID = "vn" + std::to_string(node->getVirtualNodeID());
			}
			else {
				nodeID = node->getID();
			}
			for (LDNode* outNode : node->outNodes) {
				if (outNode->isVirtualNode()) {
					outNodeID = "vn" + std::to_string(outNode->getVirtualNodeID());
				}
				else {
					outNodeID = outNode->getID();
				}
				dotFile << outNodeID << " -> " << nodeID << std::endl;
			}
		}*/

		dotFile << "}" << std::endl;
		dotFile.flush();
		dotFile.close(); 

		string cmdStr = exeDir + " network" + std::to_string(networkID) + ".gv" + " -Tsvg -o " + " network" + std::to_string(networkID) + ".svg";
		const char *cmdExe = cmdStr.c_str();
		WinExec(cmdExplore, SW_NORMAL);
		WinExec(cmdExe, SW_NORMAL);
		std::cout << "complete network" << networkID << " !\n";
		networkID++;
	}
	

	
}
