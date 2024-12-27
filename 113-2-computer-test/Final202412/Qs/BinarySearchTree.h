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

	void inorder(void visit(BinaryNode<ItemType> &), BinaryNode<ItemType> *subtreePtr) const;
	void levelorder(void visit(BinaryNode<ItemType> &), BinaryNode<ItemType> *subtreePtr) const;
	int singleChildCount_I(BinaryNode<ItemType> *subTreePtr);
	int singleChildCount_R(BinaryNode<ItemType> *subTreePtr);
	int nodeDegree_I(BinaryNode<ItemType> *subTreePtr, const ItemType target);
	int nodeDegree_R(BinaryNode<ItemType> *subTreePtr, const ItemType target);
	int getHeightHelper(BinaryNode<ItemType> *subTreePtr) const;

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
	int getHeight() const;
	// int getNumberOfNodes() const;
	// ItemType getRootData() const throw(PrecondViolatedExcep);
	// void setRootData(const ItemType& newData) const  throw(PrecondViolatedExcep);
	bool add(const ItemType &newEntry);
	bool remove(const ItemType &anEntry);
	void clear();
	//   ItemType getEntry(const ItemType& anEntry) const;
	//   throw(NotFoundException);
	//   bool contains(const ItemType& anEntry) const;
	int singleChildCount(string str);
	int nodeDegree(string str, const ItemType target);
	int getHeightDifference();

	//------------------------------------------------------------
	// Public Traversals Section.
	//------------------------------------------------------------
	void inorderTraverse(void visit(BinaryNode<ItemType> &)) const;
	void levelorderTraverse(void visit(BinaryNode<ItemType> &)) const;

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
int BinarySearchTree<ItemType>::getHeight() const
{
	return getHeightHelper(rootPtr);
}

template <class ItemType>
int BinarySearchTree<ItemType>::getHeightHelper(BinaryNode<ItemType> *subTreePtr) const
{

	// add your code here

	return 0;
}

template <class ItemType>
int BinarySearchTree<ItemType>::getHeightDifference()
{

	// add your code here

	return 0;
}

template <class ItemType>
int BinarySearchTree<ItemType>::nodeDegree(string str, const ItemType target)
{
	if (str == "i")
		return nodeDegree_I(rootPtr, target);
	if (str == "r")
		return nodeDegree_R(rootPtr, target);
	return 0;
}

template <class ItemType>
int BinarySearchTree<ItemType>::nodeDegree_I(BinaryNode<ItemType> *subtreePtr, const ItemType target)
{

	// add your code here

	return 0;
}

template <class ItemType>
int BinarySearchTree<ItemType>::nodeDegree_R(BinaryNode<ItemType> *subtreePtr, const ItemType target)
{

	// add your code here

	return 0;
}

template <class ItemType>
int BinarySearchTree<ItemType>::singleChildCount(string str)
{
	if (str == "i")
		return singleChildCount_I(rootPtr);
	if (str == "r")
		return singleChildCount_R(rootPtr);
	return 0;
}

template <class ItemType>
int BinarySearchTree<ItemType>::singleChildCount_I(BinaryNode<ItemType> *subtreePtr)
{

	// add your code here

	return 0;
}

template <class ItemType>
int BinarySearchTree<ItemType>::singleChildCount_R(BinaryNode<ItemType> *subtreePtr)
{

	// add your code here

	return 0;
}

#endif
