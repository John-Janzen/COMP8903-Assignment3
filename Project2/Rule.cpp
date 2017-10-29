#include "Rule.h"

/*Constructor*/
Rule::Rule() {}

/*Destructor*/
Rule::~Rule(){}

/*Get the result of the rule*/
void Rule::setResult(std::string s) { _result = s; }

/*Set a new rule condition or antecedent*/
void Rule::setPreReq(std::string s) { _conditions.emplace_back(s); }

/*Get the list of conditions or Antecendent*/
std::vector<std::string> Rule::getPreReq() { return _conditions; }

/*Get the result of the rule*/
std::string Rule::getResult() { return _result; }
