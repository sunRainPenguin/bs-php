#include "FBInVarNode.h"



FBInVarNode::FBInVarNode(string id, FBEleType type, string exp):FBNode(id,type)
{
	this->exp = exp;
}


FBInVarNode::~FBInVarNode()
{
}

string FBInVarNode::getExp()
{
	return this->exp;
}
