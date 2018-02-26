#include "XMLParser.h"
#include "pugixml.cpp"


XMLParser::XMLParser(string xmlPath)
{
	virtualNodeNum = 0;
	this->xmlDoc = new xml_document();
	xml_parse_result result = xmlDoc->load_file(xmlPath.c_str());
	std::cout << "XML Load Result: " << xmlPath << " "<<result.description() << "\n";
	// result error: ...
}


XMLParser::~XMLParser()
{
}

void XMLParser::parseLD()
{
	xml_node project = this->xmlDoc->child("project");
	xml_node addData0 = project.child("addData");
	xml_node data0 = addData0.child("data");
	xml_node resource = data0.child("resource");
	xml_node addData1 = resource.child("addData");
	xml_node data1 = addData1.child("data");
	xml_node pou = data1.child("pou");

	// parse interface
	xml_node pouInterface = pou.child("interface");
	for (xml_node varCat : pouInterface.children()) {
		for (xml_node xmlVar : varCat.children("variable")) {
			Variable* var = parseVar(xmlVar);
			if (var != nullptr) {
				mapVar.insert(make_pair(var->getName(), var));
			}
		}
	}

	// parse POU
	// 解析节点信息
	xml_node body = pou.child("body");
	xml_node LD = body.child("LD");

	int treeID = 0;
	LDNetworkTree* tree = nullptr;

	string LDEleID;
	LDEleType ldEleType;
	Variable* var;
	LDNode* node = nullptr;
	for (xml_node xmlLDEle : LD.children()) {

		if ((string(xmlLDEle.name()) == "leftPowerRail" || string(xmlLDEle.name()) == "vendorElement" || string(xmlLDEle.name()) == "rightPowerRail") && string(xmlLDEle.previous_sibling().previous_sibling().name()) != "leftPowerRail") { // 防止第一次遇到leftPowerRail和vendorElement生成两棵树
			if (tree != nullptr) {
				vecTree.push_back(tree);
			}
			tree = new LDNetworkTree(treeID);
			treeID++;
			if (string(xmlLDEle.name()) == "leftPowerRail") {
				node = new LDNode(virtualNodeNum); // virtual node: 这里默认xml中左电源线的id为0
				mapLDNodes.insert(make_pair("vn" + std::to_string(virtualNodeNum), node));
				virtualNodeNum++;
				tree->vecTreeNode.push_back(node);
			}
		}
		else {
			if (string(xmlLDEle.name()) == "contact") {
				ldEleType = Contact;
			}
			else if (string(xmlLDEle.name()) == "coil") {
				ldEleType = Coil;
			}
			else {
				continue;	// 目前处理以上三种节点
			}
 			LDEleID = xmlLDEle.attribute("localId").value();
			var = mapVar[xmlLDEle.child("variable").text().as_string()];
			int nodeX = xmlLDEle.child("position").attribute("x").as_int();
			int nodeY = xmlLDEle.child("position").attribute("y").as_int();
			Pos* pos = new Pos(nodeX, nodeY);
			node = new LDNode(LDEleID, ldEleType, var, xmlLDEle.attribute("negated").as_bool(), xmlLDEle.attribute("storage").as_bool(), pos);
			if (node->getType() == Coil) {
				tree->setCoil(node);
			}
			mapLDNodes.insert(make_pair(node->getID(), node));
			tree->vecTreeNode.push_back(node);
		}
		// 其他LD元素类型 ...
	}

	// 遍历所有节点，添加“入边”“出边”信息
	string refId = "";
	for (xml_node xmlLDEle : LD.children()) {
		if (string(xmlLDEle.name()) == "contact" || string(xmlLDEle.name()) == "coil" ) {
			for (xml_node xmlConnection : xmlLDEle.child("connectionPointIn").children()) {
				if (string(xmlConnection.name()) == "connection") {
					refId = xmlConnection.attribute("refLocalId").as_string();
					// 这里默认localID为0的节点为左电源线
					if (refId != "0") {
						mapLDNodes[xmlLDEle.attribute("localId").as_string()]->inNodes.push_back(mapLDNodes[refId]);
						mapLDNodes[refId]->outNodes.push_back(mapLDNodes[xmlLDEle.attribute("localId").as_string()]);
					}
					else {
						mapLDNodes[xmlLDEle.attribute("localId").as_string()]->inNodes.push_back(mapLDNodes["vn0"]);
						mapLDNodes["vn0"]->outNodes.push_back(mapLDNodes[xmlLDEle.attribute("localId").as_string()]);
					}
				}
			}
		}
	}

	// 转换为二叉树
	for (LDNetworkTree* tree : this->vecTree) {
		for (LDNode* node : tree->vecTreeNode) {
			if (node->outNodes.size() > 2) {
				cutBranches(node,tree);
			}
		}
	}

	// 生成Process statement list
	ofstream il;
	il.open("OUTPUT\\LD_ICIL.il", std::ios::trunc);
	il << "Program() = " << std::endl;
	for (LDNetworkTree* tree : this->vecTree) {
			il << tree->getCoil()->getVar()->getName() << " = ";
			il << LDToBoolExp(tree) << ";" << std::endl;	
	}
	il.flush();
	il.close();
}

