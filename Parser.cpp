#include "Parser.h"


Parser::Parser()
{
	position = -1;
}

Parser::~Parser()
{
}

Datalog Parser::Parse(std::vector<Token> tokens)
{
	//copying the vector
	this->tokens = tokens;

	try
	{
		//datalog parser
		DatalogParser();
		if (tokens.at(position + 1).getTokentype() != EOFILE)
		{
			//std::cout << position << " " << tokens.size() << std::endl;
			throw tokens.at(position + 1);
		}

		//printing out
		//datalog.ToString();
		//return datalog;
	}
	catch (Token tk)
	{
		//std::cout << "Failure!" << std::endl;
		//std::cout << "  ";
		//tk.ToString();
	}

	//find extra token

	//std::cout << position << tokens.size() << std::endl;
	return datalog;

}

void Parser::Match(TokenType tk)
{
	//Check if next token is what we want?
	++position; //next position

	if (tokens.at(position).getTokentype() != tk)
	{
		throw tokens.at(position);
	}
}

void Parser::DatalogParser()
{
	bool isfact = false;
	if (NextTokentype() != SCHEMES)
	{
		throw tokens.at(0);
	}
	Match(SCHEMES);
	Match(COLON);

	ParseSchemes();

	//Facts not required
	if (NextTokentype() == FACTS)
	{
		isfact = true;
		Match(FACTS);
		Match(COLON);
		ParseFactList();
	}

	//Rules not required
	if (NextTokentype() == RULES && isfact)
	{
		Match(RULES);
		Match(COLON);
		ParseRuleList();
	}
	else
	{
		throw tokens.at(position + 1);
	}


	//Queries required
	if (NextTokentype() != QUERIES)
	{
		throw tokens.at(position + 1);
	}

	Match(QUERIES);
	Match(COLON);

	ParseQueries();
	ParseQueriesList();
}

void Parser::ParseQueries()
{
	if (NextTokentype() != ID)
	{
		throw tokens.at(position + 1);
	}

	ParsePredQ();
	Match(Q_MARK);
}

void Parser::ParseQueriesList()
{
	if (NextTokentype() == ID)
	{
		ParseQueries();
		ParseQueriesList();
	}
}

void Parser::ParseRuleList()
{
	if (NextTokentype() == ID)
	{
		ParseRules();
		ParseRuleList();
	}
}

void Parser::ParseRules()
{
	ParseHeadPred();
	Match(COLON_DASH);
	ParsePred();
	ParsePredList();
	Match(PERIOD);

	//rule one line
	datalog.addRules(rule);
	rule.bodyPredClear();
}

void Parser::ParsePredList()
{
	if (NextTokentype() == COMMA)
	{
		Match(COMMA);
		ParsePred();
		ParsePredList();
	}
}

void Parser::ParsePred()
{
	Match(ID);
	pred.setName(tokens.at(position).getValue());

	Match(LEFT_PAREN);
	ParseParam();
	ParseParamList();

	Match(RIGHT_PAREN);
	rule.setBodyPred(pred);
	pred.clearVec(); // clear
}

void Parser::ParseParamList()
{
	if (NextTokentype() == COMMA)
	{
		Match(COMMA);
		ParseParam();
		ParseParamList();
	}
}

void Parser::ParseParam()
{
	if (NextTokentype() == STRING)
	{
		Match(STRING);
		pm.SetToken(tokens.at(position));
		pred.addParam(pm);
	}
	else if (NextTokentype() == ID)
	{
		Match(ID);
		pm.SetToken(tokens.at(position));
		pred.addParam(pm);
	}
	else if (NextTokentype() == LEFT_PAREN)
	{
		ParseExpression();
	}
	else
	{
		//double check!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		throw tokens.at(position + 1);
	}
}

void Parser::ParseExpression()
{
	Match(LEFT_PAREN);
	pm.SetToken(tokens.at(position));
	pred.addParam(pm);

	ParseParam();
	ParseOperator();
	ParseParam();

	Match(RIGHT_PAREN);
	pm.SetToken(tokens.at(position));
	pred.addParam(pm);
}

