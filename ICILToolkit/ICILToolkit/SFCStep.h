#ifndef _SFCSTEP_H_
#define _SFCSTEP_H_
#include "Constants.h"
#include "SFCEle.h"

class SFCStep:SFCEle
{
public:
	string id;
	vector<SFCEle*> sfcPrvs;
	SFCStep(SFCEleType type, string id);
	~SFCStep();
};

#endif // !_SFCSTEP_H_ 