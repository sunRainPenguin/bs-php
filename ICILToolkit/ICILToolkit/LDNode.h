#include "Variable.h"

enum LDEleType {
	VirtualNode,
	Contact,
	Coil
};
struct Pos {
	int x;
	int y;
public:
	Pos(int x, int y);
};

class LDNode
{
private:
	int virtualNodeID;
	bool isVirtual;	// whether it is a virtual node()
	string ID;
	LDEleType type;
	Variable* var;
	bool negated;
	bool storage;
	Pos* pos;

public:
	vector<LDNode*> inNodes;
	vector<LDNode*> outNodes;
	LDNode(int virtualNodeID);
	LDNode(string ID, LDEleType type, Variable* var, bool negated, bool storage, Pos* pos);
	~LDNode();
	int getVirtualNodeID();
	bool isVirtualNode();
	string getID();
	string getIDOrVnID();
	LDEleType getType();
	Variable* getVar();
	bool isNegated();
	bool isStorage();
	Pos* getPos();

};

// 包含contact、virtual node的图
class LDNetworkTree {
private:
	int ID; // network ID
	LDNode* coil; // coil分解后的结果：一棵树只有一个coil

public:
	vector<LDNode*> vecTreeNode; // 一个network中的所有节点:由于目前拓扑排序没有用到虚拟节点，这里的虚拟节点暂时没有按照拓扑排序
	LDNetworkTree(int ID);
	void setCoil(LDNode* node);
	LDNode* getCoil();
};



