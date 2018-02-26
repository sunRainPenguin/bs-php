#include "FBOutVarNode.h"



FBOutVarNode::FBOutVarNode(string id, FBEleType type, FBConnection* connection, string exp)
	:FBNode(id,type)
{
	this->connection = connection;
	this->exp = exp;
}


FBOutVarNode::~FBOutVarNode()
{
}

FBConnection * FBOutVarNode::getFBConnection()
{
	return this->connection;
}
 
string FBOutVarNode::getExp()
{
	return this->exp;
}
