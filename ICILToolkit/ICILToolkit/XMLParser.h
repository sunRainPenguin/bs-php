#include "LDNode.h"
#include "LDExpNode.h"
#include "FBInVarNode.h"
#include "FBOutVarNode.h"
#include "FBBlockNode.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"
#include <iostream>
#include <algorithm> 
#include <set>
#include <queue>
#include <utility>
using std::set;
using std::queue;
using std::pair;
using namespace pugi;

class XMLParser
{
private:
	xml_document* xmlDoc;
	int virtualNodeNum;
	string LDToBoolExp(LDNetworkTree* tree);
	Variable* parseVar(xml_node xmlVar);
	void cutBranches(LDNode* branchNode, LDNetworkTree* tree);
	LDNode*  addParenthesis(LDNode* branchNode, LDNetworkTree* tree);

public:
	unordered_map<string, Variable*> mapVar;
	unordered_map<string, LDNode*> mapLDNodes; 
	unordered_map<string, FBNode*> mapFBNodes;
	vector<LDNetworkTree*> vecTree;
	XMLParser(string xmlPath);
	~XMLParser();
	string parseLD();
	string parseFB();
};

