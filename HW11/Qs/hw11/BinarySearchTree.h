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
//#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"
#include <queue>
#include <stack>

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
private:
   BinaryNode<ItemType>* rootPtr;
   
protected:
   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods.
   //------------------------------------------------------------
   // Recursively finds where the given node should be placed and
   // inserts it in a leaf at that point.
   BinaryNode<ItemType>* insertInorder(BinaryNode<ItemType>* subTreePtr,
                                       BinaryNode<ItemType>* newNode);
   
   // Removes the given target value from the tree while maintaining a
   // binary search tree.
   BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr,
                                     const ItemType target,
                                     bool& success);
   
   // Removes a given node from a tree while maintaining a
   // binary search tree.
   BinaryNode<ItemType>* removeNode(BinaryNode<ItemType>* nodePtr);
   
   // Removes the leftmost node in the left subtree of the node
   // pointed to by nodePtr.
   // Sets inorderSuccessor to the value in this node.
   // Returns a pointer to the revised subtree.
   BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                            ItemType& inorderSuccessor, int& newWordCount);
   
   BinaryNode<ItemType>* removeRightmostNode(BinaryNode<ItemType>* nodePtr,
                                            ItemType& inorderSuccessor, int& newWordCount);
   
   // Returns a pointer to the node containing the given value,
   // or nullptr if not found.
   BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr,
                                  const ItemType& target) const;

   void inorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* treePtr) const;
   void levelorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* treePtr) const;
   
public:
   //------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------
   BinarySearchTree();
   BinarySearchTree(const ItemType& rootItem);
   BinarySearchTree(const BinarySearchTree<ItemType>& tree);
   virtual ~BinarySearchTree();
   
   //------------------------------------------------------------
   // Public Methods Section.
   //------------------------------------------------------------
   bool isEmpty() const;
   //int getHeight() const;
   //int getNumberOfNodes() const;
   //ItemType getRootData() const throw(PrecondViolatedExcep);
   //void setRootData(const ItemType& newData) const  throw(PrecondViolatedExcep);
   bool add(const ItemType& newEntry);
   bool remove(const ItemType& anEntry);
//   void clear();
//   ItemType getEntry(const ItemType& anEntry) const;
//   throw(NotFoundException);
//   bool contains(const ItemType& anEntry) const;
   
   //------------------------------------------------------------
   // Public Traversals Section.
   //------------------------------------------------------------
   //void preorderTraverse(void visit(ItemType&)) const;
   void inorderTraverse(void visit(BinaryNode<ItemType>&)) const;
   //void postorderTraverse(void visit(ItemType&)) const;
   void levelorderTraverse(void visit(BinaryNode<ItemType>&)) const;
   
   //------------------------------------------------------------
   // Overloaded Operator Section.
   //------------------------------------------------------------
   BinarySearchTree<ItemType>& operator=(const BinarySearchTree<ItemType>& rightHandSide);   
}; // end BinarySearchTree

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : rootPtr(nullptr)
{
}  // end default constructor

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem)
{
   rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
}  // end constructor

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& treePtr)
{
   rootPtr = copyTree(treePtr.rootPtr);
}  // end copy constructor

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
   destroyTree( rootPtr );
}  // end destructor

//////////////////////////////////////////////////////////////
//      Protected Tree Traversal Sub-Section
//////////////////////////////////////////////////////////////

template<class ItemType>
void BinarySearchTree<ItemType>::inorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* treePtr) const
{
   if (treePtr != nullptr)
   {
      inorder(visit, treePtr->getLeftChildPtr());
      visit( *treePtr );
      inorder(visit, treePtr->getRightChildPtr());
   }  // end if
}  // end inorder



template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
   return ( rootPtr == nullptr ) ;
}  // end add


template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(BinaryNode<ItemType>&)) const
{
   inorder(visit, rootPtr);
}  // end inorderTraverse

template<class ItemType>
void BinarySearchTree<ItemType>::levelorderTraverse(void visit(BinaryNode<ItemType>&)) const
{
   levelorder(visit, rootPtr);
}  // end inorderTraverse

