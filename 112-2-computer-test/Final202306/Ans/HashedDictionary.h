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

	HashedEntry<KeyType, ItemType> *newEntry = new HashedEntry<KeyType, ItemType>(newItem, searchKey);
	HashedEntry<KeyType, ItemType> *curPtr = hashTable[itemHashIndex];
	HashedEntry<KeyType, ItemType> *prevPtr = nullptr;
	HashedEntry<KeyType, ItemType> *targetPtr = hashTable[itemHashIndex];

	if (!hashTable[itemHashIndex])
	{
		hashTable[itemHashIndex] = newEntry;
		return;
	}

	if (itemPtr)
	{
		while (curPtr)
		{
			if (curPtr == itemPtr)
			{
				delete newEntry;

				newEntry = new HashedEntry<KeyType, ItemType>(curPtr->getItem(), curPtr->getKey());
				newEntry->setCount(curPtr->getCount());
				newEntry->countUp();

				if (curPtr == hashTable[itemHashIndex])
					hashTable[itemHashIndex] = curPtr->getNext();
				else
					prevPtr->setNext(curPtr->getNext());

				delete curPtr;

				curPtr = hashTable[itemHashIndex];
				targetPtr = hashTable[itemHashIndex];
				break;
			}
			prevPtr = curPtr;
			curPtr = curPtr->getNext();
		}
	}

	while (curPtr)
	{
		if (newEntry->getCount() < targetPtr->getCount())
		{
			prevPtr = targetPtr;
			targetPtr = targetPtr->getNext();
		}
		else if (newEntry->getCount() == targetPtr->getCount())
		{
			if (newEntry->getItem().size() < targetPtr->getItem().size())
			{
				prevPtr = targetPtr;
				targetPtr = targetPtr->getNext();
			}
			else if (newEntry->getItem().size() == targetPtr->getItem().size())
			{
				if (newEntry->getItem() < targetPtr->getItem())
				{
					prevPtr = targetPtr;
					targetPtr = targetPtr->getNext();
				}
			}
		}
		curPtr = curPtr->getNext();
	}

	if (targetPtr == hashTable[itemHashIndex])
	{
		newEntry->setNext(targetPtr);
		hashTable[itemHashIndex] = newEntry;
	}
	else
	{
		prevPtr->setNext(newEntry);
		newEntry->setNext(targetPtr);
	}
} // end add

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType &searchKey) //* add your code here
{
	bool itemFound = false;
	HashedEntry<string, string> *itemPtr = getEntry(searchKey);
	// Compute the hashed index into the array
	int itemHashIndex = getHashIndex(searchKey);

	HashedEntry<KeyType, ItemType> *curPtr = hashTable[itemHashIndex];
	HashedEntry<KeyType, ItemType> *newEntry = nullptr;
	HashedEntry<KeyType, ItemType> *prevPtr = nullptr;
	HashedEntry<KeyType, ItemType> *targetPtr = nullptr;

	if (itemPtr)
	{
		while (curPtr)
		{
			if (curPtr == itemPtr)
			{
				newEntry = new HashedEntry<KeyType, ItemType>(curPtr->getItem(), curPtr->getKey());
				newEntry->setCount(curPtr->getCount());
				newEntry->countDown();

				if (curPtr == hashTable[itemHashIndex])
					hashTable[itemHashIndex] = curPtr->getNext();
				else
					prevPtr->setNext(curPtr->getNext());

				delete curPtr;

				curPtr = hashTable[itemHashIndex];
				targetPtr = hashTable[itemHashIndex];
				break;
			}
			prevPtr = curPtr;
			curPtr = curPtr->getNext();
		}

		if (newEntry->getCount() == 0)
			delete newEntry;
		else
		{
			while (curPtr)
			{
				if (newEntry->getCount() < targetPtr->getCount())
				{
					prevPtr = targetPtr;
					targetPtr = targetPtr->getNext();
				}
				else if (newEntry->getCount() == targetPtr->getCount())
				{
					if (newEntry->getItem().size() < targetPtr->getItem().size())
					{
						prevPtr = targetPtr;
						targetPtr = targetPtr->getNext();
					}
					else if (newEntry->getItem().size() == targetPtr->getItem().size())
					{
						if (newEntry->getItem() < targetPtr->getItem())
						{
							prevPtr = targetPtr;
							targetPtr = targetPtr->getNext();
						}
					}
				}
				curPtr = curPtr->getNext();
			}

			if (targetPtr == hashTable[itemHashIndex])
			{
				newEntry->setNext(targetPtr);
				hashTable[itemHashIndex] = newEntry;
			}
			else
			{
				prevPtr->setNext(newEntry);
				newEntry->setNext(targetPtr);
			}
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
