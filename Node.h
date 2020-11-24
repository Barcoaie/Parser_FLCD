#pragma once
#include<string>

class Node {
private:
	char data;
	Node * parent;
	Node * left_child;
	Node * right_sibling;
public:
	Node(char data);

	char getData();

	Node * getParent();

	Node * getLeftChild();

	Node * getRightSibling();

	void setData(char newData);

	void setLeftChild(Node * newChild);

	void setRightSibling(Node * newSibling);

	void setParent(Node * newParent);

	void prettyPrint(std::string tab, std::string & res);

	~Node();
};