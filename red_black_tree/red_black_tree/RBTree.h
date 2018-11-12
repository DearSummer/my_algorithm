#pragma once
#include "RBNode.h"

class RBTree
{
	RBNode * root;

	void leftRotation(RBNode * n);
	void rightRotation(RBNode * n);

	void insert(RBNode * n);
	void insertFixUp(RBNode * n);

	static RBNode * maxNode(RBNode * tree);
	static RBNode * minNode(RBNode * tree);

	static RBNode * search(RBNode * tree,int target);

	void remove(RBNode * node);
	void removeFixUp(RBNode * node, RBNode * parent);

	static void destory(RBNode * tree);

	void perorderPrint(RBNode * tree) const;
	void midorderPrint(RBNode * tree) const;
public:

	int maxValue() const;
	int minValue() const;

	void insert(int value);
	void remove(int value);

	void clear() const;

	static RBNode * next(RBNode * node);
	static RBNode * prev(RBNode * node);

	RBNode * getRoot() const;

	void perorderPrint() const;
	void midorderPrint() const;
	RBTree();
	~RBTree();

};

