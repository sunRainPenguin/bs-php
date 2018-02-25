#include "FBNode.h"
class FBInVarNode :
	public FBNode
{
private:
	string exp;

public:
	FBInVarNode(string id, FBEleType type, string exp);
	~FBInVarNode();
	string getExp();
};

