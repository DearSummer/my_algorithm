#include "LinkedList.h"
#include <iostream>

using std::exception;

template <typename T>
LinkedList<T>::Item::Item(T& e, Item* prev, Item* next): element(e), prev(prev), next(next)
{
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList&)
{
}

template <typename T>
void LinkedList<T>::linkHead(T& e)
{
	Node * head = this->head;
	Node * newNode = new Node(e, nullptr, head);

	if (head == nullptr)
		tail = newNode;
	else
		head->prev = newNode;

	this->head = newNode;
	len++;
}

template <typename T>
void LinkedList<T>::linkTail(T& e)
{
	Node * tailNode = tail;
	Node * newNode = new Node(e, tailNode, nullptr);
	
	if (tailNode == nullptr)
		head = newNode;
	else
		tail->next = newNode;

	tail = newNode;

	len++;
}

template <typename T>
T* LinkedList<T>::unlink(Node* node)
{
	if (node == nullptr)
		throw exception("Node is empty");

	T element = node->element;
	Node * prev = node->prev;
	Node * next = node->next;

	if(prev != nullptr)
	{
		prev->next = next;
		node->prev = nullptr;
	}
	else
	{
		head = prev->next;
	}

	if(next != nullptr)
	{
		next->prev = prev;
		node->prev = nullptr;
	}else
	{
		tail = prev;
	}

	len--;
	delete node;
	return &element;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNode(int index)
{

	checkIsValidIndex(index);

	Node * target = head;
	if (index > (len >> 1))
	{
		target = tail;
		for (int i = len - 1; i > index; i--)
		{
			target = target->prev;
		}
	}
	else
	{
		for (int i = 0; i < index; i++)
		{
			target = target->next;
		}
	}

	return target;
}



template <typename T>
void LinkedList<T>::linkBefore(T& e, Node* node)
{
	Node * prev = node->prev;
	Node * newNode = new Node(e, prev, node);
	node->prev = newNode;
	if (prev == nullptr)
		head = newNode;
	else
		prev->next = newNode;

	len++;
}

template <typename T>
LinkedList<T>::LinkedList():head(nullptr),tail(nullptr),len(0)
{
}

template <typename T>
bool LinkedList<T>::add(T& e)
{
	linkTail(e);
	return true;
}

template <typename T>
int LinkedList<T>::contains(T& e)
{
	int index = 0;

	if (head == nullptr || tail == nullptr)
		throw exception("LinkedList is empty");

	for(Node * n = head;n != tail; n = n->next)
	{
		if (n->element == e)
			return index;

		index++;
	}
	return -1;
}

template <typename T>
bool LinkedList<T>::remove(T& e)
{
	const int index = contains(e);
	if (index == -1)
		return false;

	return unlink(getNode(index)) != nullptr;
}

template <typename T>
bool LinkedList<T>::isEmpty()
{
	return len == 0;
}

template <typename T>
int LinkedList<T>::size()
{
	return len;
}

template <typename T>
void LinkedList<T>::add(T& e, int index)
{
	checkIsValidIndex(index);
	linkBefore(e, getNode(index));
}

template <typename T>
T* LinkedList<T>::get(int index)
{
	if (index < 0 || index >= len)
		throw exception("Index Out Of Range");

	Node * target = head;
	for(int i = 0 ;i < index;i++)
	{
		target = target->next;
	}
	return &(target->element);
}

template <typename T>
T* LinkedList<T>::remove(const int index)
{
	checkIsValidIndex(index);
	
	return unlink(getNode(index));
	
}

template<typename T>
void LinkedList<T>::addHead(T & e)
{
	linkHead(e);
}

template<typename T>
void LinkedList<T>::addTail(T & e)
{
	linkTail(e);
}

template<typename T>
T * LinkedList<T>::getHead()
{
	return head;
}

template<typename T>
T * LinkedList<T>::getTail()
{
	return tail;
}

template <typename T>
T& LinkedList<T>::operator[](int index)
{
	return *get(index);
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	if(len != 0)
	{
		while(head->next != nullptr)
		{
			Node* item = head;
			head = head->next;
			delete item;
		}
	}
}


template <typename T>
bool LinkedList<T>::iterator::hasNext()
{
	return cur != nullptr && cur->next != nullptr;
}

template <typename T>
T& LinkedList<T>::iterator::next()
{
	cur = cur->next;
	return cur->element;
}

