#pragma once
#include <vector>

#include "Fact.h"

///<summary>
/// This is the rule class
/// It holds a name and a list of string conditions or antecendents
///</summary>
class Rule
{
public:
	Rule();
	~Rule();
	void setResult(std::string);
	void setPreReq(std::string);
	std::vector<std::string> getPreReq();
	std::string getResult();
	
private:
	std::vector<std::string> _conditions;
	std::string _result;
};

