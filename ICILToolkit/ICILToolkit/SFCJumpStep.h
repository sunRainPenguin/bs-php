#ifndef _SFCJUMPSTEP_H_
#define _SFCJUMPSTEP_H_

#include "Constants.h"
#include "SFCEle.h"

class SFCJumpStep:SFCEle
{
public:
	string id;
	string tname;
	vector<SFCEle*> sfcPrvs;
	SFCJumpStep(SFCEleType type, string id, string tname);
	~SFCJumpStep();
};

#endif // !_SFCJUMPSTEP_H_