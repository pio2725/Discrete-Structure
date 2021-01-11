#ifndef RELATION_H
#define RELATION_H

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <sstream>

#include "Tuple.h"
#include "Scheme.h"

class Relation
{
public:
	Relation(std::string name, Scheme scheme);
	Relation();
	~Relation();

	void AddTuple(Tuple tupleToAdd);
	std::string GetRelationName();
	void ToString(Relation& relation, std::map<std::string, int>& trackingMap, std::vector<std::string>& nameList);

	Relation SelectType1(int position, std::string value, Relation& previousRelation);
	Relation SelectType2(int existingPosition, int newPosition2, Relation& previousRelation);
	Relation Project(std::vector<int>& positionList, Relation& previousRelation);
	Relation Rename(std::vector<std::string> namelist, std::map<std::string, int>& trackingMap, Relation& previousRelation);
private:
	std::string name;
	Scheme scheme;
	std::set<Tuple> tupleSet;

};

#endif