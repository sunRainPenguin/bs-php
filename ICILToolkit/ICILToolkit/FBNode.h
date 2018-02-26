#ifndef _FBNODE_H_
#define _FBNODE_H_

#include "Constants.h"

enum FBEleType {
	InVar,
	OutVar,
	Block
};

struct FBConnection {
	string refLocalId;
	string formalParameter;
	FBConnection(string refLocalId, string formalParameter);
};

struct FBInterface {
	string varFormalParameter;
	FBConnection* connection;
	FBInterface(string varFormalParameter, FBConnection* connection);
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
	virtual string getExp();	// FBInVar FBOutVar
	virtual FBConnection* getFBConnection();	// FBOutVar
	virtual string getFBTypeName();	// FBBlock
	virtual string getInstanceName();	// FBBlock
	virtual string getICILExp();	// FBBlock
	virtual void setICILExp(string exp);	// FBBlock
	virtual string getFBOutput(string varFormalParameter);	// FBBlock
	virtual vector<FBInterface*> getInVars();	// FBBlock
	virtual vector<FBInterface*> getOutVars();	// FBBlock
};
#endif
