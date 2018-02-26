#include "Constants.h"

class LDExpNode
{
private:
	string n;	// The LD expression element(!op: LDNode id, op: op symbol)
	bool isOp;	// Whether "n" is an operator symbol("(",")","+","*")

public:
	LDExpNode* next;
	LDExpNode* prv;
	LDExpNode(string n, bool isOp);
	~LDExpNode();
	string getN();
	bool isOperator();
	static void insertExpNode(LDExpNode* posFollow, LDExpNode* n, LDExpNode* posBefore); // insert a node before the pos
};