void XMLParser::parseFB()
{
	string processStmtList = "";
	xml_node project = this->xmlDoc->child("project");
	xml_node addData0 = project.child("addData");
	xml_node data0 = addData0.child("data");
	xml_node resource = data0.child("resource");
	xml_node addData1 = resource.child("addData");
	xml_node data1 = addData1.child("data");
	xml_node pou = data1.child("pou");

	// parse POU
	// 解析节点信息
	xml_node body = pou.child("body");
	xml_node FBD = body.child("FBD");

	FBInVarNode* fbInVarNode = nullptr;
	FBOutVarNode* fbOutVarNode = nullptr;
	FBBlockNode* fbBlockNode = nullptr;
	xml_node xmlexp;
	xml_node xmlConnectIn;
	xml_node xmlConnection;
	string id = "";
	string refLocalId = "";
	string formalParameter = "";
	string varFormalParameter = "";
	string exp = "";
	string fbTypeName = "";
	string fbInstanceName = "";
	FBConnection* fbConnection = nullptr;
	FBInterface* fbinterface = nullptr;
	for (xml_node n : FBD.children()) {
		id = string(n.attribute("localId").as_string());
		if (string(n.name()) == "inVariable") {
			xmlexp = n.child("expression");
			exp = string(xmlexp.text().as_string());
			fbInVarNode = new FBInVarNode(id, InVar, exp);
			mapFBNodes.insert(make_pair(id, fbInVarNode));
			vecFBNode.push_back(fbInVarNode);
		}
		else if (string(n.name()) == "outVariable") {
			xmlConnectIn = n.child("connectionPointIn");
			xmlConnection = xmlConnectIn.child("connection");
			xmlexp = n.child("expression");
			exp = string(xmlexp.text().as_string());
			refLocalId = xmlConnection.attribute("refLocalId").as_string();
			formalParameter = xmlConnection.attribute("formalParameter").as_string();
			fbConnection = new FBConnection(refLocalId, formalParameter);
			fbOutVarNode = new FBOutVarNode(id, OutVar, fbConnection, exp);
			mapFBNodes.insert(make_pair(id, fbOutVarNode));
			vecFBNode.push_back(fbOutVarNode);
		}
		else if (string(n.name()) == "block") {
			fbTypeName = n.attribute("typeName").as_string();
			fbInstanceName = n.attribute("instanceName").as_string();
			fbBlockNode = new FBBlockNode(id, Block, fbTypeName, fbInstanceName);
			for (xml_node inputVar : n.child("inputVariables")) {
						varFormalParameter = inputVar.attribute("formalParameter").as_string();
						xmlConnectIn = inputVar.child("connectionPointIn");
						xmlConnection = xmlConnectIn.child("connection");
						refLocalId = xmlConnection.attribute("refLocalId").as_string();
						formalParameter = xmlConnection.attribute("formalParameter").as_string();
						fbConnection = new FBConnection(refLocalId, formalParameter);
						fbinterface = new FBInterface(varFormalParameter, fbConnection);
						fbBlockNode->inVars.push_back(fbinterface);
			}
			for (xml_node outVar : n.child("outputVariables")) {
				varFormalParameter = string(outVar.attribute("formalParameter").as_string());
				fbinterface = new FBInterface(varFormalParameter, nullptr);
				fbBlockNode->outVars.push_back(fbinterface);
			}
			mapFBNodes.insert(make_pair(id, fbBlockNode));
			vecFBNode.push_back(fbBlockNode);
		}
	}

	// 生成Process statement list
	ofstream il;
	il.open("OUTPUT\\FB_ICIL.il", std::ios::trunc);
	vector<FBNode*>::iterator it = vecFBNode.begin();
	FBNode* fbNode = nullptr;
	string op = "";
	string ICILExp = "";
	string temp = "";

	// 遍历所有的AND OR表达式，组织成ICIL表达式
	while (it!= vecFBNode.end()){
		fbNode = *it;
		if (fbNode->getType() != Block) {
			it++;
			continue;
		}
		if (fbNode->getFBTypeName() == "OR" || fbNode->getFBTypeName() == "AND") {
			if (fbNode->getFBTypeName() == "OR") {
				op = "||";
			}
			else {
				op = "&&";
			}
			ICILExp = "";
			for (FBInterface* in : fbNode->getInVars()) {
				/*temp = mapFBNodes[in->connection->refLocalId]->getFBOutput(in->connection->formalParameter);*/
				temp = this->getConnectionExp(in->connection);
				if (in == fbNode->getInVars()[0]) {
					ICILExp = ICILExp.append(temp);
				}
				else {
					ICILExp = ICILExp.append(op + temp);
				}
			}
			fbNode->setICILExp(ICILExp);
		}
		it++;
	}
	
	// 遍历所有其他节点，组成最终ICIL代码
	il << "Program() = " << std::endl;
	it = vecFBNode.begin();
	while (it != vecFBNode.end()) {
		fbNode = *it;
		if (fbNode->getType() == OutVar) {
			// expression = connection
			il << fbNode->getExp() << " = " << this->getConnectionExp(fbNode->getFBConnection()) << ";" << std::endl;
		}
		else if (fbNode->getType() == Block) {
			if (fbNode->getFBTypeName() == "OR" || fbNode->getFBTypeName() == "AND") {
				it++;
				continue;
			}
			// FB(arg0,arg1)
			il << fbNode->getInstanceName() << "(";
			for (FBInterface* in : fbNode->getInVars()) {
				if (in != fbNode->getInVars()[0]) {
					il << ",";
				}
				il << in->varFormalParameter << "=" << this->getConnectionExp(in->connection);
			}
			il << ");" << std::endl;
		}
		it++;
	}
	il.flush();
	il.close();
}

