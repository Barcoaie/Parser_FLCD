#include "Parser.h"
#include<iostream>

Parser::Parser(Grammar g, std::string word)
{
	grammar = g;
	cuvant = word;
	state = 'q';
	i = 0;
	working_stack = std::stack<std::string>();
	input_stack.push(grammar.getInitialState());
}

void Parser::expand()
{
	//ma doare capul
	char ch = input_stack.top();
	input_stack.pop();
	std::vector<std::string> prods = grammar.getProdForNonT(ch);
	std::reverse(prods[0].begin(), prods[0].end());
	for (auto c : prods[0]) {
		input_stack.push(c);
	}
	std::string string_ch = std::string(1, ch) + "0";
	working_stack.push(string_ch);
}

void Parser::advance()
{
	i++;
	char ch = input_stack.top();
	input_stack.pop();
	std::string string_ch = std::string(1, ch);
	working_stack.push(string_ch);
}

void Parser::momentary_insuccess()
{
	state = 'b';
}

void Parser::back()
{
	i--;
	std::string string_ch = working_stack.top();
	working_stack.pop();

	char ch = string_ch[0];
	input_stack.push(ch);
}

void Parser::another_try()
{
	std::string string_ch = working_stack.top();
	working_stack.pop();

	char ch = string_ch[0];
	if (i == 0 && ch == grammar.getInitialState()) {
		state = 'e';
	}
	std::vector<std::string> prods = grammar.getProdForNonT(ch);
	
	string_ch.erase(string_ch.begin(), string_ch.begin() + 1);
	int nr = std::stoi(string_ch);

	int dec = prods[nr].size();
	while (dec != 0) {
		input_stack.pop();
		dec--;
	}

	if (nr + 1 < prods.size()) {
		// ne-am dat seama mai tarziu de state = 'q' decat de mai sus
		//	|
		//	|
		//	V
		state = 'q';
		std::string new_ch = std::string(1, ch) + std::to_string((nr + 1));
		working_stack.push(new_ch);
		std::string another_prod = prods[nr + 1];
		//std::cout << another_prod << "\n";
		std::reverse(another_prod.begin(), another_prod.end());
		for (auto c : another_prod) {
			input_stack.push(c);
		}
	}
	else {
		input_stack.push(ch);
	}
}

void Parser::success()
{
	state = 'f';
}

void Parser::construct_tree(Node *& node, std::stack<std::string> & stack)
{
	Node * tata = nullptr;
	Node * current = nullptr;

	std::stack<std::string> aux = std::stack<std::string>();

	while (grammar.getTerminals().find(stack.top()[0]) != std::string::npos) {
		stack.pop();
	}

	std::string string_ch = stack.top();
	stack.pop();

	std::vector<std::string> prods = grammar.getProdForNonT(string_ch[0]);
	if (node == nullptr) {
		node = new Node(string_ch[0]);
	}

	string_ch.erase(string_ch.begin(), string_ch.begin() + 1);
	int nr = std::stoi(string_ch);

	node->setLeftChild(new Node(prods[nr][0]));
	current = node->getLeftChild();

	for (auto c : prods[nr].substr(1)) {
		current->setRightSibling(new Node(c));
		current = current->getRightSibling();
	}

	current = node->getLeftChild();
	while (current != nullptr) {
		if (grammar.getNonTerminals().find(current->getData()) != std::string::npos) {
			construct_tree(current, stack);
		}
		current = current->getRightSibling();
	}
	/*

	while (!aux.empty()) {
		std::string string_ch = aux.top();
		aux.pop();

		char ch = string_ch[0];
		if (grammar.getNonTerminals().find(ch) != std::string::npos) {
			string_ch.erase(string_ch.begin(), string_ch.begin() + 1);
			int nr = std::stoi(string_ch);

			if (tata == nullptr) {
				tata = new Node(ch);
				current = tata;
			}
			
			std::vector<std::string> prods = grammar.getProdForNonT(ch);
			current->setLeftChild(new Node(prods[nr][0]));
			std::string copie = prods[nr];
			copie.erase(copie.begin(), copie.begin() + 1);
			Node * copie_nod = current->getLeftChild();
			for (auto c : copie) {
				copie_nod->setRightSibling(new Node(c));
				copie_nod = copie_nod->getRightSibling();
			}
			current = current->getLeftChild();
			while (grammar.getTerminals().find(current->getData()) != std::string::npos && current == nullptr) {
				while (current->getRightSibling() == nullptr && current != tata) {
					current = current->getParent();
				}
				current = current->getRightSibling();
			}
		}
	}
	return tata;
	*/
}

std::string Parser::doamne_ajuta()
{
	while (state != 'f' && state != 'e') {
		if (state == 'q') {
			if (input_stack.empty() && i == cuvant.size()) {
				success();
				break;
			}
			char ch = input_stack.top();
			if (grammar.getTerminals().find(ch) != std::string::npos) {
				if (ch == cuvant[i]) {
					advance();
				}
				else
					momentary_insuccess();
			}
			if (grammar.getNonTerminals().find(ch) != std::string::npos) {
				expand();
			}
		}
		else if (state == 'b') {
			std::string string_ch = working_stack.top();
			char ch = string_ch[0];
			if (grammar.getTerminals().find(ch) != std::string::npos) {
				back();
			}
			if (grammar.getNonTerminals().find(ch) != std::string::npos) {
				another_try();
			}
		}
	}
	if (state == 'f') {
		std::stack<std::string> aux = std::stack<std::string>();
		while (!working_stack.empty()) {
			std::string string_ch = working_stack.top();
			std::cout << working_stack.top() << ' ';
			working_stack.pop();
			aux.push(string_ch);
		}
		std::cout<<'\n';
		Node * tata = nullptr;
		construct_tree(tata, aux);
		std::string res = "";
		tata->prettyPrint("", res);
		std::cout << res;
		return "accepted sequence";
	}
	if (state == 'e') {
		return "error";
	}
	return std::string("cu ce ai gresit ma nene ma");
}

Parser::~Parser()
{
}
