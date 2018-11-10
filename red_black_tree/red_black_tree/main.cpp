

#include "RBTree.h"
#include <iostream>

int main()
{
	int a[10] = { 3,4,5,6,7,2,3,1,8,6 };
	RBTree rbTree;

	for(int i = 0;i < 10;i++)
	{
		rbTree.insert(a[i]);
	}

	rbTree.perorderPrint();
	std::cout << std::endl;
	rbTree.midorderPrint();
	int b;
	std::cin >> b;
	return 0;
}
