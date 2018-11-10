#include "RBNode.h"



RBNode::RBNode()
 :red(false), value(0), left(nullptr),right(nullptr), parent(nullptr)
{}

RBNode::RBNode(int value, bool red, RBNode* left, RBNode* right, RBNode* parent): red(red), value(value), left(left),
                                                                                  right(right), parent(parent)
{
}

std::string RBNode::toString() const
{
	std::string temp = std::to_string(value) + "(";
	temp += red ? "R" : "B";
	temp += ") ";
	return temp;
}