// 将LD转换为布尔表达式，只包含contact
string XMLParser::LDToBoolExp(LDNetworkTree* tree)
{
	string boolExp = "";
	LDExpNode* root = nullptr;
	LDExpNode* last = nullptr;
	for (LDNode* node : tree->vecTreeNode) {
		if (!node->isVirtualNode() && node->getType()==Contact) {
			LDExpNode* expNode = new LDExpNode(node->getID(), false);
			if (root == nullptr) {
				root = expNode;
			}
			if (last != nullptr) {
				last->next = expNode;
				expNode->prv = last;
			}
			last = expNode;
		}
	}

	LDExpNode* cn = root ->next;
	while (cn != nullptr) {
		// Do not apply the rules to operators
		if (cn->isOperator()) {
			cn = cn->next;
			continue;
		}
		// rule 1
		if (this->mapLDNodes[cn->getN()]->getPos()->x == this->mapLDNodes[cn->prv->getN()]->getPos()->x) {
			LDExpNode* n = new LDExpNode("&&", true);
			LDExpNode::insertExpNode(nullptr, n, cn);
		}
		else {
			// rule 2
			bool prvEnterCn = false;
			for (LDNode* node : mapLDNodes[cn->getN()]->inNodes) {
				if (cn->prv->getN() == node->getID()) {
					prvEnterCn = true;
					break;
				}
			}
			if (prvEnterCn) {
				LDExpNode* n = new LDExpNode("&&", true);
				LDExpNode::insertExpNode(nullptr, n, cn);
			}
			// rule 3
			else {
				LDExpNode* n = new LDExpNode("||", true);
				LDExpNode::insertExpNode(nullptr, n, cn);
			}
		}
		cn = cn->next;
	}

	// 遍历每个分叉点，在表达式链表中添加括号
	set<pair<string, string>> setPair;
	LDNode* mergeNode = nullptr;
	LDNode* l = nullptr;
	LDNode* r = nullptr;
	int s = 0;
	for (LDNode* n : tree->vecTreeNode) {
		if (n->outNodes.size() > 1) {
			mergeNode = addParenthesis(n, tree);
			if (mergeNode != nullptr) {
				l = n->outNodes[0];
				while (l->isVirtualNode() && !l->outNodes.empty()) {
					l = l->outNodes[0];
				}
				s = mergeNode->inNodes.size();
				r = mergeNode->inNodes[s - 1];
				setPair.insert(make_pair(l->getIDOrVnID(), r->getIDOrVnID()));
			}
		}
	}
	set<pair<string, string>>::iterator itSetPair = setPair.begin();
	LDExpNode* ldExpNode = root;
	while (itSetPair != setPair.end()) {
		ldExpNode = root;
		while (ldExpNode!=nullptr)
		{
			if (ldExpNode->getN() == itSetPair->first) {
				LDExpNode* l = new LDExpNode("(", true);
				LDExpNode::insertExpNode(nullptr, l, ldExpNode);
			}
			else if (ldExpNode->getN() == itSetPair->second) {
				LDExpNode* r = new LDExpNode(")", true);
				LDExpNode::insertExpNode(ldExpNode,r,nullptr);
				break;
			}
			ldExpNode = ldExpNode->next;
		}
		itSetPair++;
	}

	// 由于加括号时可能加在表达式首部，所以需要调整表达式的root
	while (root->prv != nullptr) {
		root = root->prv;
	}
	cn = root;
	while (cn != nullptr) {
		if (cn->isOperator()) {
			boolExp += cn->getN() + " ";
		}
		else {
			boolExp += mapLDNodes[cn->getN()]->getVar()->getName() + " ";
		}
		cn = cn->next;
	}
	return boolExp;
}

