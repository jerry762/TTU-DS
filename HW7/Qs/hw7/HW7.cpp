// HW6.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "BagInterface.h"
#include "ArrayBag.h"
#include "LinkedBag.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

void displayBag(ArrayBag<string>& bag)
{
   cout << "The bag contains " << bag.getCurrentSize()
        << " items: "
		;
   vector<string> bagItems = bag.toVector();
   int numberOfEntries = (int)bagItems.size();
   for (int i = 0; i < numberOfEntries; i++)
   {
      cout << bagItems[i] << " ";
   }  // end for
   cout << endl;
}  // end displayBag

void bagTester(ArrayBag<string>& bag)
{
   cout << "isEmpty: returns " << bag.isEmpty() << endl;
   displayBag(bag);
   
   string items[] = {"1A", "2B", "3C", "4D", "5E", "6F"};
   cout << "Add 6 items to the bag: " << endl;

   for (int i = 0; i < 6; i++)
   {
      bag.add(items[i]);
   }  // end for
   
   cout << "isEmpty: returns " << bag.isEmpty() << endl;
   cout << "getCurrentSize: returns " << bag.getCurrentSize() << endl;
   cout << "add(\"extra\") returns " << bag.add("extra") << endl;
   cout << "addFirst(\"extra\") returns " << bag.addFirst("extra") << endl;
   cout << "insertFirst(\"extra\") returns " << bag.insertFirst("extra") << endl;
   
   displayBag(bag);

   for (int i = 0; i < 6; i++)
   {
      bag.deleteFirst();
	  displayBag(bag);
	  bag.addFirst(items[i]);
	  displayBag(bag);
	  bag.removeFirst();
	  displayBag(bag);
	  bag.insertFirst(items[i]);
	  displayBag(bag);
	  bag.remove(items[i]);
	  displayBag(bag);
   } 
   
   cout << "remove(\"extra\") returns " << bag.remove("extra") << endl;
   cout << "removeFirst() returns " << bag.removeFirst() << endl;
   cout << "deleteFirst() returns " << bag.deleteFirst() << endl;
} // end bagTester

void displayBag(LinkedBag<string>* bagPtr)
{
   cout << "The bag contains " << bagPtr->getCurrentSize()
   << " items: ";
	vector<string> bagItems = bagPtr->toVector();
   
   int numberOfEntries = (int)bagItems.size();
   
   for (int i = 0; i < numberOfEntries; i++)
   {
      cout << bagItems[i] << " ";
   }  // end for
   cout << endl;
}  // end displayBag

void bagTester(LinkedBag<string>* bagPtr)
{
   cout << "isEmpty: returns " << bagPtr->isEmpty() << endl;
   
   string items[] = {"1A", "2B", "3C", "4D", "5E", "6F"};
   cout << "Add 6 items to the bag: " << endl;
   
   for (int i = 0; i < 6; i++)
       bagPtr->add(items[i]);
   
   displayBag(bagPtr);
   cout << "isEmpty: returns " << bagPtr->isEmpty() << endl;
   cout << "getCurrentSize returns : " << bagPtr->getCurrentSize() << endl;
   cout << "Try to add another entry: add(\"extra\") returns "
   << bagPtr->add("extra") << endl;
   cout << "Try to add another entry: addToLast(\"extra1\") returns "
   << bagPtr->addLast("extra1") << endl;
   cout << "Try to add another entry: add2ndToLast(\"extra2\") returns "
   << bagPtr->add2ndToLast("extra2") << endl;

   displayBag(bagPtr);  
   bagPtr->remove2ndToLast();
   displayBag(bagPtr);  
   bagPtr->removeLast();
   displayBag(bagPtr);  
   bagPtr->remove("extra");
   displayBag(bagPtr);  

   for (int i = 0; i < 7; i++)
   {
      bagPtr->removeLast();
	  displayBag(bagPtr);
   }  // end for

   bagPtr->clear();

   for (int i = 0; i < 6; i++)
      bagPtr->add2ndToLast(items[i]);

   displayBag(bagPtr);

   for (int i = 0; i < 7; i++)
   {
      bagPtr->remove2ndToLast();
	  displayBag(bagPtr);
   }  // end for

   for (int i = 0; i < 6; i++)
      bagPtr->addLast(items[i]);

   displayBag(bagPtr);
      
   for (int i = 0; i < 6; i++)
   {
      bagPtr->removeLast();
	  displayBag(bagPtr);
	  bagPtr->addLast(items[i]);
	  displayBag(bagPtr);
	  bagPtr->remove2ndToLast();
	  displayBag(bagPtr);
	  bagPtr->add2ndToLast(items[i]);
	  displayBag(bagPtr);
	  bagPtr->remove(items[i]);
	  displayBag(bagPtr);
   } 
   bagPtr->remove2ndToLast();
   displayBag(bagPtr);  
   bagPtr->removeLast();
   displayBag(bagPtr);  
}  // end bagTester

int main()
{
   char userChoice;

   while (toupper(userChoice) != 'X') {
	   cout << "Enter 'A' to test the array-based implementation\n"
		   << " 'L' to test the link-based implementation or 'X' to exit: ";
	   cin >> userChoice;

	   if (toupper(userChoice) == 'A')
	   {
		  ArrayBag<string> bag;
		  cout << "Testing the Array-Based Bag:" << endl;
		  cout << "The initial bag is empty." << endl;
		  bagTester(bag);
	   }
	   else
	   {
		  LinkedBag<string>* bagPtr = nullptr;
		  bagPtr = new LinkedBag<string>();
		  cout << "Testing the Link-Based Bag:" << endl;
		  cout << "The initial bag is empty." << endl;
	      bagTester(bagPtr);
	      delete bagPtr;
   	      bagPtr = nullptr;
	   }  // end if

	   cout << "All done!\n\n" << endl;
   }
   
   return 0;
}  // end main
