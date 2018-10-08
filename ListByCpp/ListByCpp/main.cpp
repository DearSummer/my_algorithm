
#include "List.h"
#include <ostream>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
int main()
{
	// ²âÊÔArrayList<int>
	ArrayList<int> ia;
	for (int i = 0; i < 15; i++) {
		ia.add(i);
	}
	cout << "size : " << ia.size() << endl;
	for (int i = 0; i < ia.size(); i++)
		cout << ia[i] << endl;

	ia.remove(3);
	cout << "size : " << ia.size() << endl;
	for (int i = 0; i < ia.size(); i++)
		cout << ia[i] << endl;

	int n = 17;
	ia.add(n);
	cout << "size : " << ia.size() << endl;
	for (int i = 0; i < ia.size(); i++)
		cout << ia[i] << endl;

	

	// ²âÊÔArrayList<string>
	ArrayList<string> sa;
	fstream in;
	in.open("main.cpp");
	string line;
	while (getline(in, line)) {
		sa.add(line);
	}
	for (int i = 0; i < sa.size(); i++) {
		cout << sa[i] << std::endl;
	}
	in.close();

	for(int i = 0; i < sa.size();i++)
	{
		if (sa[i] == "int main()")
			sa.remove(i);
	}


	int __s;
	cin >> __s;

	return 0;
}
