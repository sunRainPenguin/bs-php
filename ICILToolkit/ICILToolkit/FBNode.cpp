#include "FBNode.h"


FBNode::FBNode(string ID, FBEleType type)
{
	this->ID = ID;
	this->type = type;
}

FBNode::~FBNode()
{
}

FBEleType FBNode::getType()
{
	return this->type;
}

string FBNode::getID()
{
	return this->ID;
}

string FBNode::getExp()
{
	return "";
}

string FBNode::getRefLocalId()
{
	return "";
}

string FBNode::getFormalParameter()
{
	return "";
}

vector<FBInterface*> FBNode::getInVars()
{
	return vector<FBInterface*>();
}

vector<FBInterface*> FBNode::getOutVars()
{
	return vector<FBInterface*>();
}


