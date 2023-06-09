//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file  HashedDictionary.cpp */

// Separate chaining resolves collisions

// PARTIALLY COMPLETE
#include <string>
#include "HashedEntry.h"

template <class KeyType, class ItemType>
class HashedDictionary
{
private:
	HashedEntry<KeyType, ItemType> **hashTable;
	static const int DEFAULT_SIZE = 1;
	HashedEntry<KeyType, ItemType> *nextPtr;
	int hashTableSize;

public:
	HashedDictionary();
	HashedDictionary(int size);
	void add(const KeyType &searchKey, const ItemType &newItem);
	bool remove(const KeyType &searchKey);
	HashedEntry<KeyType, ItemType> *getEntry(const KeyType &searchKey);
	void traverse(int itemHashIndex, void visit(HashedEntry<KeyType, ItemType> &)) const;
	void clear();
	bool isEmpty();
	int getTableSize();

protected:
	int getHashIndex(const KeyType &searchKey);
}; // end HashedDictionary

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary()
{
	hashTableSize = DEFAULT_SIZE;
	hashTable = new HashedEntry<KeyType, ItemType> *[hashTableSize];

	for (int i = 0; i < hashTableSize; i++)
		hashTable[i] = nullptr;
}

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary(int size)
{
	hashTableSize = size;
	hashTable = new HashedEntry<KeyType, ItemType> *[hashTableSize];

	for (int i = 0; i < hashTableSize; i++)
		hashTable[i] = nullptr;
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::traverse(int itemHashIndex, void visit(HashedEntry<KeyType, ItemType> &)) const
{
	HashedEntry<KeyType, ItemType> *itemPtr = hashTable[itemHashIndex];

	while (itemPtr != nullptr)
	{
		visit(*itemPtr);
		itemPtr = itemPtr->getNext();
	}
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::clear()
{
	HashedEntry<KeyType, ItemType> *nextPtr, *curPtr;

	for (int i = 0; i < hashTableSize; i++)
	{
		curPtr = hashTable[i];

		while (curPtr != nullptr)
		{
			nextPtr = curPtr->getNext();
			delete curPtr;
			curPtr = nextPtr;
		} // end while

		hashTable[i] = nullptr;
	} // end if
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getTableSize()
{
	return hashTableSize;
}

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::isEmpty()
{
	for (int i = 0; i < hashTableSize; i++)
	{
		if (hashTable[i] != nullptr)
			return false;
	}

	return true;
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getHashIndex(const KeyType &searchKey)
{
	int strLen = searchKey.length();

	if (strLen == 0)
		return 0;

	return ((unsigned char)searchKey[0]) % hashTableSize;
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::add(const KeyType &searchKey, const ItemType &newItem) //* add your code here
{
	HashedEntry<string, string> *itemPtr = getEntry(searchKey);
	// Compute the hashed index into the array
	int itemHashIndex = getHashIndex(searchKey);

	// b

	if (!itemPtr)
	{
		HashedEntry<KeyType, ItemType> *newEntry = new HashedEntry<KeyType, ItemType>(newItem, searchKey);

		if (hashTable[itemHashIndex] == nullptr)
			hashTable[itemHashIndex] = newEntry;
		else
		{
			newEntry->setNext(hashTable[itemHashIndex]);
			hashTable[itemHashIndex] = newEntry;
		}
	}
	else
		itemPtr->countUp();

} // end add

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType &searchKey) //* add your code here
{
	bool itemFound = false;
	HashedEntry<string, string> *itemPtr = getEntry(searchKey);
	// Compute the hashed index into the array
	int itemHashIndex = getHashIndex(searchKey);

	// e

	if (itemPtr)
	{
		HashedEntry<KeyType, ItemType> *curPtr = hashTable[itemHashIndex];
		HashedEntry<KeyType, ItemType> *prevPtr = nullptr;

		while (curPtr)
		{
			if (curPtr->getItem() == itemPtr->getItem())
			{
				if (itemPtr->getCount() == 1)
				{
					if (curPtr == hashTable[itemHashIndex])
						hashTable[itemHashIndex] = curPtr->getNext();
					else
						prevPtr->setNext(curPtr->getNext());

					delete curPtr;
				}
				else
					itemPtr->countDown();

				break;
			}

			prevPtr = curPtr;
			curPtr = curPtr->getNext();
		}

		itemFound = true;
	}

	return itemFound;
} // end remove

template <class KeyType, class ItemType>
HashedEntry<KeyType, ItemType> *HashedDictionary<KeyType, ItemType>::getEntry(const KeyType &searchKey) //* add your code here
{
	bool itemFound = false;

	// Compute the hashed index into the array
	int itemHashIndex = getHashIndex(searchKey);

	HashedEntry<KeyType, ItemType> *curPtr = hashTable[itemHashIndex];

	while (curPtr)
	{
		if (curPtr->getKey() == searchKey)
		{
			itemFound = true;
			break;
		}
		curPtr = curPtr->getNext();
	}

	return curPtr;
}
