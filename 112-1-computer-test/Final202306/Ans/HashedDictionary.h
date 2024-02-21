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

	HashedEntry<KeyType, ItemType> *newEntry = nullptr;
	HashedEntry<KeyType, ItemType> *curPtr = nullptr;
	HashedEntry<KeyType, ItemType> *prevPtr = nullptr;

	if (!itemPtr) // not find
	{
		newEntry = new HashedEntry<KeyType, ItemType>(newItem, searchKey);

		if (!hashTable[itemHashIndex]) // empty add directly
		{
			hashTable[itemHashIndex] = newEntry;
			return;
		}
	}
	else // find
	{
		if (itemPtr == hashTable[itemHashIndex])
		{
			itemPtr->countUp();
			return;
		}
		else
		{
			curPtr = hashTable[itemHashIndex];
			newEntry = new HashedEntry<KeyType, ItemType>(itemPtr->getItem(), itemPtr->getKey());
			newEntry->setCount(itemPtr->getCount());
			newEntry->countUp();

			while (curPtr)
			{
				if (curPtr == itemPtr)
				{
					prevPtr->setNext(curPtr->getNext());
					delete curPtr;
					break;
				}
				prevPtr = curPtr;
				curPtr = curPtr->getNext();
			}
		}
	}

	curPtr = hashTable[itemHashIndex];

	while (curPtr)
	{
		if (newEntry->getCount() < curPtr->getCount())
		{
			prevPtr = curPtr;
			curPtr = curPtr->getNext();
		}
		else if (newEntry->getCount() == curPtr->getCount())
		{
			if (newEntry->getItem().size() < curPtr->getItem().size())
			{
				prevPtr = curPtr;
				curPtr = curPtr->getNext();
			}
			else if (newEntry->getItem().size() == curPtr->getItem().size())
			{
				if (newEntry->getItem() < curPtr->getItem())
				{
					prevPtr = curPtr;
					curPtr = curPtr->getNext();
				}
				else
					break;
			}
			else
				break;
		}
		else
			break;
	}

	if (curPtr == hashTable[itemHashIndex])
	{
		newEntry->setNext(curPtr);
		hashTable[itemHashIndex] = newEntry;
	}
	else
	{
		prevPtr->setNext(newEntry);
		newEntry->setNext(curPtr);
	}

} // end add

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType &searchKey) //* add your code here
{
	HashedEntry<string, string> *itemPtr = getEntry(searchKey);
	// Compute the hashed index into the array
	int itemHashIndex = getHashIndex(searchKey);

	HashedEntry<KeyType, ItemType> *newEntry = nullptr;
	HashedEntry<KeyType, ItemType> *curPtr = nullptr;
	HashedEntry<KeyType, ItemType> *prevPtr = nullptr;

	if (!itemPtr) // not find
		return false;
	else // find
	{
		curPtr = hashTable[itemHashIndex];

		newEntry = new HashedEntry<KeyType, ItemType>(itemPtr->getItem(), itemPtr->getKey());
		newEntry->setCount(itemPtr->getCount());
		newEntry->countDown();

		while (curPtr)
		{
			if (curPtr == itemPtr)
			{
				if (curPtr == hashTable[itemHashIndex])
					hashTable[itemHashIndex] = curPtr->getNext();
				else
					prevPtr->setNext(curPtr->getNext());

				delete curPtr;
				break;
			}
			prevPtr = curPtr;
			curPtr = curPtr->getNext();
		}

		if (newEntry->getCount() == 0)
			delete newEntry;
		else
		{
			curPtr = hashTable[itemHashIndex];

			while (curPtr)
			{
				if (newEntry->getCount() < curPtr->getCount())
				{
					prevPtr = curPtr;
					curPtr = curPtr->getNext();
				}
				else if (newEntry->getCount() == curPtr->getCount())
				{
					if (newEntry->getItem().size() < curPtr->getItem().size())
					{
						prevPtr = curPtr;
						curPtr = curPtr->getNext();
					}
					else if (newEntry->getItem().size() == curPtr->getItem().size())
					{
						if (newEntry->getItem() < curPtr->getItem())
						{
							prevPtr = curPtr;
							curPtr = curPtr->getNext();
						}
						else
							break;
					}
					else
						break;
				}
				else
					break;
			}

			if (curPtr == hashTable[itemHashIndex])
			{
				newEntry->setNext(curPtr);
				hashTable[itemHashIndex] = newEntry;
			}
			else
			{
				prevPtr->setNext(newEntry);
				newEntry->setNext(curPtr);
			}
		}
		return true;
	}
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
