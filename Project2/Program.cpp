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
						rule->setPreReq(line3);	// add as a Antecedent for the rule

				else  if (count == 0 && line2.find(",") == std::string::npos)	// If there is not (,) sign then it is a single rule
					rule->setPreReq(line2);	// Add a single antecedent for the rule

				if (count != 0)
					rule->setResult(line2); // set rule result for the rule

				count++; // increment counter to make sure we set the result as a result and not some antecedent
			}
			_rules.emplace_back(rule);	// Put rule as a object in the rules vector
			
		}
		else {										// If not then it is a fact
			for each (Fact *fact in _facts) {		// Go through our list of facts
				if (fact->getFactID().compare(line) == 0) { // If they both have the same name then 
					contained = true;							// Flag that we already have a fact with the same name
				}
			}
			if (!contained) {									// If we have a fact with the same name skip
				Fact *newFact = new Fact(line);	// Make new fact with name
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
		std::cout << "Evaluated Fact #" << i++ << ": " << fact->getFactID() << "\n";
	}
	std::cin >> fileName;	// Enter anything to complete program
							// This is just to see the results

	inFile.close();			// Close the infile reader
}

/*
* Checks each fact against the rules
*/
void Program::checkAgainstFacts() {

	for each (Rule *rule in _rules) {		// For every rule
		int count = 0;
		bool contained = false;
		for each (std::string t in rule->getPreReq()) {	// And every antecedent

			
			for each (Fact *fact in _facts) { // For every fact we check the strings
				if (fact->getFactID().compare(t) == 0)							// If the fact and antecedent equal increment counter
					count++;

				if (fact->getFactID().compare(rule->getResult()) == 0)			// If the fact has a rule result that are the same flag that it already has it
					bool contained = true;
			}
			if (count == rule->getPreReq().size() && !contained) {	// Check if the fact meets the requirements for the rule and doesn't alreay contain it
				_evaluatedFacts.emplace_back(new Fact(rule->getResult())); // place a new fact for print out sake to show what was evalutated
				_facts.emplace_back(new Fact(rule->getResult()));
				count = 0;											// reset counter
			}
		}
	}
}