Variable * XMLParser::parseVar(xml_node xmlVar)
{
	Variable* var = nullptr;
	VarType varType = NullType;
	string varValue = "";

	xml_node type = xmlVar.child("type");
	if (type.child("BOOL")) {
		varType = Bool;
		varValue = "false";
	}
	if (type.child("INT")) {
		varType = Int;
		varValue = "0";
	}
	if (type.child("REAL")) {
		varType = Real;
		varValue = "0.0";
	}
	if (type.child("STRING")) {
		varType = String;
		varValue = "";
	}
	if (type.child("TIME")) {
		varType = Time;
		varValue = "T#0s";
	}
	// user defined type ...

	var = new Variable(varType, xmlVar.attribute("name").value(), varValue);
	return var;
}

// 多叉树转二叉树
void XMLParser::cutBranches(LDNode* branchNode, LDNetworkTree* tree)
{
	if (branchNode->outNodes.size() <= 2) {
		return;
	}

	// 切断原有的入边出边
	vector<LDNode*> outs = branchNode->outNodes;
	branchNode->outNodes.clear();

	LDNode* last = outs[0];
	LDNode* currRoot = nullptr;
	int i = 1;
	while (i < outs.size()) {
		if (i == outs.size() - 1) {
			currRoot = branchNode;
		}
		else {
			currRoot = new LDNode(this->virtualNodeNum);
			tree->vecTreeNode.push_back(currRoot);
			this->virtualNodeNum++;
		}

		currRoot->outNodes.push_back(last);
		currRoot->outNodes.push_back(outs[i]);
		// 需要将outs中原来为branchNode的位置用虚拟节点替换，除了outs中最后一个节点
		if (last->inNodes.size() > 0) {
			std::replace(last->inNodes.begin(), last->inNodes.end(), branchNode, currRoot);
		}
		else {
			last->inNodes.push_back(currRoot);
		}	
		if (i != outs.size() - 1) {
			std::replace(outs[i]->inNodes.begin(), outs[i]->inNodes.end(), branchNode, currRoot);
		}

		last = currRoot;
		i++;
	}
}