void Parser::ParseOperator()
{
	if (NextTokentype() == ADD)
	{
		Match(ADD);
		pm.SetToken(tokens.at(position));
		pred.addParam(pm);
	}
	else if (NextTokentype() == MULTIPLY)
	{
		Match(MULTIPLY);
		pm.SetToken(tokens.at(position));
		pred.addParam(pm);
	}
}

void Parser::ParseHeadPred()
{
	Match(ID);
	pred.setName(tokens.at(position).getValue());

	Match(LEFT_PAREN);

	Match(ID);
	pm.SetToken(tokens.at(position));
	pred.addParam(pm);

	ParseIdList();
	Match(RIGHT_PAREN);

	rule.setHeadPred(pred);
	pred.clearVec();
}

void Parser::ParseSchemes()
{
	if (NextTokentype() == FACTS || NextTokentype() == RULES || NextTokentype() == QUERIES)
	{
		throw tokens.at(position + 1);
	}


	Match(ID);

	pred.setName(tokens.at(position).getValue());

	Match(LEFT_PAREN);
	Match(ID);

	pm.SetToken(tokens.at(position));
	pred.addParam(pm);

	ParseIdList();

	Match(RIGHT_PAREN);

	//one predicate
	datalog.addSchemes(pred);
	pred.clearVec(); // clear

	ParseSchemeList();
}

void Parser::ParseIdList()
{
	//dealing with lamda
	if (tokens.at(position + 1).getTokentype() == COMMA)
	{
		Match(COMMA);
		Match(ID);
		pm.SetToken(tokens.at(position));
		pred.addParam(pm);

		ParseIdList();
	}
}

void Parser::ParseSchemeList()
{
	if (tokens.at(position + 1).getTokentype() == ID)
	{
		ParseSchemes();
		ParseSchemeList();
	}
}

void Parser::ParseFacts()
{
	Match(ID);
	pred.setName(tokens.at(position).getValue());

	Match(LEFT_PAREN);

	Match(STRING);
	pm.SetToken(tokens.at(position));
	pred.addParam(pm);
	datalog.addDomain(tokens.at(position).getValue());

	ParseStringList();

	Match(RIGHT_PAREN);
	Match(PERIOD);

	datalog.addFacts(pred);
	pred.clearVec(); // clear pred
}

void Parser::ParseStringList()
{
	if (NextTokentype() == COMMA)
	{
		Match(COMMA);
		Match(STRING);
		pm.SetToken(tokens.at(position));
		pred.addParam(pm);
		datalog.addDomain(tokens.at(position).getValue());

		ParseStringList();
	}
}

void Parser::ParseFactList()
{
	//called first
	if (NextTokentype() == ID)
	{
		ParseFacts();
		ParseFactList();
	}
}

TokenType Parser::NextTokentype()
{
	return tokens.at(position + 1).getTokentype();
}

void Parser::ParsePredQ()
{
	Match(ID);
	pred.setName(tokens.at(position).getValue());

	Match(LEFT_PAREN);
	ParseParamQ();
	ParseParamListQ();

	Match(RIGHT_PAREN);
	datalog.addQueries(pred);
	pred.clearVec(); // clear
}

void Parser::ParseParamQ()
{
	if (NextTokentype() == STRING)
	{
		Match(STRING);
		pm.SetToken(tokens.at(position));
		pred.addParam(pm);
	}
	else if (NextTokentype() == ID)
	{
		Match(ID);
		pm.SetToken(tokens.at(position));
		pred.addParam(pm);
	}
	else if (NextTokentype() == LEFT_PAREN)
	{
		ParseExpressionQ();
	}
	else
	{
		//double check!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		throw tokens.at(position + 1);
	}
}

void Parser::ParseParamListQ()
{
	if (NextTokentype() == COMMA)
	{
		Match(COMMA);
		ParseParamQ();
		ParseParamListQ();
	}
}

void Parser::ParseExpressionQ()
{
	Match(LEFT_PAREN);
	pm.SetToken(tokens.at(position));
	pred.addParam(pm);

	ParseParamQ();
	ParseOperator();
	ParseParamQ();

	Match(RIGHT_PAREN);
	pm.SetToken(tokens.at(position));
	pred.addParam(pm);
}