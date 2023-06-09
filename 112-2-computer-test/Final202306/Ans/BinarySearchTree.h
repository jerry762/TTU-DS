//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing 16-4.

/** Link-based implementation of the ADT binary search tree.
 @file BinarySearchTree.h */

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
// #include "NotFoundException.h"
#include "PrecondViolatedExcep.h"
#include <queue>
#include <stack>

template <class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
private:
	BinaryNode<ItemType> *rootPtr;

protected:
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	// Recursively finds where the given node should be placed and
	// inserts it in a leaf at that point.
	BinaryNode<ItemType> *insertInorder(BinaryNode<ItemType> *subTreePtr,
										BinaryNode<ItemType> *newNode);

	// Removes the given target value from the tree while maintaining a
	// binary search tree.
	BinaryNode<ItemType> *removeValue(BinaryNode<ItemType> *subTreePtr,
									  const ItemType target,
									  bool &success);

	// Removes a given node from a tree while maintaining a
	// binary search tree.
	BinaryNode<ItemType> *removeNode(BinaryNode<ItemType> *nodePtr);

	// Removes the leftmost node in the left subtree of the node
	// pointed to by nodePtr.
	// Sets inorderSuccessor to the value in this node.
	// Returns a pointer to the revised subtree.
	BinaryNode<ItemType> *removeLeftmostNode(BinaryNode<ItemType> *nodePtr,
											 ItemType &inorderSuccessor);

	BinaryNode<ItemType> *removeRightmostNode(BinaryNode<ItemType> *nodePtr,
											  ItemType &inorderSuccessor);

	// Returns a pointer to the node containing the given value,
	// or nullptr if not found.
	BinaryNode<ItemType> *findNode(BinaryNode<ItemType> *subtreePtr,
								   const ItemType &target) const;

	void inorder(void visit(BinaryNode<ItemType> &), BinaryNode<ItemType> *subtreePtr) const;
	bool isAllTwoChildren_Recu(BinaryNode<ItemType> *subtreePtr, const ItemType target);
	bool isAllTwoChildren_Iter(BinaryNode<ItemType> *subtreePtr, const ItemType target);
	int nodesOfTwoChildren_Recu(BinaryNode<ItemType> *subtreePtr);
	int nodesOfTwoChildren_Iter(BinaryNode<ItemType> *subtreePtr);

public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BinarySearchTree();
	BinarySearchTree(const ItemType &rootItem);
	BinarySearchTree(const BinarySearchTree<ItemType> &tree);
	virtual ~BinarySearchTree();

	//------------------------------------------------------------
	// Public Methods Section.
	//------------------------------------------------------------
	bool isEmpty() const;
	// int getHeight() const;
	// int getNumberOfNodes() const;
	// ItemType getRootData() const throw(PrecondViolatedExcep);
	// void setRootData(const ItemType& newData) const  throw(PrecondViolatedExcep);
	bool add(const ItemType &newEntry);
	bool remove(const ItemType &anEntry);
	void clear();
	//   ItemType getEntry(const ItemType& anEntry) const;
	//   throw(NotFoundException);
	//   bool contains(const ItemType& anEntry) const;
	void reverse();
	ItemType find(const ItemType target);

	bool isAllTwoChildrenR(const ItemType target);
	bool isAllTwoChildrenI(const ItemType target);
	int nodesOfTwoChildrenR();
	int nodesOfTwoChildrenI();

	//------------------------------------------------------------
	// Public Traversals Section.
	//------------------------------------------------------------
	void inorderTraverse(void visit(BinaryNode<ItemType> &)) const;

	//------------------------------------------------------------
	// Overloaded Operator Section.
	//------------------------------------------------------------
	BinarySearchTree<ItemType> &operator=(const BinarySearchTree<ItemType> &rightHandSide);
}; // end BinarySearchTree

template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : rootPtr(nullptr)
{
} // end default constructor

template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType &rootItem)
{
	rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
} // end constructor

template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType> &treePtr)
{
	rootPtr = copyTree(treePtr.rootPtr);
} // end copy constructor

