#include "Relation.h"

Relation::Relation(std::string name, Scheme scheme)
{
	this->name = name;
	this->scheme = scheme;
}

Relation::Relation()
{
}

Relation::~Relation()
{
}

void Relation::AddTuple(Tuple tupleToAdd)
{
	tupleSet.insert(tupleToAdd);
}

void Relation::ToString(Relation& relation, std::map<std::string, int>& trackingMap, std::vector<std::string>& nameList)
{
	if (relation.tupleSet.empty())
	{
		//output the query
		std::cout << "No" << std::endl;
	}
	else
	{
		std::cout << "Yes(" << relation.tupleSet.size() << ")" << std::endl;

		if (!trackingMap.empty())
		{
			if (trackingMap.size() == 1)
			{
				for (unsigned int i = 0; i < nameList.size(); i++)
				{
					for (std::set<Tuple>::iterator itr = relation.tupleSet.begin(); itr != relation.tupleSet.end(); itr++)
					{
						std::cout << "  " << nameList.at(i) << "=" << (*itr).at(i) << std::endl;
					}
				}
			}
			else
			{
				//two or more variables
				for (std::set<Tuple>::iterator itr = relation.tupleSet.begin(); itr != relation.tupleSet.end(); itr++)
				{
					std::ostringstream os;

					os << "  ";
					for (unsigned int i = 0; i < (*itr).size(); i++)
					{
						os << nameList.at(i) << "=" << (*itr).at(i) << ", ";
					}
					os << std::endl;

					std::string temp = os.str();
					temp.erase(temp.size()-3, 2); // erase the last comma
					std::cout << temp;
				}
				
				


			}
		}
	}
}

std::string Relation::GetRelationName()
{
	return name;
}

Relation Relation::SelectType1(int position, std::string value, Relation& previousRelation)
{
	Relation newRelation;
	newRelation.name = previousRelation.name;
	newRelation.scheme = previousRelation.scheme;

	for (std::set<Tuple>::iterator itr = previousRelation.tupleSet.begin(); itr != previousRelation.tupleSet.end(); itr++)
	{
		if ((*itr).at(position) == value)
		{
			//Add matching tuples
			newRelation.AddTuple((*itr));
		}
	}

	return newRelation;
}

Relation Relation::SelectType2(int existingPosition, int newPosition, Relation& previousRelation)
{
	Relation newRelation;
	newRelation.name = previousRelation.name;
	newRelation.scheme = previousRelation.scheme;

	// column positions
	for (std::set<Tuple>::iterator itr = previousRelation.tupleSet.begin(); itr != previousRelation.tupleSet.end(); itr++)
	{
		std::vector<std::string> temp = (*itr);
		if (temp.at(existingPosition) == temp.at(newPosition))
		{
			//addTuple
			newRelation.AddTuple((*itr));
		}
	}
	return newRelation;
}

Relation Relation::Project(std::vector<int>& positionList, Relation& previousRelation)
{
	Relation newRelation;
	newRelation.name = previousRelation.name;
	//newRelation.scheme = previousRelation.scheme;

	// only columns in the position vector

	//copying new scheme
	for (unsigned int i = 0; i < positionList.size(); i++)
	{
		newRelation.scheme.push_back(previousRelation.scheme.at(positionList.at(i)));
	}

	//Dealing w/ tuples
	for (std::set<Tuple>::iterator itr = previousRelation.tupleSet.begin(); itr != previousRelation.tupleSet.end(); itr++)
	{
		Tuple newTuple;
		std::vector<std::string> temp = (*itr);

		for (unsigned int i = 0; i < positionList.size(); i++)
		{
			newTuple.push_back(temp.at(positionList.at(i)));
		}
		newRelation.AddTuple(newTuple);
	}

	return newRelation;
}

//get vector of names(scheme)
Relation Relation::Rename(std::vector<std::string> namelist, std::map<std::string, int>& trackingMap, Relation& previousRelation)
{
	Relation newRelation;

	newRelation = previousRelation;

	//for (std::map<std::string, int>::iterator itr = trackingMap.begin(); itr != trackingMap.end(); itr++)
	//{
	//	int position = itr->second;
	//	std::string newName = itr->first;

	//	//DOUBLE CHECK
	//	newRelation.scheme.at(position) = newName;
	//}

	//in order?
	for (unsigned int i = 0; i < namelist.size(); i++)
	{
		newRelation.scheme.at(i) = namelist.at(i);
	}

	return newRelation;
}