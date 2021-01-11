#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>

#include "Token.h"


class Scanner
{
public:
	Scanner(std::string filename);
	~Scanner();

	void Tokenize();

	void FoundSpecific(TokenType tk, std::string value, int linenum);
	void IsSchemes(std::ifstream& in);
	void IsFacts(std::ifstream& in);
	void IsRules(std::ifstream& in);
	void IsQueries(std::ifstream& in);

	void IsString(std::ifstream& in);
	void IsComment(std::ifstream& in);

	void MakeUndefined(std::string undefinedString, int line);
	void UndefinedTokens(int c);

	void MakeIdentifiers(std::string IDstring);
	void DefaultIdentifiers(int c, std::ifstream& in);

	std::vector<Token> getTokenVector() const;

protected:
	TokenType tokentype;
	std::string value;
	std::string filename;
	int lineNum;
	std::vector<Token> tokens;
};

#endif