template<class ItemType>
void BinarySearchTree<ItemType>::levelorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* treePtr) const
{
	// the data structures that may be useful
	queue<BinaryNode<ItemType>*> nodeQueue;
	stack<BinaryNode<ItemType>*> nodeStack;
	BinaryNode<ItemType> *tmpPtr = treePtr;


	// the following is actually an interative inoder
	// replace the code with yours


	do {
		while ( tmpPtr != NULL ) {
			nodeStack.push( tmpPtr );
			tmpPtr = tmpPtr->getLeftChildPtr();
		}

		if ( ! nodeStack.empty() ) {
			tmpPtr = nodeStack.top();
			visit( *tmpPtr );
			nodeStack.pop();
			tmpPtr = tmpPtr->getRightChildPtr();
		}
	} while ( ! nodeStack.empty() || tmpPtr != NULL );
}  // end levelorder

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData)
{
   BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
   rootPtr = insertInorder(rootPtr, newNodePtr);
   return true;
}  // end add

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType>* subTreePtr,
                                                            BinaryNode<ItemType>* newNodePtr)
{
	if (subTreePtr == nullptr)
		return newNodePtr;

	BinaryNode<ItemType>* tempPtr;

	if ( subTreePtr->getItem() > newNodePtr->getItem() ) {
		tempPtr = insertInorder( subTreePtr->getLeftChildPtr(), newNodePtr );
		subTreePtr->setLeftChildPtr( tempPtr );
	}
	else {
		tempPtr = insertInorder( subTreePtr->getRightChildPtr(), newNodePtr );
		subTreePtr->setRightChildPtr( tempPtr );
	}
	
	return subTreePtr;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& anEntry)
{
	bool success = false;
	rootPtr = removeValue( rootPtr, anEntry, success );

	return success;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr,
                                     const ItemType target,
                                     bool& success)
{
	if ( subTreePtr == nullptr ) {
		success = false;
		return nullptr;
	}
	
	if ( subTreePtr->getItem() == target ) {
		subTreePtr = removeNode( subTreePtr );
		success = true;
		return subTreePtr;
	}
	
	BinaryNode<ItemType>* tempPtr;

	if ( subTreePtr->getItem() > target ) {
		tempPtr = removeValue( subTreePtr->getLeftChildPtr(), target, success );
		subTreePtr->setLeftChildPtr( tempPtr );
		return subTreePtr;
	}
	else {
		tempPtr = removeValue( subTreePtr->getRightChildPtr(), target, success );
		subTreePtr->setRightChildPtr( tempPtr );
		return subTreePtr;
	}
}
   
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeNode(BinaryNode<ItemType>* nodePtr)
{
	if ( nodePtr->isLeaf() ) {
		delete nodePtr;
		nodePtr = nullptr;
		return nodePtr;
	} 

	if ( nodePtr->getLeftChildPtr() == nullptr || nodePtr->getRightChildPtr() == nullptr ) {
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightChildPtr();

		if ( nodeToConnectPtr == nullptr )
			nodeToConnectPtr = nodePtr->getLeftChildPtr();

		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;
	}

	BinaryNode<ItemType>* tempPtr;
	ItemType newNodeValue;
	int newWordCount;

	tempPtr = removeLeftmostNode( nodePtr->getRightChildPtr(), newNodeValue, newWordCount );
	nodePtr->setRightChildPtr( tempPtr );
//	tempPtr = removeRightmostNode( nodePtr->getLeftChildPtr(), newNodeValue, newWordCount );
//	nodePtr->setLeftChildPtr( tempPtr );
	nodePtr->setItem( newNodeValue );
	nodePtr->setCount( newWordCount );
	return nodePtr;
}
   
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                            ItemType& inorderSuccessor, int& newWordCount)
{
	if ( nodePtr->getLeftChildPtr() == nullptr ) {
		inorderSuccessor = nodePtr->getItem();
		newWordCount = nodePtr->getCount();
		return removeNode( nodePtr );
	} 
	else 
		return removeLeftmostNode( nodePtr->getLeftChildPtr(), inorderSuccessor, newWordCount );
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeRightmostNode(BinaryNode<ItemType>* nodePtr,
                                            ItemType& inorderPredecessor, int& newWordCount)
{


	// add your code here


}

#endif
