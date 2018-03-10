#include "SFCJumpStep.h"



SFCJumpStep::SFCJumpStep(SFCEleType type, string id, string tname):SFCEle(type)
{
	this->id = id;
	this->tname = tname;
}


SFCJumpStep::~SFCJumpStep()
{
}
