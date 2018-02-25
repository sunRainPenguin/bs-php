#include "FBBlockNode.h"



FBBlockNode::FBBlockNode(string ID, FBEleType type):FBNode(ID, type)
{
}


FBBlockNode::~FBBlockNode()
{
}

vector<FBInterface*> FBBlockNode::getInVars()
{
	return this->inVars;
}

vector<FBInterface*> FBBlockNode::getOutVars()
{
	return this->outVars;
}

FBInterface::FBInterface(string formalParameter, string refLocalId)
{
	this->formalParameter = formalParameter;
	this->refLocalId = refLocalId;
}
