#include "BagInterface.h"
#include "Node.h"
#include <cstddef>
#include <string>

template <class ItemType>
class LinkedBag : public BagInterface<ItemType>
{
private:
   Node<ItemType> *headPtr; // Pointer to first node
   int itemCount;           // Current count of bag items

public:
   LinkedBag();
   LinkedBag(const LinkedBag<ItemType> &aBag); // Copy constructor
   virtual ~LinkedBag();                       // Destructor should be virtual
   int getCurrentSize() const;
   bool isEmpty() const;
   bool add(const ItemType &newEntry);
   bool remove(const ItemType &anEntry);
   bool removeDuplicate();
   void clear();
   vector<ItemType> toVector() const;
};

template <class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0)
{
}

template <class ItemType>
LinkedBag<ItemType>::~LinkedBag()
{
   clear();
}

template <class ItemType>
bool LinkedBag<ItemType>::isEmpty() const
{
   return itemCount == 0;
}

template <class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const
{
   return itemCount;
}

template <class ItemType>
void LinkedBag<ItemType>::clear()
{
   Node<ItemType> *nodeToDeletePtr = headPtr;

   while (headPtr != nullptr)
   {
      headPtr = headPtr->getNext();

      // Return node to the system
      nodeToDeletePtr->setNext(nullptr);
      delete nodeToDeletePtr;

      nodeToDeletePtr = headPtr;
   } // end while
   // headPtr is nullptr; nodeToDeletePtr is nullptr

   itemCount = 0;
}

template <class ItemType>
bool LinkedBag<ItemType>::add(const ItemType &newEntry)
{

   // add your code here

   return false;
}

template <class ItemType>
vector<ItemType> LinkedBag<ItemType>::toVector() const
{
   vector<ItemType> bagContents;
   Node<ItemType> *curPtr = headPtr;
   int counter = 0;

   while ((curPtr != nullptr) && (counter < itemCount))
   {
      bagContents.push_back(curPtr->getItem());
      curPtr = curPtr->getNext();
      counter++;
   }

   return bagContents;
}

template <class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType &anEntry)
{

   // add your code here

   return false;
}

template <class ItemType>
bool LinkedBag<ItemType>::removeDuplicate()
{

   // add your code here

   return false;
}
