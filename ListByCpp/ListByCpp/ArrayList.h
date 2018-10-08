#pragma once
#include "IList.h"
#include <cstddef>
#include <iterator>

template<class T,int defaultCapacity = 10>
class ArrayList : public IList<T>
{
public:
	ArrayList();
	bool add(T& e) override;
	int contains(T& e) override;
	bool remove(T& e) override;
	bool isEmpty() override;
	int size() override;
	void add(T& e, int index) override;
	T * get(int index) override;
	T * remove(int index) override;

	T& operator[](int index);

private:
	int len;
	int capacity;
	T* arr;
	void ensureCapacityInternal(int minCapacity);
	void ensureExplicitCapacity(int minCapacity);
	void inflate(int minCapacity);
	ArrayList(const ArrayList& arr);
};



