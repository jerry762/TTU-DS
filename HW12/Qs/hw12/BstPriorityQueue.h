
#include "BinarySearchTree.h"

template<class ItemType>
class BstPriorityQueue : public BinarySearchTree<ItemType>
{
public:
//	BstPQueue();
	bool pqIsEmpty() const;
	void pqInsert(const ItemType& newItem);
	void pqDelete(ItemType& priorityItem);
	void pqTraverse(void visit(BinaryNode<ItemType>&));
};

/** @file BstPQ.cpp
 * ADT priority queue.
 * A binary search tree represents the priority queue. */

template<class ItemType>
bool BstPriorityQueue<ItemType>::pqIsEmpty() const
{
	return isEmpty();
}  // end pqIsEmpty

template<class ItemType>
void BstPriorityQueue<ItemType>::pqInsert(const ItemType& newItem)
{
	this->add( newItem );
}  // end pqInsert

template<class ItemType>
void BstPriorityQueue<ItemType>::pqDelete(ItemType& priorityItem)
{
	BinaryNode<ItemType>* tempPtr;

	ItemType minimumValue;

	if ( findMinimumValue( minimumValue ) )
		remove(minimumValue);

	priorityItem = minimumValue;
}  // end pqDelete

template<class ItemType>
void BstPriorityQueue<ItemType>::pqTraverse(void visit(BinaryNode<ItemType>&))
{
      inorderTraverse( visit );
}
// End of implementation file.

