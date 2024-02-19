//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Listing 15-1.
 @file BinaryTreeInterface.h */

#ifndef _BINARY_TREE_INTERFACE
#define _BINARY_TREE_INTERFACE

template<class ItemType>
class BinaryTreeInterface
{
public:
   /** Tests whether this binary tree is empty.
    @return True if the binary tree is empty, or false if not. */
   virtual bool isEmpty() const = 0;
   
   /** Gets the height of this binary tree.
    @return The height of the binary tree. */
   virtual int getHeight() const = 0;
   
   /** Gets the number of nodes in this binary tree.
    @return The number of nodes in the binary tree. */
   virtual int getNumberOfNodes() const = 0;
   
   /** Gets the data that is in the root of this binary tree.
    @pre  The binary tree is not empty.
    @post  The root?™s data has been returned, and the binary tree is unchanged.
    @return  The data in the root of the binary tree. */
//   virtual ItemType getRootData() const = 0;
   
   /** Replaces the data item in the root of this binary tree
       with the given data, if the tree is not empty. However, if
       the tree is empty, inserts a new root node containing the
       given data into the tree.
    @pre  None.
    @post  The data in the root of the binary tree is as given.
    @param newData  The data for the root. */
   //virtual void setRootData(const ItemType& newData) = 0;
   
   /** Adds a new node containing the given data to this binary tree.
    @param newData  The data for the new node.
    @post  The binary tree contains a new node.
    @return  True if the addition is successful, or false not. */
   virtual bool add(const ItemType& newData) = 0;
   
   /** Removes the node containing the given data item from this binary tree.
    @param data  The data value to remove from the binary tree.
    @return  True if the removal is successful, or false not. */
   //virtual bool remove(const ItemType& data) = 0;
   
   /** Removes all nodes from this binary tree. */
 //  virtual void clear() = 0;
   
   /** Gets a specific entry in this binary tree.
    @post  The desired entry has been returned, and the binary tree
       is unchanged. If no such entry was found, an exception is thrown.
    @param anEntry  The entry to locate.
    @return  The entry in the binary tree that matches the given entry.
    @throw  NotFoundException if the given entry is not in the tree. */
   //virtual ItemType getEntry(const ItemType& anEntry) const;
//                    throw(NotFoundException) = 0;
   
   /** Tests whether a given entry occurs in this binary tree.
    @post  The binary search tree is unchanged.
    @param anEntry  The entry to find.
    @return  True if the entry occurs in the tree, or false if not. */
   //virtual bool contains(const ItemType& anEntry) const = 0;
   
   /** Traverses this binary tree in preorder (inorder, postorder) and
       calls the function visit once for each node.
    @param visit A client-defined function that performs an operation on
       or with the data in each visited node. */
   //virtual void preorderTraverse(void visit(ItemType&)) const = 0;
   virtual void inorderTraverse(void visit(const ItemType&)) const = 0;
   //virtual void postorderTraverse(void visit(ItemType&)) const = 0;
}; // end BinaryTreeInterface
#endif
