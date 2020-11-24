#pragma once
#include <string>
#include <stack>
#include "Node.h"
#include "Grammar.h"

class Parser
{
private:
	Grammar grammar;
	std::string cuvant;
	char state;
	int i;
	std::stack<std::string> working_stack;
	std::stack<char> input_stack;
public:
	Parser(Grammar g, std::string word);

	void expand();
	void advance();
	void momentary_insuccess();
	void back();
	void another_try();
	void success();

	void construct_tree(Node *& node, std::stack<std::string> & stack);

	std::string doamne_ajuta();

	~Parser();
};

