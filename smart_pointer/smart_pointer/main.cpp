


#include "SmartPtr.cpp"
#include <iostream>

int main()
{


	SmartPtr<int> sp1(new int(2));
	SmartPtr<int> sp2(sp1);
	SmartPtr<int> sp3(new int(3));
	sp2 = sp3;
	*sp2 = 20;
	std::cout << sp1.toString() << std::endl;
	std::cout << sp2.toString() << std::endl;
	std::cout << sp3.toString() << std::endl;
	int *i = new int(2);
	{
		SmartPtr<int> ptr1(i);
		{
			SmartPtr<int> ptr2(ptr1);
			{
				SmartPtr<int> ptr3 = ptr2;
				std::cout << *ptr1<< std::endl;
				*ptr1 = 20;
				std::cout << *ptr1 << std::endl;
				std::cout << ptr1.toString().c_str() << std::endl;
			}
			std::cout << ptr1.toString().c_str() << std::endl;
		}
	}

	int c;
	std::cin >> c;
	return 0;
}
