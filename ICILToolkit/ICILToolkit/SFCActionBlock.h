#ifndef _SFCACTIONBLOCK_H_
#define _SFCACTIONBLOCK_H_

#include "Constants.h"
#include "SFCEle.h"
#include "SFCAction.h"
class SFCActionBlock:SFCEle
{
public:
	string id;
	vector<SFCEle*> sfcPrvs; // step
	string qualifier;
	SFCAction* action;
	SFCActionBlock(SFCEleType type, string id, string qualifier);
	~SFCActionBlock();
};

#endif // !_SFCACTIONBLOCK_H_