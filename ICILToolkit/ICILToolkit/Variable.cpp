#include "Variable.h"



Variable::~Variable()
{
}

VarType Variable::getType()
{
	return this->type;
}

string Variable::getName()
{
	return this->name;
}

string Variable::getValue()
{
	return this->value;
}
