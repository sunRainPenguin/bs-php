#include "LDExpNode.h"



LDExpNode::LDExpNode(string n, bool isOp)
{
	this->n = n;
	this->isOp = isOp;
	this->next = nullptr;
	this->prv = nullptr;
}


LDExpNode::~LDExpNode()
{
}

string LDExpNode::getN()
{
	return this->n;
}

bool LDExpNode::isOperator()
{
	return this->isOp;
}

void LDExpNode::insertExpNode(LDExpNode* posFollow, LDExpNode* n, LDExpNode* posBefore)
{
	if (posBefore != nullptr && posFollow != nullptr) {
		return;		// not valid
	}
	if (posBefore != nullptr) {
		if (posBefore->prv != nullptr) {
			posBefore->prv->next = n;
			n->prv = posBefore->prv;
		}
		posBefore->prv = n;
		n->next = posBefore;
	}
	else if(posFollow != nullptr){
		if (posFollow->next != nullptr) {
			posFollow->next->prv = n;
			n->next = posFollow->next;
		}
		posFollow->next = n;
		n->prv = posFollow;
	}
}

