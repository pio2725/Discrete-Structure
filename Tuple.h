#ifndef TUPLE_H
#define TUPLE_H
#include <iostream>
#include <string>
#include <vector>

class Tuple : public std::vector<std::string>
{
	//Tuple class itself can be treated like a vector
public:
	Tuple();
	~Tuple();
private:
};

#endif