#include "Scanner.h"


Scanner::Scanner(std::string filename)
{
	lineNum = 1;
	this->filename = filename;
}

Scanner::~Scanner()
{
}

void Scanner::Tokenize()
{
	std::ifstream in;
	in.open(filename);

	int c;

	while (true)
	{
		c = in.get();

		if (c == EOF)
		{
			//++lineNum;
			Token tk(EOFILE, "", lineNum);
			//tk.ToString();

			tokens.push_back(tk);
			break;
		}

		switch (c)
		{
		case '.':
			FoundSpecific(PERIOD, ".", lineNum);
			break;
		case ',':
			FoundSpecific(COMMA, ",", lineNum);
			break;
		case '?':
			FoundSpecific(Q_MARK, "?", lineNum);
			break;
		case '(':
			FoundSpecific(LEFT_PAREN, "(", lineNum);
			break;
		case ')':
			FoundSpecific(RIGHT_PAREN, ")", lineNum);
			break;
		case ':':
			if (in.peek() == '-')
			{
				in.get();
				FoundSpecific(COLON_DASH, ":-", lineNum);
			}
			else
			{
				FoundSpecific(COLON, ":", lineNum);
			}
			break;
		case '*':
			FoundSpecific(MULTIPLY, "*", lineNum);
			break;
		case '+':
			FoundSpecific(ADD, "+", lineNum);
			break;
		case '\n':
		case ' ':
		case '\t':
			if (c == '\n')
			{
				++lineNum;
			}
			break;
		case 'S':
			//check Scemes
			IsSchemes(in);
			break;
		case 'F':
			IsFacts(in);
			break;
		case 'R':
			IsRules(in);
			break;
		case 'Q':
			IsQueries(in);
			break;
		case '\'':
			//string
			IsString(in);
			break;
		case '#':
			//comment
			IsComment(in);
			break;
		case '$':
		case '&':
		case '^':
			UndefinedTokens(c);
			break;
		default:
			//Identifier
			DefaultIdentifiers(c, in);
		}
	}
	in.close();

	//std::cout << "Total Tokens = " << tokens.size();
}

void Scanner::MakeIdentifiers(std::string IDstring)
{
	Token token(ID, IDstring, lineNum);
	//token.ToString();
	tokens.push_back(token);
}

void Scanner::DefaultIdentifiers(int c, std::ifstream& in)
{
	//1.letter + digit or letters
	//2. No start with digits
	//ex) 1person -> undefined 1 and ID person

	std::ostringstream os;
	std::string result;
	int input = 0;
	char ch = c;
	os << ch;

	if (isdigit(ch) || !isalpha(ch))
	{
		//Start with digit -> Undefined
		result = os.str();
		MakeUndefined(result, lineNum);
		return;
	}

	while (true)
	{
		if (isalpha(in.peek()) || isdigit(in.peek()))
		{
			input = in.get();
			os << (char)input;
		}
		else
		{
			result = os.str();
			Token token(ID, result, lineNum);
			//token.ToString();
			tokens.push_back(token);
			break;
		}
	}
}

void Scanner::UndefinedTokens(int c)
{
	char ch = c;
	std::string s(1, ch);

	Token token(UNDEFINED, s, lineNum);
	//token.ToString();
	tokens.push_back(token);
}

void Scanner::MakeUndefined(std::string undefinedString, int line)
{
	Token token(UNDEFINED, undefinedString, line);
	//token.ToString();
	tokens.push_back(token);
}

void Scanner::IsComment(std::ifstream& in)
{
	//1. single charachter
	std::ostringstream os;
	std::string result;
	int currentline = lineNum;
	os << "#";

	int c = 0;

	if (in.peek() == '|')
	{
		//could be muti-line comment
		c = in.get();
		os << (char)c;

		while (true)
		{
			if (in.peek() != EOF)
			{
				c = in.get();
				os << (char)c;
			}
			else
			{
				result = os.str();
				MakeUndefined(result, currentline);
				break;
			}


			if (c == '\n')
			{
				++lineNum;
			}

			if (c == '|')
			{
				if (in.peek() == '#')
				{
					c = in.get();
					os << (char)c;
					//valid comments
					result = os.str();
					//Token token(COMMENT, result, currentline);
					//token.ToString();
					//tokens.push_back(result);
					break;
				}
			}
			else if (c == EOF)
			{
				result = os.str();
				//std::cout << "Go make undefined: " << result << std::endl;
				MakeUndefined(result, currentline);
				break;
			}
		}
	}
	else
	{
		while (true)
		{
			if (in.peek() == '\n' || in.peek() == EOF)
			{
				//stop
				result = os.str();
				//Token token(COMMENT, result, currentline);
				//token.ToString();
				//tokens.push_back(result);
				break;
			}
			else
			{
				c = in.get();
				os << (char)c;
			}
		}
	}
}

