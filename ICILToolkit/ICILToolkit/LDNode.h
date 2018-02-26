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

// ����contact��virtual node��ͼ
class LDNetworkTree {
private:
	int ID; // network ID
	LDNode* coil; // coil�ֽ��Ľ����һ����ֻ��һ��coil

public:
	vector<LDNode*> vecTreeNode; // һ��network�е����нڵ�:����Ŀǰ��������û���õ�����ڵ㣬���������ڵ���ʱû�а�����������
	LDNetworkTree(int ID);
	void setCoil(LDNode* node);
	LDNode* getCoil();
};



