//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing 18-5.

/** A class of entry objects for a hashing implementation of the
    ADT dictionary.
 @file HashedEntry.h */
 
#ifndef _HASHED_ENTRY
#define _HASHED_ENTRY

#include "Entry.h"

template<class KeyType, class ItemType>
class HashedEntry : public Entry<KeyType, ItemType>
{
private:
   HashedEntry<KeyType, ItemType>* nextPtr;
   
public:
   HashedEntry();
   HashedEntry(ItemType newEntry, KeyType searchKey);
   HashedEntry(ItemType newEntry, KeyType searchKey,
               HashedEntry<KeyType, ItemType>* nextEntryPtr);
   void setNext(HashedEntry<KeyType, ItemType>* nextEntryPtr);
   HashedEntry<KeyType, ItemType>* getNext() const;

}; // end HashedEntry

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry():nextPtr(nullptr)
{
}

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry(ItemType newEntry, KeyType searchKey):nextPtr(nullptr)
{
	setItem( newEntry );
	setKey( searchKey ); 
}

template<class KeyType, class ItemType>
void HashedEntry<KeyType, ItemType>::setNext(HashedEntry<KeyType, ItemType>* nextEntryPtr)
{
	nextPtr = nextEntryPtr;
}

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>* HashedEntry<KeyType, ItemType>::getNext() const
{
	return nextPtr;
}
#endif