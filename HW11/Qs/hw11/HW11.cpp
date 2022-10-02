// HW11.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "BinarySearchTree.h"

using namespace std;

void input(string sMessage, string &sInputString)
{
	do {
		cout << sMessage << endl;
		cin >> sInputString;
	} while ( cin.fail() );

	return;
}

void display(BinaryNode<string>& aNode)
{
	cout << aNode.getItem() << ":"<< aNode.getCount() << "  ";
}

int main()
{
 	string sInput, aString, aLine;
	BinarySearchTree<string> myBST;

	while (1) {
		input( "\nEnter command: A to Add, C to Count, R to Remove, or X to Exit", sInput );
			
		if ( sInput == "A"  || sInput == "a" ) {
			input( "Enter a string: ",  aString );
			myBST.add( aString );
			cout << endl << "The inorder traversal after Add is " << endl;
			myBST.inorderTraverse( display );
			cout << endl << "The levelorder traversal after Add is " << endl;
			myBST.levelorderTraverse( display );
		} 
		else if ( sInput == "R" || sInput == "r" ) {
			input( "Enter a string: ",  aString );
			try {
				myBST.remove( aString );

				if ( myBST.isEmpty() ) {
					cout << "The tree is now empty!" << endl;
				}
				else {
					cout << endl << "The inoder traversal after Remove is " << endl;
					myBST.inorderTraverse( display );
					cout << endl << "The levelorder traversal after Remove is " << endl;
					myBST.levelorderTraverse( display );
				}
			}
			catch (...)
			{
				cout << "No item deleted!"  << endl;
			}
		}
		else if ( sInput == "C"  || sInput == "c" ) {
			cin.ignore();
			cout << "Enter a line of text: ";
			getline( cin, aLine );

			string token, theDelimters = ".,!?;: ";
			int end = 0;
			int start = aLine.find_first_not_of( theDelimters, end );

			while ( start != string::npos ) {
				end = aLine.find_first_of( theDelimters, start );
				token = aLine.substr( start, end - start );
				myBST.add( token );
				start = aLine.find_first_not_of( theDelimters, end );
			}
			cout << endl << "The inoder traversal after Count is " << endl;
			myBST.inorderTraverse( display );
			cout << endl << "The levelorder traversal after Count is " << endl;
			myBST.levelorderTraverse( display );
		}
		else  if ( sInput == "X" || sInput == "x" )
			return 0;	
		else 
			cout << "Unknown command!\r" << endl;
	}

	return 0;
}


