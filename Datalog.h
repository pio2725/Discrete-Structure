#ifndef DATA_H
#define DATA_H

#include "Predicate.h"
#include "Rules.h"

#include <iostream>
#include <vector>
#include <set>
#include <string>

class Datalog
{
public:
	Datalog();
	~Datalog();

	void addSchemes(Predicate pred);
	void addFacts(Predicate pred);
	void addQueries(Predicate pred);
	void addRules(Rules rule);
	void addDomain(std::string s);

	std::vector<Predicate> GetSchemes();
	std::vector<Predicate> GetFacts();
	std::vector<Predicate> GetQueries();
	std::vector<Rules> GetRules();
	std::set<std::string> GetDomains();

	void ToString();

private:
	std::vector<Predicate> schemeVec;
	std::vector<Predicate> factVec;
	std::vector<Predicate> QueryVec;
	std::vector<Rules> ruleVec;
	std::set<std::string> domainSet;
};

#endif