#include "Grammar.h"
#include<fstream>

Grammar::Grammar()
{
}

void Grammar::readFile(std::string filename)
{
	std::ifstream infile(filename);
	std::string line;
	std::string delimiter = ",";
	size_t pos = 0;
	std::string token;

	std::getline(infile, line);
	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		non_terminals = non_terminals + token;
		line.erase(0, pos + delimiter.length());
	}
	non_terminals = non_terminals + line;

	pos = 0;
	std::getline(infile, line);
	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		terminals = terminals + token;
		line.erase(0, pos + delimiter.length());
	}
	terminals = terminals + line;

	std::getline(infile, line);
	q0 = line[0];

	std::string eq = " = ";
	std::string bara = " | ";
	while (std::getline(infile, line)) {
		std::string start, val;
		pos = line.find(eq);
		start = line.substr(0, pos);
		line.erase(0, pos + eq.length()); 
		while ((pos = line.find(bara)) != std::string::npos) {
			token = line.substr(0, pos);
			productions[start[0]].push_back(token);
			line.erase(0, pos + bara.length());
		}
		productions[start[0]].push_back(line);
	}
}

std::string Grammar::prettyPrint()
{
	std::string res = "";
	res = res + "Set of non-terminal symbols: " + this->non_terminals + "\n";
	res = res + "Set of terminal symbols: " + this->terminals + "\n";
	res = res + "Start symbol: " + this->q0 + "\n";
	res = res + "Set of productions:\n";
	for (std::map<char, std::vector<std::string>>::iterator it = productions.begin(); it != productions.end(); ++it) {
		res = res + it->first + " = ";
		for (auto n : it->second) {
			res = res + n + " | ";
		}
		res.erase(res.length() - 2, res.length());
		res = res + "\n";
	}
	return res;
}

std::string Grammar::production_for_nonterminal(char q)
{
	std::string res = "";
	for (auto n : productions[q]) {
		res = res + n + " | ";
	}
	res.erase(res.length() - 2, res.length());
	return res;
}

std::vector<std::string> Grammar::getProdForNonT(char q)
{
	return productions[q];
}

char Grammar::getInitialState()
{
	return q0;
}

std::string Grammar::getTerminals()
{
	return terminals;
}

std::string Grammar::getNonTerminals()
{
	return non_terminals;
}

Grammar::~Grammar()
{
}
