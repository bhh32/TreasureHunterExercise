#pragma once

#include <cassert>
#include "Iterator.h"

template<typename T>
class TLinkedList
{
public:
	struct TLinkedListNode
	{
		T value;
		TLinkedListNode* next;
	};

	TLinkedList();
	~TLinkedList();

	Iterator<TLinkedList<T>> Begin()
	{
		return Iterator<TLinkedList<T>>(*this, 0);
	}

	Iterator<TLinkedList<T>> End()
	{
		return Iterator<TLinkedList<T>>(*this, size + 1);
	}

	void Append(T value);
	T &At(size_t index);
	size_t GetSize() const;
	bool Empty() const;
	T &Front() const;
	T &Back() const;
	void Clear();
	void Erase(size_t index);
	size_t Count(T value);
	void Insert(T value, size_t index);

protected:
	TLinkedListNode* head;
	TLinkedListNode* tail;
	size_t size;
};

template<typename T>
TLinkedList<T>::TLinkedList() : head(nullptr), tail(head), size(0)
{}

template<typename T>
TLinkedList<T>::~TLinkedList()
{
	TLinkedListNode* iter = head;

	while (iter != nullptr)
	{
		TLinkedListNode* next = iter->next;
		delete iter;
		iter = next;
	}
}

template<typename T>
void TLinkedList<T>::Append(T value)
{
	TLinkedListNode* newNode = new TLinkedListNode;
	newNode->value = value;
	newNode->next = nullptr;

	if (head == nullptr)
	{
		head = newNode;
		tail = head;
		size++;
	}
	else
	{
		TLinkedListNode* iter = head;

		while (iter->next != nullptr)
		{
			iter = iter->next;
		}

		iter->next = newNode;
		tail = iter->next;
		size++;
	}
}

template<typename T>
T &TLinkedList<T>::At(size_t index)
{
	assert(index <= size);

	size_t counter = 0;

	TLinkedListNode* currentNode = head;

	while (counter < index && currentNode != nullptr)
	{
		currentNode = currentNode->next;
		counter++;
	}

	return currentNode->value;
}

template<typename T>
size_t TLinkedList<T>::GetSize() const
{
	return size;
}

template<typename T>
bool TLinkedList<T>::Empty() const
{
	return head == nullptr;
}

template<typename T>
T &TLinkedList<T>::Front() const
{
	assert(!Empty());

	return head->value;
}

template<typename T>
T &TLinkedList<T>::Back() const
{
	assert(!Empty());

	return tail->value;
}

template<typename T>
void TLinkedList<T>::Clear()
{
	TLinkedListNode* iter = head;

	while (head != nullptr)
	{
		if (iter != nullptr)
		{
			TLinkedListNode* next = iter->next;

			delete iter;

			iter = next;
		}

		if (iter == nullptr)
			head = nullptr;
	}
}

template<typename T>
void TLinkedList<T>::Erase(size_t index)
{
	// Ensure
	assert(index <= size);

	size_t counter = 0;

	TLinkedListNode* currentNode = head;
	TLinkedListNode* previousNode = head;

	while (counter < index)
	{
		if (counter == index - 1)
			previousNode = currentNode;

		currentNode = currentNode->next;
		counter++;
	}

	previousNode->next = currentNode->next;

	if (index == 0)
		head = currentNode->next;

	delete currentNode;
	
	size--;
}

template<typename T>
size_t TLinkedList<T>::Count(T value)
{
	size_t counter = 0;

	TLinkedListNode* currentNode = head;

	while (currentNode != nullptr)
	{
		if (currentNode->value == value)
			counter++;
	}

	return counter;
}

template<typename T>
void TLinkedList<T>::Insert(T value, size_t index)
{
	assert(index <= size);

	// Allocate the memory for the new node and set it's value to the specified value
	TLinkedListNode* newNode = new TLinkedListNode;
	newNode->value = value;

	// Create and set the currentNode to head
	TLinkedListNode* currentNode = head;

	// Allocate memory for the previous node
	TLinkedListNode* previousNode = new TLinkedListNode;

	size_t counter = 0;

	// Gets the node that is currently at the index as well as the node before it
	while (counter < index)
	{
		if (counter == index - 1)
			previousNode = currentNode;

		currentNode = currentNode->next;

		counter++;
	}

	// The current node at the specified idx is saved in the temp variable
	TLinkedListNode* temp = currentNode;

	// The current node is set to the new node
	currentNode = newNode;

	// The pointer to the next node is set to the temp variable that holds the original node
	currentNode->next = temp;

	// The pointer of the previous node is set to the new current node
	previousNode->next = currentNode;

	// Increase the size
	size++;
}


