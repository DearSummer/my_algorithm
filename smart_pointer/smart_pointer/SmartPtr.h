#pragma once
#include <string>

template <typename T>
class SmartPtr
{
	T * ptr;
	int * count;
public:
	explicit SmartPtr<T>(T *ptr);
	SmartPtr(const SmartPtr &ptr);

	~SmartPtr();

	SmartPtr& operator= (const SmartPtr& p);
	T& operator*();
	T* operator->();

	std::string toString();
};
