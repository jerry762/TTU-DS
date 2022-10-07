//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** A class of entry objects for an array-based implementation of the ADT dictionary.
    Listing 18-2.
 @file Entry.h */

#ifndef _ENTRY
#define _ENTRY

template <class KeyType, class ItemType>
class Entry
{
private:
   ItemType item;
   KeyType key;
   
protected:
   void setKey(const KeyType& searchKey);
   
public:
   Entry();
   Entry(ItemType newEntry, KeyType searchKey);
   ItemType getItem() const;
   KeyType getKey() const;
   void setItem(const ItemType& newEntry);
   bool operator==(const Entry<KeyType, ItemType>& rightHandItem) const;
   bool operator>(const Entry<KeyType, ItemType>& rightHandItem) const;
}; // end Entry

#//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

template <class KeyType, class ItemType>
Entry<KeyType, ItemType>::Entry()
{
}

template <class KeyType, class ItemType>
Entry<KeyType, ItemType>::Entry(ItemType newEntry, KeyType searchKey): item(newEntry), key(searchKey)
{
}

template <class KeyType, class ItemType>
bool Entry<KeyType, ItemType>::operator==(const Entry<KeyType, ItemType>& rightHandItem) const
{
   return (searchKey == rightHandItem.getKey());
}  // end operator==

template <class KeyType, class ItemType>
bool Entry<KeyType, ItemType>::operator>(const Entry<KeyType, ItemType>& rightHandItem) const
{
   return (searchKey > rightHandItem.getKey());
}  // end operator==

template <class KeyType, class ItemType>
ItemType Entry<KeyType, ItemType>:: getItem() const
{
	return item;
}

template <class KeyType, class ItemType>
KeyType Entry<KeyType, ItemType>:: getKey() const
{
	return key;
}

template <class KeyType, class ItemType>
void Entry<KeyType, ItemType>:: setKey(const KeyType& searchKey)
{
	key = searchKey;
}
template <class KeyType, class ItemType>
void Entry<KeyType, ItemType>::setItem(const ItemType& newEntry)
{
	item = newEntry;
}
#endif
