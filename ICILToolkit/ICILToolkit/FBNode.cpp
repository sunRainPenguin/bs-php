#include "FBNode.h"

FBInterface::FBInterface(string varFormalParameter, FBConnection* connection)
{
	this->varFormalParameter = varFormalParameter;
	this->connection = connection;
}

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

FBConnection * FBNode::getFBConnection()
{
	return nullptr;
}


string FBNode::getFBTypeName()
{
	return "";
}

string FBNode::getInstanceName()
{
	return "";
}

string FBNode::getICILExp()
{
	return "";
}

void FBNode::setICILExp(string exp)
{
}

string FBNode::getFBOutput(string varFormalParameter)
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

FBConnection::FBConnection(string refLocalId, string formalParameter)
{
	this->refLocalId = refLocalId;
	this->formalParameter = formalParameter;
}

