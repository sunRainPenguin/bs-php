#ifndef _SFCSIMULTANEOUSCV_H
#define _SFCSIMULTANEOUSCV_H

#include "Constants.h"
#include "SFCEle.h"

class SFCSimultaneousCv:SFCEle
{
public:
	string id;
	vector<SFCEle*> sfcPrvs;
	SFCSimultaneousCv(SFCEleType type, string id);
	~SFCSimultaneousCv();
};

#endif // !_SFCSIMULTANEOUSCV_H