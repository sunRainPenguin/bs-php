#ifndef _SFCSIMULTANEOUSDV_H
#define _SFCSIMULTANEOUSDV_H

#include "Constants.h"
#include "SFCEle.h"

class SFCSimultaneousDv:SFCEle
{
public:
	string id;
	string name;
	SFCSimultaneousDv(SFCEleType type, string id, string name);
	~SFCSimultaneousDv();
};

#endif // !_SFCSIMULTANEOUSDV_H