template <class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
	this->destroyTree(rootPtr);
} // end destructor

//////////////////////////////////////////////////////////////
//      Protected Tree Traversal Sub-Section
//////////////////////////////////////////////////////////////

template <class ItemType>
void BinarySearchTree<ItemType>::inorder(void visit(BinaryNode<ItemType> &), BinaryNode<ItemType> *subtreePtr) const
{
	if (subtreePtr != nullptr)
	{
		inorder(visit, subtreePtr->getLeftChildPtr());
		visit(*subtreePtr);
		inorder(visit, subtreePtr->getRightChildPtr());
	} // end if
} // end inorder

//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

template <class ItemType>
void BinarySearchTree<ItemType>::clear()
{
	this->destroyTree(rootPtr);
	rootPtr = nullptr;
}

template <class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
	return (rootPtr == nullptr);
}

template <class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType &newData)
{
	BinaryNode<ItemType> *newNodePtr = new BinaryNode<ItemType>(newData);
	rootPtr = insertInorder(rootPtr, newNodePtr);
	return true;
} // end add

template <class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType> *subTreePtr,
																BinaryNode<ItemType> *newNodePtr)
{
	if (subTreePtr == nullptr)
		return newNodePtr;

	if (subTreePtr->getItem() == newNodePtr->getItem())
	{

		// add some code here

		return subTreePtr;
	}

	BinaryNode<ItemType> *tempPtr;

	if (subTreePtr->getItem() > newNodePtr->getItem())
	{
		tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr);
		subTreePtr->setLeftChildPtr(tempPtr);
	}
	else
	{
		tempPtr = insertInorder(subTreePtr->getRightChildPtr(), newNodePtr);
		subTreePtr->setRightChildPtr(tempPtr);
	}

	return subTreePtr;
}

template <class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(BinaryNode<ItemType> &)) const
{
	inorder(visit, rootPtr);
}

template <class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType &anEntry)
{
	bool success = false;
	rootPtr = removeValue(rootPtr, anEntry, success);

	return success;
}

template <class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType> *subTreePtr,
															  const ItemType target,
															  bool &success)
{
	if (subTreePtr == nullptr)
	{
		success = false;
		return nullptr;
	}

	if (subTreePtr->getItem() == target)
	{

		// add some code here

		return subTreePtr;
	}

	BinaryNode<ItemType> *tempPtr;

	if (subTreePtr->getItem() > target)
	{

		// add some code here
	}
	else
	{

		// add some code here
	}

	return subTreePtr;
}

template <class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::removeNode(BinaryNode<ItemType> *nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = nullptr;
		return nodePtr;
	}

	if (nodePtr->getLeftChildPtr() == nullptr || nodePtr->getRightChildPtr() == nullptr)
	{
		BinaryNode<ItemType> *nodeToConnectPtr = nodePtr->getRightChildPtr();

		if (nodeToConnectPtr == nullptr)
			nodeToConnectPtr = nodePtr->getLeftChildPtr();

		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;
	}

	BinaryNode<ItemType> *tempPtr;
	ItemType newNodeValue;

	tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue);
	nodePtr->setRightChildPtr(tempPtr);
	nodePtr->setItem(newNodeValue);

	return nodePtr;
}

template <class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType> *nodePtr,
																	 ItemType &inorderSuccessor)
{
	if (nodePtr->getLeftChildPtr() == nullptr)
	{
		inorderSuccessor = nodePtr->getItem();
		return removeNode(nodePtr);
	}
	else
	{
		BinaryNode<ItemType> *tempPtr;
		tempPtr = removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor);
		nodePtr->setLeftChildPtr(tempPtr);
		return nodePtr;
	}
}

template <class ItemType>
int BinarySearchTree<ItemType>::nodesOfTwoChildrenR()
{
	return nodesOfTwoChildren_Recu(rootPtr);
}

