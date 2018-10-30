#include "SmartPtr.h"
#include <cassert>
#include <iostream>

template <typename T>
SmartPtr<T>::SmartPtr(T* ptr):ptr(ptr),count(new int(1))
{
}

template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr& ptr)
{
	if(this != &ptr)
	{
		this->ptr = ptr.ptr;
		this->count = ptr.count;
		++(*this->count);
	}
}

template <typename T>
SmartPtr<T>::~SmartPtr()
{
	--(*this->count);
	if((*this->count) == 0)
	{
		delete ptr;
		delete count;
	}
}

template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr& p)
{
	if(this->ptr == p.ptr)
	{
		return *this;
	}

	if(this->ptr)
	{
		--(*this->count);
		if((*this->count) == 0)
		{
			delete this->ptr;
			delete this->count;
		}
	}

	this->ptr = p.ptr;
	this->count = p.count;

	++(*this->count);
	return *this;
}



template <typename T>
T& SmartPtr<T>::operator*()
{
	assert(this->ptr != nullptr);
	return *(this->ptr);
}

template <typename T>
T* SmartPtr<T>::operator->()
{
	assert(this->ptr != nullptr);
	return this->ptr;
}

template<typename T>
std::string SmartPtr<T>::toString()
{
	std::string str = "count = ";
	str.append(std::to_string((*this->count)));
	return str;
}




