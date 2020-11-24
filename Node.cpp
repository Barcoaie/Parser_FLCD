#include "Node.h"

Node::Node(char data)
{
	this->data = data;
	this->left_child = nullptr;
	this->right_sibling = nullptr;
	this->parent = nullptr;
}

char Node::getData()
{
	return data;
}

Node * Node::getParent()
{
	return parent;
}

Node * Node::getLeftChild()
{
	return left_child;
}

Node * Node::getRightSibling()
{
	return right_sibling;
}

void Node::setData(char newData)
{
	data = newData;
}

void Node::setLeftChild(Node * newChild)
{
	newChild->parent = this;
	left_child = newChild;
}

void Node::setRightSibling(Node * newSibling)
{
	right_sibling = newSibling;
	right_sibling->parent = this->parent;
}

void Node::setParent(Node * newParent)
{
	parent = newParent;
}

void Node::prettyPrint(std::string tab, std::string & res)
{
	res = res + tab + data + "\n";
	if (left_child != nullptr) {
		Node * current = left_child;
		while (current != nullptr) {
			current->prettyPrint(tab + "\t", res);
			current = current->right_sibling;
		}
	}
}

Node::~Node()
{
}
