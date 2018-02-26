#include "FBBlockNode.h"



FBBlockNode::FBBlockNode(string ID, FBEleType type, string typeName, string instanceName):FBNode(ID, type)
{
	this->typeName = typeName;
	this->instanceName = instanceName;
	this->ICILExp = "";
}


FBBlockNode::~FBBlockNode()
{
}

string FBBlockNode::getFBTypeName()
{
	return this->typeName;
}

string FBBlockNode::getInstanceName()
{
	return this->instanceName;
}

string FBBlockNode::getICILExp()
{
	return this->ICILExp;
}

void FBBlockNode::setICILExp(string exp)
{
	this->ICILExp = exp;
}

string FBBlockNode::getFBOutput(string varFormalParameter)
{
	return this->instanceName + "." + varFormalParameter;
}

vector<FBInterface*> FBBlockNode::getInVars()
{
	return this->inVars;
}

vector<FBInterface*> FBBlockNode::getOutVars()
{
	return this->outVars;
}


