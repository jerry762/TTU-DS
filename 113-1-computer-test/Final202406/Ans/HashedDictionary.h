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
    HashedEntry<KeyType, ItemType> *maxWord();
    int wordCount();

protected:
    int getHashIndex(const KeyType &searchKey);
};

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
    }
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
void HashedDictionary<KeyType, ItemType>::add(const KeyType &searchKey, const ItemType &newItem)
{
    HashedEntry<string, string> *targetPtr = getEntry(searchKey);

    int itemHashIndex = getHashIndex(searchKey);
    HashedEntry<KeyType, ItemType> *entryToAddPtr =
        new HashedEntry<KeyType, ItemType>(newItem, searchKey);

    if (targetPtr)
    {
        targetPtr->countUp();
        delete entryToAddPtr;
        entryToAddPtr = nullptr;
    }
    else
    {
        HashedEntry<KeyType, ItemType> *itemPtr = hashTable[itemHashIndex];

        if (!itemPtr)
            hashTable[itemHashIndex] = entryToAddPtr;
        else
        {
            entryToAddPtr->setNext(hashTable[itemHashIndex]);
            hashTable[itemHashIndex] = entryToAddPtr;
        }
    }
}

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType &searchKey)
{
    bool itemFound = false;
    HashedEntry<string, string> *targetPtr = getEntry(searchKey);
    int itemHashIndex = getHashIndex(searchKey);

    if (targetPtr)
    {
        if (targetPtr->getCount() > 1)
            targetPtr->countDown();
        else
        {
            HashedEntry<KeyType, ItemType> *itemPtr = hashTable[itemHashIndex];
            HashedEntry<KeyType, ItemType> *prevPtr = nullptr;

            while (itemPtr)
            {
                if (itemPtr->getKey() == searchKey)
                {
                    if (itemPtr == hashTable[itemHashIndex])
                        hashTable[itemHashIndex] = itemPtr->getNext();
                    else
                        prevPtr->setNext(itemPtr->getNext());

                    delete itemPtr;
                    itemPtr = nullptr;
                    break;
                }

                prevPtr = itemPtr;
                itemPtr = itemPtr->getNext();
            }
        }

        itemFound = true;
    }

    return itemFound;
}

template <class KeyType, class ItemType>
HashedEntry<KeyType, ItemType> *HashedDictionary<KeyType, ItemType>::getEntry(const KeyType &searchKey)
{
    bool itemFound = false;

    // Compute the hashed index into the array
    int itemHashIndex = getHashIndex(searchKey);

    HashedEntry<KeyType, ItemType> *itemPtr = hashTable[itemHashIndex];

    while (itemPtr)
    {
        if (itemPtr->getKey() == searchKey)
        {
            itemFound = true;
            break;
        }
        itemPtr = itemPtr->getNext();
    }

    return itemPtr;
}
template <class KeyType, class ItemType>
HashedEntry<KeyType, ItemType> *HashedDictionary<KeyType, ItemType>::maxWord()
{
    size_t maxCount = 0;
    HashedEntry<KeyType, ItemType> *maxWordPtr = nullptr;

    for (size_t i = 0; i < hashTableSize; i++)
    {
        if (hashTable[i])
        {
            HashedEntry<KeyType, ItemType> *currPtr = hashTable[i];

            while (currPtr)
            {
                if (maxCount < currPtr->getCount())
                {
                    maxCount = currPtr->getCount();
                    maxWordPtr = currPtr;
                }
                currPtr = currPtr->getNext();
            }
        }
    }

    return maxWordPtr;
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::wordCount()
{
    int sum = 0;

    for (size_t i = 0; i < hashTableSize; i++)
    {
        if (hashTable[i])
        {
            HashedEntry<KeyType, ItemType> *currPtr = hashTable[i];

            while (currPtr)
            {
                sum += currPtr->getCount();
                currPtr = currPtr->getNext();
            }
        }
    }

    return sum;
}
