// HW12.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <list>
#include <limits>
#include <string>
#include <iostream>
#include "BstPriorityQueue.h"
#define PQSIZE	5

using namespace std;

void display(BinaryNode<string>& anItem)
{
	cout << anItem.getItem() << "  ";
}

void input(string sMessage, string &sInputString)
{
	do {
		cout << sMessage << endl;
		cin >> sInputString;
	}  while ( cin.fail() );

	return;
}

void pqListInsert( list<string>&pqList, const string item )
{


// replace the following code with yours
	
	list<string>::iterator itemIter = pqList.begin();
	pqList.insert( itemIter, item );

}

void pqArrayInsert( string* pqArray, int& size, const string item ) 
{


// replace the following code with yours

		pqArray[ size ] = item;
		++size;

}

int main()
{
 	string sInput, aString;
	
	// for BST priority queue
	BstPriorityQueue<string> myBstPQ;
	
	// for LIST priority queue
	list<string> myListPQ;
	list<string>::iterator itemIter;

	// for ARRAY priority queue
	string myArrayPQ[ PQSIZE ];
	int i, size = 0;

	while (1) {
		input( "\nEnter command: A to Add, R to Remove, D to Display, C to Clear, or X to Exit", sInput );
			
		if ( sInput == "A"  || sInput == "a" ) {
			input( "Enter a string: ",  aString );

			// BST priority queue
			myBstPQ.pqInsert( aString );
			
			// LIST priority queue
			pqListInsert( myListPQ, aString );
			
			// ARRAY priority queue
			pqArrayInsert( myArrayPQ, size, aString);
		} 
		else if ( sInput == "R" || sInput == "r" ) {
			
			// BST priority queue
			if ( myBstPQ.pqIsEmpty() )
				cout << "BST priority queue empty!"  << endl;
			else {
				myBstPQ.pqDelete( aString );
				cout << "Removed BST queued string is: " << aString << endl;
			}

			// LIST priority queue
			if ( myListPQ.empty()  )
				cout << "LIST priority queue empty!"  << endl;
			else {
				itemIter = myListPQ.begin();
				cout << "Removed LIST queued string is: " << *itemIter << endl;
				itemIter = myListPQ.erase( itemIter );
			}

			// ARRAY priority queue
			if ( size == 0 )
				cout << "ARRAY Priority queue empty!"  << endl;
			else {
				cout << "Removed ARRAY queued string is: " << myArrayPQ[ 0 ] << endl;
				
				for ( i = 0; i < size -1; ++i ) // shift data
					myArrayPQ[ i  ] = myArrayPQ[ i + 1 ];

				--size;
			}
		}
		else if ( sInput == "D" || sInput == "d" ) {

			// BST priority queue
			if ( myBstPQ.pqIsEmpty() )
				cout << "BST priority queue empty!"  << endl;
			else {
				cout << "BST queued strings are: ";
				myBstPQ.pqTraverse( display ); 
				cout << endl;
			}

			// LIST priority queue
			if ( myListPQ.empty() )
				cout << "LIST priority queue empty!"  << endl;
			else {
				cout << "LIST queued strings are: ";

				for ( itemIter = myListPQ.begin(); itemIter != myListPQ.end(); ++itemIter )
					cout << *itemIter << "  ";
				cout << endl;
			}

			// ARRAY priority queue
			if ( size == 0 )
				cout << "ARRAY priority queue empty!"  << endl;
			else {
				cout << "ARRAY queued strings are: ";

				for ( i = 0; i < size; ++i )
					cout << myArrayPQ[ i ] << "  ";
				cout << endl;
			}
		}
		else if ( sInput == "C" || sInput == "c" ) {

			// BST priority queue
			if ( myBstPQ.pqIsEmpty() )
				cout << "BST priority queue empty!"  << endl;
			else {
				cout << "Removed BST queued strings are: ";

				while ( !myBstPQ.pqIsEmpty() ) {
					myBstPQ.pqDelete( aString );
					cout << aString << "  ";
				}
				cout << endl;
			}

			// LIST priority queue
			if ( myListPQ.empty() )
				cout << "LIST priority queue empty!"  << endl;
			else {
				cout << "Removed LIST queued strings are: ";
				itemIter = myListPQ.begin();

				while ( !myListPQ.empty() ) {
					cout << *itemIter << "  ";
					itemIter = myListPQ.erase( itemIter );
				}
				cout << endl;
			}

			// ARRAY priority queue
			if ( size == 0 )
				cout << "ARRAY priority queue empty!"  << endl;
			else {
				cout << "Removed ARRAY queued strings are: ";

				for ( i = 0; i < size; ++i )
					cout << myArrayPQ[ i ] << "  ";
				cout << endl;

				size = 0;
			}
		}
		else  if ( sInput == "X" || sInput == "x" )
			return 0;	
		else 
			cout << "Unknown command!\r" << endl;
	}

	return 0;
}
