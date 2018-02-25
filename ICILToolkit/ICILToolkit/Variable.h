#pragma once
#include <string>
using std::string;

enum VarType {
	NullType,
	Bool,
	Int,
	Real,
	String,
	Time,
	UDT		// user define type
};

class Variable
{
private:
	VarType type;
	string name;
	string value;

public:
	Variable(VarType type, string name, string value)
	{
		this->type = type;
		this->name = name;
		this->value = value;
	}
	~Variable();

	VarType getType();
	string getName();
	string getValue();

};

