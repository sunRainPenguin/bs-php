#include "FBNode.h"
class FBOutVarNode :
	public FBNode
{
private: 
	FBConnection* connection;
	string exp;

public:
	FBOutVarNode(string id, FBEleType type, FBConnection* connection, string exp);
	~FBOutVarNode();
	FBConnection* getFBConnection();
	string getExp();

};