template <class ItemType>
int BinarySearchTree<ItemType>::nodesOfTwoChildren_Recu(BinaryNode<ItemType> *subtreePtr) //* add your code here
{
	if (!subtreePtr)
		return 0;

	if (subtreePtr->getLeftChildPtr() && subtreePtr->getRightChildPtr())
	{
		return 1 + nodesOfTwoChildren_Recu(subtreePtr->getLeftChildPtr()) + nodesOfTwoChildren_Recu(subtreePtr->getRightChildPtr());
	}
	else
	{
		return nodesOfTwoChildren_Recu(subtreePtr->getLeftChildPtr()) + nodesOfTwoChildren_Recu(subtreePtr->getRightChildPtr());
	}

	return 0;
}
template <class ItemType>
int BinarySearchTree<ItemType>::nodesOfTwoChildrenI()
{
	return nodesOfTwoChildren_Iter(rootPtr);
}

template <class ItemType>
int BinarySearchTree<ItemType>::nodesOfTwoChildren_Iter(BinaryNode<ItemType> *subtreePtr) //* add your code here
{
	int count = 0;
	queue<BinaryNode<ItemType> *> q;

	if (subtreePtr)
		q.push(subtreePtr);

	while (!q.empty())
	{
		BinaryNode<ItemType> *temp = q.front();

		q.pop();

		if (temp->getLeftChildPtr() && temp->getRightChildPtr())
			count++;

		if (temp->getLeftChildPtr())
			q.push(temp->getLeftChildPtr());

		if (temp->getRightChildPtr())
			q.push(temp->getRightChildPtr());
	}

	return count;
}

template <class ItemType>
bool BinarySearchTree<ItemType>::isAllTwoChildrenR(const ItemType target)
{
	return (isAllTwoChildren_Recu(rootPtr, target));
}

template <class ItemType>
bool BinarySearchTree<ItemType>::isAllTwoChildren_Recu(BinaryNode<ItemType> *subtreePtr, const ItemType target) //* add your code here
{
	if (!subtreePtr)
		return false;

	if (target > subtreePtr->getItem())
		return isAllTwoChildren_Recu(subtreePtr->getRightChildPtr(), target);
	else if (target < subtreePtr->getItem())
		return isAllTwoChildren_Recu(subtreePtr->getLeftChildPtr(), target);
	else
	{
		queue<BinaryNode<ItemType> *> q;

		q.push(subtreePtr);

		while (!q.empty())
		{
			BinaryNode<ItemType> *temp = q.front();

			q.pop();

			if ((temp->getLeftChildPtr() == nullptr && temp->getRightChildPtr() != nullptr) ||
				(temp->getLeftChildPtr() != nullptr && temp->getRightChildPtr() == nullptr))
				return false;

			if (temp->getLeftChildPtr())
				q.push(temp->getLeftChildPtr());

			if (temp->getRightChildPtr())
				q.push(temp->getRightChildPtr());
		}
		return true;
	}
} // end

template <class ItemType>
bool BinarySearchTree<ItemType>::isAllTwoChildrenI(const ItemType target)
{
	return (isAllTwoChildren_Iter(rootPtr, target));
}

template <class ItemType>
bool BinarySearchTree<ItemType>::isAllTwoChildren_Iter(BinaryNode<ItemType> *subtreePtr, const ItemType target) //* add your code here
{
	while (subtreePtr)
	{
		if (target > subtreePtr->getItem())
			subtreePtr = subtreePtr->getRightChildPtr();
		else if (target < subtreePtr->getItem())
			subtreePtr = subtreePtr->getLeftChildPtr();
		else
		{
			queue<BinaryNode<ItemType> *> q;

			q.push(subtreePtr);

			while (!q.empty())
			{
				BinaryNode<ItemType> *temp = q.front();

				q.pop();

				if ((temp->getLeftChildPtr() == nullptr && temp->getRightChildPtr() != nullptr) ||
					(temp->getLeftChildPtr() != nullptr && temp->getRightChildPtr() == nullptr))
					return false;

				if (temp->getLeftChildPtr())
					q.push(temp->getLeftChildPtr());

				if (temp->getRightChildPtr())
					q.push(temp->getRightChildPtr());
			}
			return true;
		}
	}
	return false;
} // end
#endif
