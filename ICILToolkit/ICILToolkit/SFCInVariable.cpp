#include "SFCInVariable.h"



SFCInVariable::SFCInVariable(SFCEleType type, string id, string exp):SFCEle(type)
{
	this->id = id;
	this->exp = exp;
}


SFCInVariable::~SFCInVariable()
{
}
