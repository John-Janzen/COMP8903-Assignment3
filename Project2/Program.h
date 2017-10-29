#pragma once
#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <direct.h>
#include <vector>
#include <algorithm>
#include <cctype>


#include "Fact.h"
#include "Rule.h"



class Program
{
public:
	Program();
	~Program();
	void runProgram(char*);
	void checkAgainstFacts();
private:
	std::vector<Fact*> _facts;
	std::vector<Rule*> _rules;
	std::vector<Fact*> _evaluatedFacts;
};

