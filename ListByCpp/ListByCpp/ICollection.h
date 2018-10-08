#pragma once

template<class  T>
class ICollection
{

public:
	virtual ~ICollection<T>() = default;
	virtual bool add(T& e) = 0;
	virtual int contains(T& e) = 0;
	virtual bool remove(T& e) = 0;
	virtual bool isEmpty() = 0;
	virtual int size() = 0;
};

