

#include "RBTree.h"
#include <iostream>

int main()
{
	int a[10] = { 3,4,5,6,7,2,3,1,8,6 };
	RBTree rbTree;

	for (int i : a)
	{
		rbTree.insert(i);
	}

	rbTree.perorderPrint();
	std::cout << std::endl;
	rbTree.midorderPrint();
	std::cout << std::endl;

	std::cout << rbTree.next(rbTree.getRoot())->value << std::endl;
	std::cout << rbTree.prev(rbTree.getRoot())->value << std::endl;

	rbTree.remove(4);
	rbTree.perorderPrint();
	std::cout << std::endl;
	rbTree.midorderPrint();
	std::cout << std::endl;
	std::cout << rbTree.next(rbTree.getRoot())->value << std::endl;
	std::cout << rbTree.prev(rbTree.getRoot())->value << std::endl;

	int b;
	std::cin >> b;
	return 0;
}
