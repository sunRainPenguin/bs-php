#ifndef _FBNODE_H_
#define _FBNODE_H_

#include <string>
#include <vector>
using std::string;
using std::vector;

enum FBEleType {
	InVar,
	OutVar,
	Block
};

struct FBInterface {
	string formalParameter;
	string refLocalId;
	FBInterface(string formalParameter, string refLocalId);
};

class FBNode
{
private:
	string ID;
	FBEleType type;

public:
	FBNode(string ID, FBEleType type);
	~FBNode();
	FBEleType getType();
	string getID();
	virtual string getExp();
	virtual string getRefLocalId();
	virtual string getFormalParameter();
	virtual vector<FBInterface*> getInVars();
	virtual vector<FBInterface*> getOutVars();
};
#endif