void Scanner::IsString(std::ifstream& in)
{
	std::ostringstream os;
	os << "\'";
	int currentline = lineNum;
	std::string result;

	int c = 0;
	while (true)
	{

		if (in.peek() != EOF)
		{
			c = in.get();
			os << (char)c;
		}
		else
		{
			result = os.str();
			MakeUndefined(result, currentline);
			break;
		}

		if (c == '\n')
		{
			++lineNum;
		}

		if (c == '\'')
		{
			if (in.peek() == '\'')
			{
				c = in.get();
				os << (char)c;
			}
			else
			{
				result = os.str();
				Token token(STRING, result, currentline);
				//token.ToString();
				tokens.push_back(token);
				break;
			}
		}
		else if (in.peek() == EOF)
		{

			result = os.str();
			//std::cout << "Go make undefined : " << result << std::endl;
			//std::cout << currentline << std::endl;
			MakeUndefined(result, currentline);
			break;
		}

	}
}

void Scanner::IsQueries(std::ifstream& in)
{
	std::string temp = "Q";
	std::string target = "Queries";
	int c = 0;
	bool state = true;

	for (unsigned int i = 1; i < target.size(); i++)
	{
		if (in.peek() == target[i])
		{
			c = in.get();
			temp.push_back(c);
		}
		else
		{
			state = false;
			while (true)
			{
				if (isalpha(in.peek()))
				{
					c = in.get();
					temp.push_back(c);
				}
				else
				{
					break;
				}
			}
			break;
		}
	}

	if (state)
	{
		if (isalpha(in.peek()))
		{
			//Make it as ID
			while (true)
			{
				if (isalpha(in.peek()))
				{
					c = in.get();
					temp.push_back(c);
				}
				else
				{
					break;
				}
			}

			MakeIdentifiers(temp);
		}
		else
		{
			Token token(QUERIES, "Queries", lineNum);
			//token.ToString();
			tokens.push_back(token);
		}

	}
	else
	{
		//ID
		//std::cout << "Go make it " << temp << " as ID" << std::endl;
		MakeIdentifiers(temp);
	}
}

void Scanner::IsRules(std::ifstream& in)
{
	std::string temp = "R";
	std::string target = "Rules";
	int c = 0;
	bool state = true;

	for (unsigned int i = 1; i < target.size(); i++)
	{
		if (in.peek() == target[i])
		{
			c = in.get();
			temp.push_back(c);
		}
		else
		{
			state = false;
			while (true)
			{
				if (isalpha(in.peek()))
				{
					c = in.get();
					temp.push_back(c);
				}
				else
				{
					break;
				}
			}
			break;
		}
	}

	if (state)
	{
		if (isalpha(in.peek()))
		{
			//Make it as ID
			while (true)
			{
				if (isalpha(in.peek()))
				{
					c = in.get();
					temp.push_back(c);
				}
				else
				{
					break;
				}
			}

			MakeIdentifiers(temp);
		}
		else
		{
			Token token(RULES, "Rules", lineNum);
			//token.ToString();
			tokens.push_back(token);
		}
	}
	else
	{
		//ID
		//std::cout << "Go make it " << temp << " as ID" << std::endl;
		MakeIdentifiers(temp);
	}
}

void Scanner::IsFacts(std::ifstream& in)
{
	std::string temp = "F";
	std::string target = "Facts";
	int c = 0;
	bool state = true;

	for (unsigned int i = 1; i < target.size(); i++)
	{
		if (in.peek() == target[i])
		{
			c = in.get();
			temp.push_back(c);
		}
		else
		{
			state = false;
			while (true)
			{
				if (isalpha(in.peek()))
				{
					c = in.get();
					temp.push_back(c);
				}
				else
				{
					break;
				}
			}
			break;
		}
	}



	if (state)
	{
		if (isalpha(in.peek()))
		{
			//Make it as ID
			while (true)
			{
				if (isalpha(in.peek()))
				{
					c = in.get();
					temp.push_back(c);
				}
				else
				{
					break;
				}
			}

			MakeIdentifiers(temp);
		}
		else
		{
			Token token(FACTS, "Facts", lineNum);
			//token.ToString();
			tokens.push_back(token);
		}
	}
	else
	{
		//ID
		//std::cout << "Go make it " << temp << " as ID" << std::endl;
		MakeIdentifiers(temp);
	}

}

void Scanner::IsSchemes(std::ifstream& in)
{
	// S...... could be either Schemes or ID
	std::string temp = "S";
	std::string target = "Schemes";
	int c = 0;
	bool state = true;

	for (unsigned int i = 1; i < target.size(); i++)
	{
		if (in.peek() == target[i])
		{
			c = in.get();
			temp.push_back(c);
		}
		else
		{
			state = false;
			while (true)
			{
				if (isalpha(in.peek()))
				{
					c = in.get();
					temp.push_back(c);
				}
				else
				{
					break;
				}
			}
			break;
		}
	}

	if (state)
	{
		if (isalpha(in.peek()))
		{
			//Make it as ID
			while (true)
			{
				if (isalpha(in.peek()))
				{
					c = in.get();
					temp.push_back(c);
				}
				else
				{
					break;
				}
			}

			MakeIdentifiers(temp);
		}
		else
		{
			Token token(SCHEMES, "Schemes", lineNum);
			//token.ToString();
			tokens.push_back(token);
		}
	}
	else
	{
		//ID
		//std::cout << "Go make it " << temp << " as ID" << std::endl;
		MakeIdentifiers(temp);
	}
}

void Scanner::FoundSpecific(TokenType tk, std::string value, int linenum)
{
	Token token(tk, value, linenum);
	//token.ToString();
	tokens.push_back(token);
}

std::vector<Token> Scanner::getTokenVector() const
{
	return tokens;
}