#include "SFCActionBlock.h"



SFCActionBlock::SFCActionBlock(SFCEleType type, string id, string qualifier):SFCEle(type)
{
	this->id = id;
	this->qualifier = qualifier;
}


SFCActionBlock::~SFCActionBlock()
{
}
