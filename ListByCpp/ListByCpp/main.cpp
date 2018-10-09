
#include "List.h"
#include <ostream>
#include <iostream>
#include <string>
#include <fstream>


using namespace std;
int main()
{
	cout << "����ArrayList" << endl;
	// ����ArrayList<int>
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



	// ����ArrayList<string>
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

	// ����LinkedList<int>
	LinkedList<int> il;
	for (int i = 0; i < 33; i++) {
		il.add(i);
	}
	for (int i = 0; i < il.size(); i++) {
		cout << *il.get(i) << endl;
	}

	// ����LinkedList<string>
	LinkedList<string> sl;
	in.open("Main.cpp");
	while (getline(in, line)) {
		sl.add(line);
	}
	for (int i = 0; i < sl.size(); i++) {
		cout << *sl.get(i) << endl;
	}
	in.close();


	// ����LinkedList<int>�ĵ���
	LinkedList<int>::iterator ilt(il);
	cout << "����LinkedList iterator" << endl;
	while (ilt.hasNext()) {
		cout << ilt.next() << endl;
	}

	// ����LinkedList<string>�ĵ���
	LinkedList<string>::iterator slt(sl);
	while (slt.hasNext()) {
		cout << slt.next() << endl;
	}





	int __s;
	cin >> __s;

	return 0;
}
