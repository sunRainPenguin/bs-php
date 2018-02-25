#include "FBNode.h"
class FBOutVarNode :
	public FBNode
{
private: 
	string refLocalId;
	string formalParameter;
	string exp;

public:
	FBOutVarNode(string id, FBEleType type, string refLocalId, string formalParameter, string exp);
	~FBOutVarNode();
	string getRefLocalId();
	string getFormalParameter();
	string getExp();

};

