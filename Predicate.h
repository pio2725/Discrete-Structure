#ifndef PREDICATE_H
#define PREDICATE_H
#include "Parameter.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Predicate
{
public:
	Predicate();
	Predicate(std::string name);
	~Predicate();

	void addParam(Parameter pm);

	int ParamSize() const;

	std::string Tostring();

	void setName(std::string name);
	std::string getName();
	std::vector<Parameter> getParamVec();

	void clearVec();
protected:
	std::string name;
	std::vector<Parameter> Param;
};

#endif