#include "Datalog.h"

Datalog::Datalog()
{
}

Datalog::~Datalog()
{
}

void Datalog::addSchemes(Predicate pred)
{
	schemeVec.push_back(pred);
}

void Datalog::addFacts(Predicate pred)
{
	factVec.push_back(pred);
}

void Datalog::addRules(Rules rule)
{
	ruleVec.push_back(rule);
}

void Datalog::addQueries(Predicate pred)
{
	QueryVec.push_back(pred);
}

void Datalog::addDomain(std::string s)
{
	domainSet.insert(s);
}

void Datalog::ToString()
{
	std::cout << "Success!" << std::endl;

	//printing schemes
	std::cout << "Schemes(" << schemeVec.size() << "):" << std::endl;
	for (unsigned int i = 0; i < schemeVec.size(); i++)
	{
		std::cout << "  " << schemeVec.at(i).Tostring() << std::endl;
	}
	//printing facts
	std::cout << "Facts(" << factVec.size() << "):" << std::endl;
	for (unsigned int i = 0; i < factVec.size(); i++)
	{
		std::cout << "  " << factVec.at(i).Tostring() << "." << std::endl;
	}
	//printing rules
	std::cout << "Rules(" << ruleVec.size() << "):" << std::endl;
	for (unsigned int i = 0; i < ruleVec.size(); i++)
	{
		std::cout << "  ";
		ruleVec.at(i).ToString();
	}
	//printing queries
	std::cout << "Queries(" << QueryVec.size() << "):" << std::endl;
	for (unsigned int i = 0; i < QueryVec.size(); i++)
	{
		std::cout << "  " << QueryVec.at(i).Tostring() << "?" << std::endl;
	}
	//printing domain
	std::cout << "Domain(" << domainSet.size() << "):" << std::endl;
	for (std::set<std::string>::iterator itr = domainSet.begin(); itr != domainSet.end(); itr++)
	{
		std::cout << "  " << *itr << std::endl;
	}
}

std::vector<Predicate> Datalog::GetSchemes()
{
	return schemeVec;
}

std::vector<Predicate> Datalog::GetFacts()
{
	return factVec;
}

std::vector<Predicate> Datalog::GetQueries()
{
	return QueryVec;
}

std::vector<Rules> Datalog::GetRules()
{
	return ruleVec;
}

std::set<std::string> Datalog::GetDomains()
{
	return domainSet;
}