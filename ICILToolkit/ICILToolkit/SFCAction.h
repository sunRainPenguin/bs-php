#ifndef _SFCACTION_H_
#define _SFCACTION_H_

#include "Constants.h"
#include "PLCBody.h"
#include "SFCEle.h"

class SFCAction : SFCEle
{ 
public:
	string name;
	PLCBody* body;
	SFCAction(SFCEleType type, string name);
	~SFCAction();
};

#endif // !_SFCACTION_H_