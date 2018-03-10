#ifndef _SFCCONVERTOR_H_
#define _SFCCONVERTOR_H_

#include "Constants.h"
#include "SFCAction.h"
#include "SFCStep.h"
#include "SFCInVariable.h"
#include "SFCTransition.h"
#include "SFCActionBlock.h"
#include "SFCJumpStep.h"
#include "SFCSimultaneousCv.h"
#include "SFCSimultaneousDv.h"

class SFCConvertor
{
private:
	unordered_map<string, SFCAction*> map_name_action;
	unordered_map<string, SFCInVariable*> map_id_action;
	unordered_map<string, SFCTransition*> map_id_transition;
	unordered_map<string, SFCActionBlock*> map_id_actionBlock;
	unordered_map<string, SFCJumpStep*> map_id_jumpstep;
	unordered_map<string, SFCSimultaneousCv*> map_id_simultaneousCv;
	unordered_map<string, SFCSimultaneousDv*> map_id_simultaneousDv;

public:
	SFCConvertor();
	~SFCConvertor();
};

#endif // _SFCCONVERTOR_H_