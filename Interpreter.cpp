#include "Interpreter.h"

Interpreter::Interpreter(Datalog datalog)
{
	this->datalog = datalog;
}

Interpreter::~Interpreter()
{
}

void Interpreter::StartInterpreting()
{
	std::vector<Predicate> schemeVec = datalog.GetSchemes();

	//Scheme makes empty relations w/o tuples
	for (unsigned int i = 0; i < schemeVec.size(); i++)
	{
		std::string relationName = schemeVec.at(i).getName(); // Relation name
		std::vector<Parameter> paramVec = schemeVec.at(i).getParamVec();

		//Scheme for each relation
		Scheme scheme; //vector of string

		//Make scheme (Attributes)
		for (unsigned int j = 0; j < paramVec.size(); j++)
		{
			scheme.push_back(paramVec.at(j).GetValue());
		}

		//Make Relation
		Relation newRelation(relationName, scheme);
		database[relationName] = newRelation;
	}

	//Interpret Facts + add tuples
	InterpretingFacts();
	EvalQuery();
}

void Interpreter::InterpretingFacts()
{
	std::vector<Predicate> factsVec = datalog.GetFacts();
	
	for (unsigned int i = 0; i < factsVec.size(); i++)
	{
		std::string predName = factsVec.at(i).getName();
		std::vector<Parameter> paramVec = factsVec.at(i).getParamVec();

		// New strings of tuple for each
		Tuple tuple;

		//Push back values to tuple
		for (unsigned int j = 0; j < paramVec.size(); j++)
		{
			tuple.push_back(paramVec.at(j).GetValue());
		}

		// iterate to add tuple to appropriate relation
		std::map<std::string, Relation>::iterator itr;
		for (itr = database.begin(); itr != database.end(); itr++)
		{
			// If fact's predName == relationName
			if (itr->first == predName)
			{
				itr->second.AddTuple(tuple);
			}
		}
	}
}

void Interpreter::EvalQuery()
{
	std::vector<Predicate> queryVec = datalog.GetQueries();

	for (unsigned int i = 0; i < queryVec.size(); i++)
	{
		std::cout << queryVec.at(i).Tostring() << "? ";

		std::string predName = queryVec.at(i).getName();
		std::vector<Parameter> paramVec = queryVec.at(i).getParamVec();

		Relation emptyRelation;

		std::map<std::string, int> trackingMap; // variable(parameter) name and position column
		std::vector<int> positionLists;
		std::vector<std::string> nameList;

		//Copy the right relation to emptyRelation
		std::map<std::string, Relation>::iterator itr = database.begin();
		while (itr != database.end())
		{
			if (itr->first == predName)
			{
				emptyRelation = itr->second;
				break;
			}
			itr++;
		}

		// Should iterate through each paramters in the query
		for (unsigned int j = 0; j < paramVec.size(); j++)
		{
			//variable or constant?
			if (paramVec.at(j).isConstant() == true)
			{
				//Constant
				//Select type 1 (position, string value)
				int position = j;
				std::string value = paramVec.at(j).GetValue();

				//push back position for Projecting
				//positionLists.push_back(j);

				//emptyRelation gets new tuples
				emptyRelation = emptyRelation.SelectType1(position, value, emptyRelation);
			}
			else
			{
				//Variable
				//Type 2 select / traking for the same variable
				std::string variable = paramVec.at(j).GetValue();
				bool alreadyExists = false;
				int existingPosition;

				//Have we seen this variable before?
				for (std::map<std::string, int>::iterator itr = trackingMap.begin(); itr != trackingMap.end(); itr++)
				{
					if (itr->first == variable)
					{
						alreadyExists = true;
						existingPosition = itr->second;
					}
				}

				if (alreadyExists)
				{
					//SelectType2
					emptyRelation = emptyRelation.SelectType2(existingPosition, j, emptyRelation);
				}
				else
				{
					//Marking for variables
					//std::vector<std::string> nameList;
					nameList.push_back(variable); // using vector of newnames

					trackingMap[variable] = j; // -> used for Rename
					positionLists.push_back(j);
				}
				
			}

		} // End of iterating every parameter in the query

		//Project function
		emptyRelation = emptyRelation.Project(positionLists, emptyRelation);
		//Rename function
		emptyRelation = emptyRelation.Rename(nameList, trackingMap, emptyRelation);
		//output function
		emptyRelation.ToString(emptyRelation, trackingMap, nameList);
	}
}

