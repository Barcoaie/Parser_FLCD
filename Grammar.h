#pragma once
#include<string>
#include<map>
#include<vector>

class Grammar
{
private:
	std::string non_terminals = "";
	std::string terminals = "";
	char q0;
	std::map<char, std::vector<std::string>> productions = std::map<char, std::vector<std::string>>();
public:
	Grammar();

	/*
	Pre: string name must be valid and file must exist
	Post:
	Input: string
	Output:
	What it does: reads the input file given for the Grammar in the following form
		   - the set of non-terminals
		   - the terminals
		   - the initial state q0
		   - the set of productions
	*/
	void readFile(std::string filename);

	/*
	Pre:
	Post:
	Input:
	Output: string
	What it does: returns the grammar in a readable form
	*/
	std::string prettyPrint();

	/*
	Pre: char must be valid
	Post:
	Input: char
	Output: string
	What it does: returns the production values for a given non-terminal symbol
	*/
	std::string production_for_nonterminal(char q);

	std::vector<std::string> getProdForNonT(char q);

	char getInitialState();

	std::string getTerminals();

	std::string getNonTerminals();
	~Grammar();
};

