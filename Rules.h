#ifndef RULES_H
#define RULES_H

#include <iostream>
#include <vector>
#include "Token.h"
#include "Predicate.h"

class Rules
{
public:
	Rules();
	~Rules();

	void ToString();

	void setHeadName(std::string name);

	void setHeadPred(Predicate pred);
	void setBodyPred(Predicate pred);
	void bodyPredClear();
private:
	std::vector<Predicate> bodyPredVec;
	std::string headPredName;
	Predicate headPred;
};

#endif