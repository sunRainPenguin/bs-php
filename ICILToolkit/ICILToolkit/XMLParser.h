#include "LDNode.h"
#include "LDExpNode.h"
#include "FBInVarNode.h"
#include "FBOutVarNode.h"
#include "FBBlockNode.h"
#include "SFCConvertor.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"
#include "Constants.h"
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
	vector<FBNode*> vecFBNode;
	XMLParser(string xmlPath);
	~XMLParser();
	void parseLD();
	void parseFB();
	void parseSFC();
	string getConnectionExp(FBConnection* fbConnection);
};

