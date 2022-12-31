//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** A class of nodes for a link-based binary tree.
 Listing 16-2.
 @file BinaryNode.h */

#ifndef _BINARY_NODE
#define _BINARY_NODE

template <class ItemType>
class BinaryNode
{
private:
   ItemType item; // Data portion
   int count;
   int leftSize;
   BinaryNode<ItemType> *leftChildPtr;  // Pointer to left child
   BinaryNode<ItemType> *rightChildPtr; // Pointer to right child

public:
   BinaryNode();
   BinaryNode(const ItemType &anItem);
   BinaryNode(const ItemType &anItem,
              BinaryNode<ItemType> *leftPtr,
              BinaryNode<ItemType> *rightPtr);

   void setItem(const ItemType &anItem);
   ItemType getItem() const;
   int getCount() const;
   void setCount(int newCount);
   int countUp();
   int countDown();
   int getLeftSize();
   void setLeftSize(int leftTreeSize);
   void increaseLeftSize();
   void decreaseLeftSize();

   bool isLeaf() const;

   BinaryNode<ItemType> *getLeftChildPtr() const;
   BinaryNode<ItemType> *getRightChildPtr() const;

   void setLeftChildPtr(BinaryNode<ItemType> *leftPtr);
   void setRightChildPtr(BinaryNode<ItemType> *rightPtr);
}; // end BinaryNode

template <class ItemType>
BinaryNode<ItemType>::BinaryNode() : leftChildPtr(nullptr), rightChildPtr(nullptr)
{
} // end default constructor

template <class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType &anItem) : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr), count(1), leftSize(0)
{
} // end constructor

template <class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType &anItem, BinaryNode<ItemType> *leftPtr, BinaryNode<ItemType> *rightPtr) : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr), count(1), leftSize(0)
{
} // end constructor

template <class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType &anItem)
{
   item = anItem;
} // end setItem

template <class ItemType>
ItemType BinaryNode<ItemType>::getItem() const
{
   return item;
} // end getItem

template <class ItemType>
bool BinaryNode<ItemType>::isLeaf() const
{
   return (leftChildPtr == nullptr && rightChildPtr == nullptr);
} // end setItem

template <class ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(BinaryNode<ItemType> *leftPtr)
{
   leftChildPtr = leftPtr;
} // end setNext

template <class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(BinaryNode<ItemType> *rightPtr)
{
   rightChildPtr = rightPtr;
} // end setNext

template <class ItemType>
BinaryNode<ItemType> *BinaryNode<ItemType>::getLeftChildPtr() const
{
   return leftChildPtr;
} // end getLeftChildPtr

template <class ItemType>
BinaryNode<ItemType> *BinaryNode<ItemType>::getRightChildPtr() const
{
   return rightChildPtr;
} // end getNext

template <class ItemType>
void BinaryNode<ItemType>::setCount(int newCount)
{
   count = newCount;
}

template <class ItemType>
int BinaryNode<ItemType>::getCount() const
{
   return count;
}

template <class ItemType>
int BinaryNode<ItemType>::countUp()
{
   return ++count;
}

template <class ItemType>
int BinaryNode<ItemType>::countDown()
{
   return --count;
}

template <class ItemType>
int BinaryNode<ItemType>::getLeftSize()
{
   return leftSize;
}

template <class ItemType>
void BinaryNode<ItemType>::setLeftSize(int leftTreeSize)
{
   leftSize = leftTreeSize;
}

template <class ItemType>
void BinaryNode<ItemType>::increaseLeftSize()
{
   leftSize++;
}

template <class ItemType>
void BinaryNode<ItemType>::decreaseLeftSize()
{
   leftSize--;
}

#endif
