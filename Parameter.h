#ifndef PARAMETER_H
#define PARAMETER_H

#include <iostream>
#include <string>
#include "Token.h"

class Parameter
{
public:
	Parameter();
	Parameter(Token tk);
	
	~Parameter();

	std::string GetValue() const;
	void Tostring();
	void SetToken(Token tk);
	bool isConstant();
private:
	Token token;
	std::string value;
	int lineNum;
};

#endif