#pragma once
#include "ICollection.h"

template<class T>
class IList : public ICollection<T>
{
public:
	virtual ~IList() = default;

	virtual void add(T& e, int index) = 0;
	virtual T * get(int index) = 0;
	virtual T * remove(int index) = 0;
};

