
#include "List.h"
#include <ostream>
#include <iostream>
#include <string>
#include <fstream>


using namespace std;
int main()
{
	cout << "²âÊÔArrayList" << endl;
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

	for (int i = 0; i < sa.size(); i++)
	{
		if (sa[i] == "int main()")
			sa.remove(i);
	}

	// ²âÊÔLinkedList<int>
	LinkedList<int> il;
	for (int i = 0; i < 33; i++) {
		il.add(i);
	}
	for (int i = 0; i < il.size(); i++) {
		cout << *il.get(i) << endl;
	}

	// ²âÊÔLinkedList<string>
	LinkedList<string> sl;
	in.open("Main.cpp");
	while (getline(in, line)) {
		sl.add(line);
	}
	for (int i = 0; i < sl.size(); i++) {
		cout << *sl.get(i) << endl;
	}
	in.close();


	// ²âÊÔLinkedList<int>µÄµü´ú
	LinkedList<int>::iterator ilt(il);
	cout << "²âÊÔLinkedList iterator" << endl;
	while (ilt.hasNext()) {
		cout << ilt.next() << endl;
	}

	// ²âÊÔLinkedList<string>µÄµü´ú
	LinkedList<string>::iterator slt(sl);
	while (slt.hasNext()) {
		cout << slt.next() << endl;
	}





	int __s;
	cin >> __s;

	return 0;
}
