#include <iostream>
#include <string>
#include <vector>

#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"

//int main()
int main(int argc, char* argv[])
{
	//std::string filename = "est.txt";
	std::string filename = argv[1];

	Scanner scanthis(filename);
	scanthis.Tokenize();
	std::vector<Token> tokens = scanthis.getTokenVector();
	Parser parser;
	//parser.Parse(tokens);
	Datalog datalog = parser.Parse(tokens);
	Interpreter interpreter(datalog);
	interpreter.StartInterpreting();

	//system("pause");
	return 0;
}