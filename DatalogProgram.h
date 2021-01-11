#ifndef DATALOG_H
#define DATALOG_H

#include "Predicate.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>




class DatalogProgram // store lists and be able to return the vectors
{
public:
	DatalogProgram();
	~DatalogProgram();
	
	//void addSchemes(Predicate pd);
	

	void ToString();

protected:
	//std::vector<Predicate> SchemesVec;
	//std::vector<Predicate> Facts;
	//std::vector<Predicate> Queries;
	//std::vector<Rules> Rule;

	std::set<std::string> domainSet;
};

#endif