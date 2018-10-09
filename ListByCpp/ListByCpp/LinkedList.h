#pragma once
#include "IList.h"

#include <iostream>
#define checkIsValidIndex(index)                   \
	if(index < 0 || index >= len)                  \
		throw std::exception("Index Out Of Range") \

template<typename T>
class LinkedList : public IList<T>
{
private:
	typedef struct Item
	{
		Item(T& e, Item* prev, Item* next);
		T element;
		Item *prev;
		Item *next;
	}Node;

	Node * head;
	Node * tail;

	int len;
	LinkedList(const LinkedList&);

	void linkBefore(T& e, Node * node);
	void linkHead(T& e);
	void linkTail(T& e);

	T* unlink(Node * node);

	Node * getNode(int index);

	

public:
	LinkedList();
	~LinkedList() override;
	
	bool add(T& e) override;
	int contains(T& e) override;
	bool remove(T& e) override;
	bool isEmpty() override;
	int size() override;
	void add(T& e, int index) override;
	T* get(int index) override;
	T* remove(int index) override;

	void addHead(T& e);
	void addTail(T& e);
	T* getHead();
	T* getTail();

	T& operator[](int index);

	class iterator
	{
		LinkedList& ll;
		Node * cur;

		friend Node * LinkedList::getNode(int index);

	public:
		explicit iterator(LinkedList& ll) :ll(ll),cur(getNode(0))
		{			
		}

		bool hasNext();
		T& next();
	};
};






