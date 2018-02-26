#include "LDNode.h"



LDNode::LDNode(int virtualNodeID)
{
	this->virtualNodeID = virtualNodeID;
	this->isVirtual = true;
	this->ID = "";
	this->type = VirtualNode;
	this->var = nullptr;
	this->negated = false;
	this->storage = false;
	this->pos = nullptr;
}

LDNode::LDNode(string ID, LDEleType type, Variable* var, bool negated, bool storage, Pos* pos)
{
	this->ID = ID;
	this->type = type;
	this->var = var;
	this->negated = negated;
	this->storage = storage;
	this->pos = pos;
	this->isVirtual = false;
	this->virtualNodeID = -1;
}


LDNode::~LDNode()
{
}

int LDNode::getVirtualNodeID()
{
	return this->virtualNodeID;
}

bool LDNode::isVirtualNode()
{
	return this->isVirtual;
}

string LDNode::getID()
{
	return this->ID;
}

string LDNode::getIDOrVnID()
{
	if (this->isVirtual) {
		return "vn" + std::to_string(this->virtualNodeID);
	}
	else {
		return this->ID;
	}
	return string();
}

LDEleType LDNode::getType()
{
	return this->type;
}

Variable * LDNode::getVar()
{
	return this->var;
}

bool LDNode::isNegated()
{
	return this->negated;
}

bool LDNode::isStorage()
{
	return this->storage;
}

Pos* LDNode::getPos()
{
	return this->pos;
}

LDNetworkTree::LDNetworkTree(int ID)
{
	this->ID = ID;
	this->coil = nullptr;
}

void LDNetworkTree::setCoil(LDNode * node)
{
	this->coil = node;
}

LDNode * LDNetworkTree::getCoil()
{
	return this->coil;
}

Pos::Pos(int x, int y)
{
	this->x = x;
	this->y = y;
}
