#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <vector>
#include <string>

#include "Database.h"
#include "Datalog.h"

class Interpreter
{
public:
	Interpreter(Datalog datalog);
	~Interpreter();

	//make a relation for every scheme
	//put it into database map
	void StartInterpreting();
	void InterpretingFacts();

	void EvalQuery();
private:
	Datalog datalog;
	Database database;
};

#endif