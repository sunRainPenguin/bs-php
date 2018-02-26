#include "FBNode.h"

class FBBlockNode :
	public FBNode
{
private:
	string typeName;
	string instanceName;
	string ICILExp;

public:
	vector<FBInterface*> inVars;
	vector<FBInterface*> outVars;
	FBBlockNode(string ID, FBEleType type, string typeName, string instanceName);
	~FBBlockNode();
	string getFBTypeName();
	string getInstanceName();
	string getICILExp();
	void setICILExp(string exp);
	string getFBOutput(string varFormalParameter);		// ���FB.Q��ʽ���ַ���
	vector<FBInterface*> getInVars();
	vector<FBInterface*> getOutVars();
};

