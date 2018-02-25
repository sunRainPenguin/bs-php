#include "FBOutVarNode.h"



FBOutVarNode::FBOutVarNode(string id, FBEleType type, string refLocalId, string formalParameter, string exp)
	:FBNode(id,type)
{
	this->refLocalId = refLocalId;
	this->formalParameter = formalParameter;
	this->exp = exp;
}


FBOutVarNode::~FBOutVarNode()
{
}

string FBOutVarNode::getRefLocalId()
{
	return this->refLocalId;
}

string FBOutVarNode::getFormalParameter()
{
	return this->formalParameter;
}

string FBOutVarNode::getExp()
{
	return this->exp;
}
