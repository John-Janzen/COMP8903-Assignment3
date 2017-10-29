#include "Fact.h"

/*Just set the fact name*/
Fact::Fact(std::string id) { _fact = id; }

/*Set fact name and new result, this is mostly for the evaluated facts*/
Fact::Fact(std::string id, std::string newProperty) {
	_fact = id;
	_newProperty = newProperty;
}

/*Destructor*/
Fact::~Fact(){}

/*Get the fact id (which is just the name)*/
std::string Fact::getFactID(){ return _fact; }

/*Add a new property to the list of properties*/
void Fact::addProperty(std::string s) { _properties.emplace_back(s); }

/*Get the list of properties*/
std::vector<std::string> Fact::getProperty() { return _properties; }