#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <map>

#include "Relation.h"

class Database : public std::map<std::string, Relation>
{
	//relations
public:
	Database();
	~Database();
protected:
};

#endif