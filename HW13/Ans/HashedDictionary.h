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
   bool add(const KeyType &searchKey, const ItemType &newItem);
   bool remove(const KeyType &searchKey);
   HashedEntry<KeyType, ItemType> *getEntry(const KeyType &searchKey);
   void traverse(int itemHashIndex, void visit(HashedEntry<KeyType, ItemType> &)) const;
   void clear();
   int getNumberOfItems();
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
bool HashedDictionary<KeyType, ItemType>::add(const KeyType &searchKey, const ItemType &newItem)
{
   // Create entry to add to dictionary
   HashedEntry<KeyType, ItemType> *entryToAddPtr =
       new HashedEntry<KeyType, ItemType>(newItem, searchKey);

   // Compute the hashed index into the array
   int itemHashIndex = getHashIndex(searchKey);

   // Add the entry to the chain at itemHashIndex
   if (hashTable[itemHashIndex] == nullptr)
   {
      hashTable[itemHashIndex] = entryToAddPtr;
   }
   else
   {
      entryToAddPtr->setNext(hashTable[itemHashIndex]);
      hashTable[itemHashIndex] = entryToAddPtr;
   } // end if

   return true;
} // end add

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType &searchKey)
{
   bool itemFound = false;

   // Compute the hashed index into the array
   int itemHashIndex = getHashIndex(searchKey);
   if (hashTable[itemHashIndex] != nullptr)
   {
      // Special case - first node has target
      if (searchKey == hashTable[itemHashIndex]->getKey())
      {
         HashedEntry<KeyType, ItemType> *entryToRemovePtr =
             hashTable[itemHashIndex];
         hashTable[itemHashIndex] = hashTable[itemHashIndex]->getNext();
         delete entryToRemovePtr;
         entryToRemovePtr = nullptr; // For safety
         itemFound = true;
      }
      else // Search the rest of the chain
      {
         HashedEntry<KeyType, ItemType> *prevPtr = hashTable[itemHashIndex];
         HashedEntry<KeyType, ItemType> *curPtr = prevPtr->getNext();
         while ((curPtr != nullptr) && !itemFound)
         {
            // Found item in chain so remove that node
            if (searchKey == curPtr->getKey())
            {
               prevPtr->setNext(curPtr->getNext());
               delete curPtr;
               curPtr = nullptr; // For safety
               itemFound = true;
            }
            else // Look at next entry in chain
            {
               prevPtr = curPtr;
               curPtr = curPtr->getNext();
            } // end if
         }    // end while
      }       // end if
   }          // end if

   return itemFound;
} // end remove

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::isEmpty()
{
   return false;
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getHashIndex(const KeyType &searchKey)
{
   int strLen = searchKey.length();

   if (strLen == 0)
      return 0;

   return (((unsigned char)searchKey[0] + (strLen > 1 ? (unsigned char)searchKey[1] : 0)) % hashTableSize);

   // another hash value
   return (((unsigned char)searchKey[0] + (unsigned char)searchKey[strLen - 1]) % hashTableSize);

   // yet another hash value
   int hashValue = (unsigned char)searchKey[0];

   for (int i = 1; i < strLen; ++i)
      hashValue = (hashValue * 256 + (unsigned char)searchKey[i]) % hashTableSize;

   return hashValue;
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getNumberOfItems()
{
   return 0;
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getTableSize()
{
   return hashTableSize;
}

template <class KeyType, class ItemType>
HashedEntry<KeyType, ItemType> *HashedDictionary<KeyType, ItemType>::getEntry(const KeyType &searchKey)
{
   // Compute the hashed index into the array
   int itemHashIndex = getHashIndex(searchKey);

   // add yor code here

   return nullptr;
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::clear()
{
   HashedEntry<KeyType, ItemType> *nextPtr, *curPtr;

   for (int i = 0; i < hashTableSize; i++)
   {
      curPtr = hashTable[i];

      // add your code here

   } // end for
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::traverse(int itemHashIndex, void visit(HashedEntry<KeyType, ItemType> &)) const
{
   HashedEntry<KeyType, ItemType> *itemPtr = hashTable[itemHashIndex];

   // add your code here
}