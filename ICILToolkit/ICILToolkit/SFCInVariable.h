#ifndef _SFCINVARIABLE_H_
#define _SFCINVARIABLE_H_

#include "Constants.h"
#include "SFCEle.h"

class SFCInVariable:SFCEle
{
public:
	string id;
	string exp;
	SFCInVariable(SFCEleType type, string id, string exp);
	~SFCInVariable();
};

#endif // !_SFCINVARIABLE_H_