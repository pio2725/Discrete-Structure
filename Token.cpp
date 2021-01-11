#include "Token.h"

Token::Token(TokenType tokentype, std::string value, int lineNum)
{
	this->tokentype = tokentype;
	this->value = value;
	this->lineNum = lineNum;
}

Token::Token()
{

}

Token::~Token()
{
}

std::string Token::TokentypeToString(TokenType ttype)
{
	switch (ttype)
	{
		case COMMA: return "COMMA"; break;
		case PERIOD: return "PERIOD"; break;
		case Q_MARK: return "Q_MARK"; break;
		case LEFT_PAREN: return "LEFT_PAREN"; break;
		case RIGHT_PAREN: return "RIGHT_PAREN"; break;
		case COLON: return "COLON"; break;
		case COLON_DASH: return "COLON_DASH"; break;
		case MULTIPLY: return "MULTIPLY"; break;
		case ADD: return "ADD"; break;
		case SCHEMES: return "SCHEMES"; break;
		case FACTS: return "FACTS"; break;
		case RULES: return "RULES"; break;
		case QUERIES: return "QUERIES"; break;
		case ID: return "ID"; break;
		case STRING: return "STRING"; break;
		case COMMENT: return "COMMENT"; break;
		case UNDEFINED: return "UNDEFINED"; break;
		case EOFILE: return "EOF"; break;
	}
	return "Error";
}

void Token::ToString()
{
	std::ostringstream os;

	os << "(" << TokentypeToString(tokentype) << ",\"" << value << "\"," << lineNum << ")" << std::endl;
	std::string result;
	result = os.str();

	std::cout << result;
}

int Token::getLinenum() const
{
	return lineNum;
}

std::string Token::getValue() const
{
	return value;
}

TokenType Token::getTokentype()
{
	return tokentype;
}