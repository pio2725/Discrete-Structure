#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

enum TokenType
{
	COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
	MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT,
	UNDEFINED, EOFILE
};

class Token
{
public:
	Token(TokenType tokentype, std::string value, int lineNum);
	Token();
	~Token();
	void ToString();
	std::string TokentypeToString(TokenType ttype);
	int getLinenum() const;
	std::string getValue() const;
	TokenType getTokentype();

private:
	std::string value;
	int lineNum;
	TokenType tokentype;
	//std::vector<TokenType> tokentypesVec;
};

#endif

