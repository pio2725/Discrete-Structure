#include "Predicate.h"

Predicate::Predicate()
{

}

Predicate::Predicate(std::string name)
{
	this->name = name;
}

Predicate::~Predicate()
{
	//Param.clear();
}

void Predicate::addParam(Parameter pm)
{
	Param.push_back(pm);
}


int Predicate::ParamSize() const
{
	return Param.size();
}

void Predicate::clearVec()
{
	Param.clear();
}

std::string Predicate::Tostring()
{
	std::ostringstream os;
	unsigned int index = 0;
	if (Param.size() > 0)
	{
		os << name << "(" << Param.at(0).GetValue();
		if (Param.at(0).GetValue() == "(")
		{
			std::string str = "";

			while (true)
			{
				while (Param.at(index).GetValue() != ")")
				{
					str.append(Param.at(index).GetValue());
					++index;
				}

				str.append(Param.at(index).GetValue());

				if ((index + 1) < Param.size())
				{
					if (Param.at(index + 1).GetValue() == "+" || Param.at(index + 1).GetValue() == "*" || Param.at(index + 1).GetValue() == ")")
					{
						//std::cout<<"here"<<std::endl; 
						++index;
						continue;
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}

			}

			while (str.find(",") != std::string::npos)
			{
				int k = str.find(",");
				str.erase(k, 1);
			}

			str.erase(0, 1);
			os << str;
		}

		for (unsigned int i = 1 + index; i < Param.size(); i++)
		{
			os << "," << Param.at(i).GetValue();

			//printing expression
			if (Param.at(i).GetValue() == "(")
			{
				std::string str = "";

				while (true)
				{
					while (Param.at(i).GetValue() != ")")
					{
						str.append(Param.at(i).GetValue());
						++i;
					}

					str.append(Param.at(i).GetValue());

					if ((i + 1) < Param.size())
					{
						if (Param.at(i + 1).GetValue() == "+" || Param.at(i + 1).GetValue() == "*" || Param.at(i + 1).GetValue() == ")")
						{
							//std::cout<<"here"<<std::endl; 
							++i;
							continue;
						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}


				}

				while (str.find(",") != std::string::npos)
				{
					int index = str.find(",");
					str.erase(index, 1);
				}

				str.erase(0, 1);
				os << str;
			}
		}
		os << ")";

	}




	return os.str();
}

void Predicate::setName(std::string name)
{
	this->name = name;
}

std::string Predicate::getName()
{
	return name;
}

std::vector<Parameter> Predicate::getParamVec()
{
	return Param;
}