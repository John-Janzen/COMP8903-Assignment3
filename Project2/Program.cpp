#include "Program.h"

Program::Program(){}

Program::~Program(){}

void Program::runProgram(char *c)
{
	std::string fileName;
	if (c == NULL) {
		std::cout << ">>Name of file \n"; //Instuctions
		char* cwd = _getcwd(0, 0);
		std::string working_directory(cwd);
		std::free(cwd);
		std::cout << ">>Current Directory: " << working_directory << "\n>>"; // Gives where the program is working from, to put the input files in
		
		std::cin >> fileName; // Waits for a file name

	}
	else {
		fileName = c;
	}
	std::string line;
	std::fstream inFile;
	inFile.open(fileName); // Opens file

	
	if (!inFile) {
		std::cout << "Unable to open file"; // If can't find file exits
		exit(1);
	}
	while (std::getline(inFile, line)) {
		line.erase(std::remove_if(line.begin(), line.end(), [](unsigned char x) {return std::isspace(x); }), line.end()); // Deletes any spaces
		std::stringstream ss(line);

		bool contained = false;

		if (line.find(">") != std::string::npos) {	// Checks if there is a (>) sign 
			Rule *rule = new Rule();				// If there is then it is a rule
			std::string line2;
			int count = 0;
			while (std::getline(ss, line2, '>')) {	// Get lines before and after the (>) sign
				std::stringstream ss2(line2);
				std::string line3;
				
				if (line2.find(",") != std::string::npos)	// If there is a (,) sign then it ahs multiple antecedents
					while (std::getline(ss2, line3, ','))	// Get strings between the (,) signs
						rule->setPreReq(line3.substr(0, line3.find("(")));	// add as a Antecedent for the rule

				else  if (count == 0 && line2.find(",") == std::string::npos)	// If there is not (,) sign then it is a single rule
					rule->setPreReq(line2.substr(0, line2.find("(")));	// Add a single antecedent for the rule

				if (count != 0)
					rule->setResult(line2.substr(0, line2.find("("))); // set rule result for the rule

				count++; // increment counter to make sure we set the result as a result and not some antecedent
			}
			_rules.emplace_back(rule);	// Put rule as a object in the rules vector
			
		}
		else {										// If not then it is a fact
			unsigned int first = line.find("(");	// find the "(" sign
			unsigned int last = line.find(")");		// find the ")" sign
			for each (Fact *fact in _facts) {		// Go through our list of facts
				if (fact->getFactID().compare(line.substr(first + 1, last - first - 1)) == 0) { // If they both have the same name then 
					fact->addProperty(line.substr(0, first));	// Just add a property			// there is no need for multiple objects of the same name
					contained = true;							// Flag that we already have a fact with the same name
				}
			}
			if (!contained) {									// If we have a fact with the same name skip
				Fact *newFact = new Fact(line.substr(first + 1, last - first - 1));	// Make new fact with name between the "("")"
				newFact->addProperty(line.substr(0, first));	// Add the property
				_facts.emplace_back(newFact);					// put in fact vector
				std::cout << "Fact: ";
				std::cout << newFact->getFactID();
				std::cout << "\n";
			}
		}
	}

	/// check against the fact for forward chainning
	checkAgainstFacts();

	int i = 0;
	for each (Fact* fact in _evaluatedFacts) { // Print out new evaluated facts
		std::cout << "Evaluated Fact #" << i++ << ": " << fact->_newProperty << "(" << fact->getFactID() << ")\n";
	}
	std::cin >> fileName;	// Enter anything to complete program
							// This is just to see the results

	inFile.close();			// Close the infile reader
}

/*
* Checks each fact against the rules
* Name should probably be checkAgainsRules
* ehh
*/
void Program::checkAgainstFacts() {
	
	for each (Fact *fact in _facts) {			// For every fact
		for each (Rule *rule in _rules) {		// We check against the rules
			int count = 0;
			bool contained = false;
			for each (std::string s in fact->getProperty()) {		// We read every property of the fact
				for each (std::string t in rule->getPreReq()) {		// And check against the antedcendents of the rules
					if (s.compare(t) == 0)							// If the fact and antecedent increment counter
						count++;

					if (s.compare(rule->getResult()) == 0)			// If the fact has a rule result that are the same flag that it already has it
						bool contained = true;
				}
				if (count == rule->getPreReq().size() && !contained) {	// Check if the fact meets the requirements for the rule and doesn't alreay contain it
					fact->addProperty(rule->getResult());				// add rule result to the properties
					_evaluatedFacts.emplace_back(new Fact(fact->getFactID(), rule->getResult())); // place a new fact for print out sake to show what was evalutated
					count = 0;											// reset counter
				}
			}
		}
	}
}
