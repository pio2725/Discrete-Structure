#include "Parameter.h"

Parameter::Parameter()
{
}

Parameter::Parameter(Token tk)
{
	token = tk;
	value = token.getValue();
	lineNum = tk.getLinenum();
}

Parameter::~Parameter()
{
}

void Parameter::Tostring()
{
	std::string str;
}

std::string Parameter::GetValue() const
{
	return token.getValue();
}

void Parameter::SetToken(Token tk)
{
	token = tk;
}

bool Parameter::isConstant()
{
	if (token.getTokentype() == STRING)
	{
		return true;
	}
	//else if (token.getTokentype() == ID)
	//{
		//return false;
	//}
	return false;
}