LDNode* XMLParser::addParenthesis(LDNode* branchNode, LDNetworkTree* tree)
{
	LDNode* mergeNode = nullptr;
	queue<LDNode*> q;
	// flag: 虚拟节点用vn*标记，普通节点用其id表示；

	// flag map
	unordered_map<string, set<string>> mapFlag;
	string nid = "";
	for (LDNode* n : tree->vecTreeNode) {
		if (n->isVirtualNode()) {
			nid = "vn" + std::to_string(n->getVirtualNodeID());
		}
		else {
			nid = n->getID();
		}
		set<string> setFlag;
		mapFlag.insert(make_pair(nid, setFlag));
	}

	// 所有分支的flag集合
	set<string> targetSetFlag;
	nid = "";
	for (LDNode* n : branchNode->outNodes) {
		q.push(n);
		if (n->isVirtualNode()) {
			nid = "vn" + std::to_string(n->getVirtualNodeID());
			targetSetFlag.insert(nid);
		}
		else {
			nid = n->getID();
			targetSetFlag.insert(nid);
		}
		mapFlag[nid].insert(nid);
	}

	// 寻找merge node
	LDNode* head = nullptr;
	string frontId = "";
	string outId = "";
	while (!q.empty()) {
		head = q.front();
		q.pop();
		if (head->isVirtualNode()) {
			frontId = "vn" + std::to_string(head->getVirtualNodeID());
		}
		else {
			frontId = head->getID();
		}

		bool same;
		for (LDNode* n : head->outNodes) {
			q.push(n);
			if (n->isVirtualNode()) {
				outId = "vn" + std::to_string(n->getVirtualNodeID());
			}
			else {
				outId = n->getID();
			}

			set_union(mapFlag[outId].begin(),mapFlag[outId].end(), mapFlag[frontId].begin(), mapFlag[frontId].end(), inserter(mapFlag[outId], mapFlag[outId].begin()));
			if (mapFlag[outId].size() != targetSetFlag.size()) {
				continue;
			}

			// 比较flag集合是否相同
			set<string>::iterator itOutFlag = mapFlag[outId].begin();
			set<string>::iterator itTargetFlag = targetSetFlag.begin();

			same = true;
			while (itOutFlag!= mapFlag[outId].end() && itTargetFlag!= targetSetFlag.end()){
				if (*itOutFlag != *itTargetFlag) {
					same = false;
				}
				itOutFlag++;
				itTargetFlag++;
			}
			if (same) {
				mergeNode = n;
				return mergeNode;
			}
		}
	}
}

string XMLParser::getConnectionExp(FBConnection* fbConnection)
{
	string connectionICIL = mapFBNodes[fbConnection->refLocalId]->getICILExp();
	if (connectionICIL != "") {
		return connectionICIL;
	}
	else if (fbConnection->formalParameter == "") {
		return mapFBNodes[fbConnection->refLocalId]->getExp();
	}
	else {
		return  mapFBNodes[fbConnection->refLocalId]->getInstanceName() + "." + fbConnection->formalParameter;
	}
}