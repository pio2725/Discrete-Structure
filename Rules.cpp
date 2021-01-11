#include "Rules.h"

Rules::Rules()
{

}

Rules::~Rules()
{
}

void Rules::setHeadName(std::string name)
{
	headPredName = name;
}

void Rules::setHeadPred(Predicate pred)
{
	headPred = pred;
}

void Rules::setBodyPred(Predicate pred)
{
	bodyPredVec.push_back(pred);
}

void Rules::bodyPredClear()
{
	bodyPredVec.clear();
}

void Rules::ToString()
{
	if (bodyPredVec.size() > 0)
	{
		std::cout << headPred.Tostring() << " :- ";
		std::cout << bodyPredVec.at(0).Tostring();
		for (unsigned int i = 1; i < bodyPredVec.size(); i++)
		{
			std::cout << "," << bodyPredVec.at(i).Tostring();
		}
		std::cout << "." << std::endl;
	}
}