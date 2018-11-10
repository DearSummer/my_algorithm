#pragma once
#include <string>

struct RBNode
{
	bool red;
	int value;

	RBNode * left;
	RBNode * right;

	RBNode * parent;

	RBNode();
	RBNode(int value, bool red, RBNode* left, RBNode* right, RBNode* parent);
	std::string toString() const;
};

