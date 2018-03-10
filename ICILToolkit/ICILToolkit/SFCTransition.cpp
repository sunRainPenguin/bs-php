#include "SFCTransition.h"



SFCTransition::SFCTransition(SFCEleType type, string id):SFCEle(type)
{
	this->id = id;
	this->condition = nullptr;
}


SFCTransition::~SFCTransition()
{
}
