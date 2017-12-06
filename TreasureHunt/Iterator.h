#pragma once

template<typename T>
class Iterator
{
public:
	// Don't create a default constructor
	Iterator() = delete;

	// Constructor
	Iterator(T &container, int initialIndex)
		: owningContainer(&container),
		currentIndex(initialIndex) {}

	// Copy Constructor
	Iterator(const Iterator<T> &other)
		: owningContainer(other.owningContainer),
		currentIndex(other.currentIndex) {}

	Iterator<T> &operator=(const Iterator<T> &other)
	{
		owningContainer = other.owningContainer;
		currentIndex = other.currentIndex;
	}

	bool operator==(const Iterator<T> &other)
	{
		bool isSameContainer = owningContainer == other.owningContainer;
		bool isSameIndex = currentIndex == other.currentIndex;

		return isSameContainer && isSameIndex;
	}

	bool operator!=(const Iterator<T> &other)
	{
		bool isSameContainer = owningContainer == other.owningContainer;
		bool isSameIndex = currentIndex == other.currentIndex;

		return !isSameContainer || !isSameIndex;
	}

	auto &operator*()
	{
		return owningContainer->At(currentIndex);
	}

	Iterator<T> &operator++()
	{
		++currentIndex;

		return *this;
	}
	
	Iterator<T> &operator++(int dummy)
	{
		Iterator<T> temp(owningContainer, currentIndex);
		operator++();

		return tmp;
	}

private:
	T* owningContainer;
	size_t currentIndex;
};