#include "FBNode.h"

class FBBlockNode :
	public FBNode
{
private:

public:
	vector<FBInterface*> inVars;
	vector<FBInterface*> outVars;
	FBBlockNode(string ID, FBEleType type);
	~FBBlockNode();
	vector<FBInterface*> getInVars();
	vector<FBInterface*> getOutVars();
};

