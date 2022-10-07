// HW13.cpp : 定義主控台應用程式的進入點。
//

#include <iostream>
#include <string>
#include "HashedDictionary.h" 

using namespace std;

void display(HashedEntry<string, string>& aRecord)
{
	cout << aRecord.getKey() << "-" << aRecord.getItem() <<"  ";
}

void input(const string& sMessage, string &sInputString)
{
	do {
		cout << sMessage << endl;
		cin >> sInputString;
	}  while ( cin.fail() );

	return;
}

int main()
{
 	string sInput, strName, strPhoneNo;
	HashedEntry<string, string>* itemPtr;
	HashedDictionary<string, string> myHashTable(11);

	while (1) {
		input( "\nEnter A to Add, R to Remove, Q to Query, D to Display, C to Clear, or X to Exit", sInput );
			
		if ( sInput == "A"  || sInput == "a" ) {
			input( "Enter name: ",  strName );
			itemPtr = myHashTable.getEntry( strName );

			if ( itemPtr != nullptr  )
					cout << "Duplicate name found." << endl;
			else {
				input( "Enter phone No: ", strPhoneNo );
				
				if ( myHashTable.add	( strName, strPhoneNo ) )
					cout << "Record added." << endl;
				else
					cout << "Record not added." << endl;
			}
		} 
		else if ( sInput == "R" || sInput == "r" ) {
			input( "Enter name: ",  strName );

			if ( myHashTable.remove( strName ) )
				cout << "Record removed." << endl;
			else
				cout << "Record not found." << endl;

		}
		else if ( sInput == "Q" || sInput == "q" ) {
			input( "Enter name: ",  strName );
			itemPtr = myHashTable.getEntry( strName );

			if ( itemPtr != nullptr ) {
				cout << "Retireved record is: ";
				display( *itemPtr );
				cout << endl;
			}
			else
			{
				cout << "Record not found." << endl;
			}
		}
		else if ( sInput == "D" || sInput == "d" ) {
			cout << "Records in Table are: " << endl;

			int i, len = myHashTable.getTableSize();

			for ( i = 0; i < len; i++ ) {
				cout << i << ": ";
				myHashTable.traverse(i, display );
				cout << endl;
			}
		}
		else if ( sInput == "C" || sInput == "c" ) {
			if (! myHashTable.isEmpty() ) {
				myHashTable.clear();
				cout << "All records cleared." << endl;
			}
			else
				cout << "No records." << endl;
		}
		else  if ( sInput == "X" || sInput == "x" )
			return 0;	
		else 
			cout << "Unknown command!\r" << endl;
	}

	return 0;
}
