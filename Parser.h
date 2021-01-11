#ifndef PARSER_H
#define PARSER_H

#include "Datalog.h"

#include <iostream>
#include <vector>
#include <string>

class Parser 
{
public:
	Parser();
	~Parser();
	void Match(TokenType tk);
	Datalog Parse(std::vector<Token> tokens);
	
	void DatalogParser();
	void ParseSchemes();
	void ParseIdList();
	void ParseSchemeList();

	void ParseFacts();
	void ParseFactList();

	void ParseRuleList();
	void ParseRules();

	void ParseQueries();
	void ParseQueriesList();

	void ParseStringList();

	void ParseHeadPred();
	void ParsePred();
	void ParsePredList();

	void ParseParam();
	void ParseParamList();

	void ParseExpression();
	void ParseOperator();

	//Quereis
	void ParsePredQ();
	void ParseParamQ();
	void ParseParamListQ();
	void ParseExpressionQ();

	TokenType NextTokentype();
	
private:
	std::vector<Token> tokens;
	TokenType tokentype;
	int position;
	Token currenToken;
	Predicate pred;
	Parameter pm;
	Datalog datalog;
	Rules rule;
};

#endif