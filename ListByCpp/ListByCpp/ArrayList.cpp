#include "ArrayList.h"
#include <algorithm>


template <class T, int defaultCapacity>
ArrayList<T, defaultCapacity>::ArrayList():len(0),capacity(defaultCapacity),arr(new T[capacity])
{
}

template<class T, int defaultCapacity>
bool ArrayList<T, defaultCapacity>::add(T& e)
{
	ensureCapacityInternal(len + 1);
	arr[len++] = e;
	return true;
}

template<class T, int defaultCapacity>
int ArrayList<T, defaultCapacity>::contains(T& e)
{
	for(int i = 0;i < len;i++)
	{
		if (e == arr[i])
			return i;
	}
	return -1;
}

template<class T, int defaultCapacity>
bool ArrayList<T, defaultCapacity>::remove(T& e)
{
	return remove(contains(e)) != nullptr;
}

template<class T, int defaultCapacity>
bool ArrayList<T, defaultCapacity>::isEmpty()
{
	return len == 0;
}

template<class T, int defaultCapacity>
int ArrayList<T, defaultCapacity>::size()
{
	return len;
}

template<class T, int defaultCapacity>
void ArrayList<T, defaultCapacity>::add(T& e, int index)
{
	ensureCapacityInternal(len + 1);
	T * newArr = new T[capacity];
	for(int i = 0;i < len;i++)
	{
		if(i < index)
		{
			newArr[i] = arr[i];
		}

		else if(i == index)
		{
			newArr[i] = e;
		}

		else
		{
			newArr[i] = arr[i - 1];
		}
	}
	len++;
	delete[] arr;
	arr = newArr;
}

template<class T, int defaultCapacity>
T * ArrayList<T, defaultCapacity>::get(int index)
{
	if (index < 0 || index >= len)
		return nullptr;
	return &arr[index];
}

template<class T, int defaultCapacity>
T * ArrayList<T, defaultCapacity>::remove(int index)
{
	if (index < 0 || index >= len)
		return nullptr;

	T* newArr = new T[--capacity];
	T* removeItem = nullptr;
	for(int i = 0;i < len;i++)
	{
		if (i < index)
			newArr[i] = arr[i];

		if (i == index)
			removeItem = &arr[i];

		if (i > index)
			newArr[i - 1] = arr[i];
	}
	len--;
	delete[] arr;
	arr = newArr;

	return removeItem;
}

template<class T, int defaultCapacity>
T& ArrayList<T, defaultCapacity>::operator[](int index)
{
	return *get(index);
}


template<class T, int defaultCapacity>
void ArrayList<T, defaultCapacity>::ensureCapacityInternal(int minCapacity)
{
	minCapacity = std::max(defaultCapacity, minCapacity);
	ensureExplicitCapacity(minCapacity);
}

template<class T, int defaultCapacity>
void ArrayList<T, defaultCapacity>::ensureExplicitCapacity(int minCapacity)
{
	if (minCapacity > capacity)
		inflate(minCapacity);
}

template<class T, int defaultCapacity>
void ArrayList<T, defaultCapacity>::inflate(int minCapacity)
{
	const int oldCapacity = len;
	int newCapacity = oldCapacity + (oldCapacity >> 1);

	if (minCapacity - newCapacity > 0)
		newCapacity = minCapacity;

	T* newItem = new T[newCapacity];
	for(int i =0;i < len;i++)
	{
		newItem[i] = arr[i];
	}

	delete[] arr;
	arr = newItem;
	capacity = newCapacity;

}

template <class T, int defaultCapacity>
ArrayList<T, defaultCapacity>::ArrayList(const ArrayList&)
{
}



