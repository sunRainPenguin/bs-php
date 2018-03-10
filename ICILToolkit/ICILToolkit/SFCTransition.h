#ifndef _SFCTRANSITION_H_
#define _SFCTRANSITION_H_

#include "Constants.h"
#include "SFCEle.h"

class SFCTransition:SFCEle
{
public:
	string id;
	vector<SFCEle*> sfcPrvs;
	SFCEle* condition;
	SFCTransition(SFCEleType type, string id);
	~SFCTransition();
};

#endif // !_SFCTRANSITION_H_