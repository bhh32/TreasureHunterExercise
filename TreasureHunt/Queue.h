#pragma once

#include "TLinkedList.h"

template<typename T>
class Queue
{
private:
	TLinkedList<T> list;

public:
	// Front is the head
	bool Empty()
	{
		return list.Empty();
	}

	size_t Size()
	{
		return list.GetSize();
	}

	void Push(T value)
	{
		list.Append(value);
	}

	T Pop()
	{
		T temp = list.Front();
		list.Erase(0);
		return temp;
	}

	T Peek()
	{
		return list.Front();
	}

	T Back()
	{
		return list.Back();
	}
};