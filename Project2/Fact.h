#pragma once
#include <string>
#include <vector>

///<summary>
/// This is the fact class
/// It holds a name and a list of string properties
/// That is pretty much it
///</summary>
class Fact
{
public:
	Fact(std::string);
	Fact(std::string id, std::string newProperty);
	~Fact();
	std::string getFactID();
	void addProperty(std::string);
	std::vector<std::string> getProperty();
	std::string _newProperty;
private:
	std::string _fact;
	std::vector<std::string> _properties;
	
	
	
};

