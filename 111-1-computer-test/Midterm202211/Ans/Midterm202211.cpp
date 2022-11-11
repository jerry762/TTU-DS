// Midterm201911.cpp : 定義主控台應用程式的進入點。
//

#include <iostream>
#include <string>
#include <cctype>
#include "polynomial1.h"
#include "BagInterface.h"
#include "ArrayBag.h"
#include "LinkedBag.h"

#define SIZE 10

void input(string sMessage, string &sInputString)
{
	cout << sMessage << endl;
	cin >> sInputString;
	return;
}

void output(string sMessage)
{
	if (sMessage.length() > 0)
		cout << endl
			 << sMessage << endl;

	return;
}

// ================ Question 1 Begins Here ==================

bool isPalindrome(string aString)
{
	size_t length = aString.size();

	if (length == 0 || length == 1)
		return true;

	return (aString.at(0) == aString.at(length - 1)) ? isPalindrome(aString.substr(1, length - 2)) : false;
}

void doQ1()
{
	string aStr;
	cout << endl
		 << "Input a string: ";
	cin >> aStr;

	cout << endl
		 << aStr + " is " << (isPalindrome(aStr) ? "" : "not ") << "a palindrome." << endl;

	return;
}

// ================ Question 1 Ends Here ==================

// ================ Question 2 Begins Here =================
void doQ2()
{
	ArrayPolynomial aArrPoly, bArrPoly, cArrPoly;
	LinkedPolynomial aLinkPoly, bLinkPoly, cLinkPoly;

	int coef, expo;

	aArrPoly.clear();
	bArrPoly.clear(), cArrPoly.clear();
	;

	for (int i = 0; i < MAX_TERMS; i++)
	{
		cout << "\n\ninput a's coefficient and exponent: ";
		cin >> coef >> expo;

		if (expo == 0 && coef == 0)
			break;

		aArrPoly.inputTerms(coef, expo);

		cout << "\n\nArrayPolynomial a = ";
		aArrPoly.printArrayBasedPoly();

		aArrPoly.ArrayBasedRotateTerms();
		cout << "\nAfter rotation=>a = ";
		aArrPoly.printArrayBasedPoly();

		cout << "\nMaximum term = ";
		aArrPoly.showArrayBasedPolyMaxTerm();

		bArrPoly.copy(aArrPoly);
		cout << "\n\nArrayPolynomial b = ";
		bArrPoly.printArrayBasedPoly();

		bArrPoly.ArrayBasedRotateTerms();
		cout << "\nAfter rotation=>b = ";
		bArrPoly.printArrayBasedPoly();

		cout << "\nMaximum term = ";
		bArrPoly.showArrayBasedPolyMaxTerm();

		cArrPoly.compactCopy(bArrPoly);
		cout << "\n\nArrayPolynomial c = ";
		cArrPoly.printArrayBasedPoly();

		cArrPoly.ArrayBasedRotateTerms();
		cout << "\nAfter rotation=>c = ";
		cArrPoly.printArrayBasedPoly();

		cout << "\nMaximum term = ";
		cArrPoly.showArrayBasedPolyMaxTerm();

		aLinkPoly.inputTerms(coef, expo);

		cout << "\n\nLinkedPolynomial a = ";
		aLinkPoly.printLinkBasedPoly();

		aLinkPoly.LinkBasedRotateTerms();
		cout << "\nAfter rotation=> a = ";
		aLinkPoly.printLinkBasedPoly();

		cout << "\nMaximum term = ";
		aLinkPoly.showLinkBasedPolyMaxTerm();

		bLinkPoly.copy(aLinkPoly);
		cout << "\n\nLinkedPolynomial b = ";
		bLinkPoly.printLinkBasedPoly();

		bLinkPoly.LinkBasedRotateTerms();
		cout << "\nAfter rotation=> b = ";
		bLinkPoly.printLinkBasedPoly();

		cout << "\nMaximum term = ";
		bLinkPoly.showLinkBasedPolyMaxTerm();

		cLinkPoly.compactCopy(bLinkPoly);
		cout << "\n\nLinkedPolynomial c = ";
		cLinkPoly.printLinkBasedPoly();

		cLinkPoly.LinkBasedRotateTerms();
		cout << "\nAfter rotation=> c = ";
		cLinkPoly.printLinkBasedPoly();

		cout << "\nMaximum term = ";
		cLinkPoly.showLinkBasedPolyMaxTerm();
	}
}
// ================ Question 2 Ends Here ==================

// ================ Question 3 Begins Here ==================

void displayBag(ArrayBag<string> &bag)
{
	cout << "The bag contains " << bag.getCurrentSize() << " items: ";
	vector<string> bagItems = bag.toVector();
	int numberOfEntries = (int)bagItems.size();

	for (int i = 0; i < numberOfEntries; i++)
	{
		cout << bagItems[i] << " ";
	} // end for

	cout << endl;
} // end displayBag

void bagTester(ArrayBag<string> &bag)
{
	string items[] = {"Banana", "Cherry", "Apple", "Cherry", "Banana", "Cherry"};
	string otherItems[] = {"Banana", "Cherry", "Apple", "Pear"};

	cout << "Add 6 items to the bag: " << endl;

	for (int i = 0; i < 6; i++)
		bag.add(items[i]);

	displayBag(bag);

	for (int i = 0; i < 4; i++)
	{
		bag.addOrRemove(otherItems[i]);
		cout << "Add or remove items from the bag: " << endl;
		displayBag(bag);
	}

	for (int i = 0; i < 4; i++)
	{
		bag.addOrRemove(otherItems[i]);
		cout << "Add or remove items from the bag: " << endl;
		displayBag(bag);
	}
} // end bagTester

void displayBag(LinkedBag<string> *bagPtr)
{
	cout << "The bag contains " << bagPtr->getCurrentSize() << " items: ";
	vector<string> bagItems = bagPtr->toVector();

	int numberOfEntries = (int)bagItems.size();

	for (int i = 0; i < numberOfEntries; i++)
	{
		cout << bagItems[i] << " ";
	} // end for

	cout << endl;
} // end displayBag

void bagTester(LinkedBag<string> *bagPtr)
{
	string items[] = {"Banana", "Cherry", "Apple", "Cherry", "Banana", "Cherry"};
	string otherItems[] = {"Banana", "Cherry", "Apple", "Pear"};

	cout << "Add 6 items to the bag: " << endl;

	for (int i = 0; i < 6; i++)
		bagPtr->add(items[i]);

	displayBag(bagPtr);

	for (int i = 0; i < 4; i++)
	{
		bagPtr->addOrRemove(otherItems[i]);
		cout << "Add or remove items from the bag: " << endl;
		displayBag(bagPtr);
	}

	for (int i = 0; i < 4; i++)
	{
		bagPtr->addOrRemove(otherItems[i]);
		cout << "Add or remove items from the bag: " << endl;
		displayBag(bagPtr);
	}
} // end bagTester

void doQ3()
{
	char userChoice = ' ';

	while (toupper(userChoice) != 'X')
	{
		cout << "Enter 'A' to test the array-based implementation\n"
			 << " 'L' to test the link-based implementation or 'X' to exit: ";
		cin >> userChoice;

		if (toupper(userChoice) == 'A')
		{
			ArrayBag<string> bag;
			cout << "\nTesting the Array-Based Bag:" << endl;
			cout << "The initial bag is empty." << endl;
			bagTester(bag);
		}
		else
		{
			LinkedBag<string> *bagPtr = nullptr;
			bagPtr = new LinkedBag<string>();
			cout << "\nTesting the Link-Based Bag:" << endl;
			cout << "The initial bag is empty." << endl;
			bagTester(bagPtr);
			delete bagPtr;
			bagPtr = nullptr;
		} // end if

		cout << "All done!\n\n"
			 << endl;
	}
}

// ================ Question 3 Ends Here ==================

// ============== Main Program Begins Here ================

int main()
{
	string sCommand, sName, sNum, sMessage;

	while (1)
	{
		cout << endl;
		cout << "1. Recursive function" << endl;
		cout << "2. Polynomial functions" << endl;
		cout << "3. Bag functions" << endl;
		input("Enter Question Number( 1 ~ 3 ) or 0 to Exit:", sNum);

		switch (sNum[0] - '0')
		{
		case 0:
			return 0;
		case 1:
			doQ1();
			break;
		case 2:
			doQ2();
			break;
		case 3:
			doQ3();
			break;
		}
	}
}

// ============== Main Program Ends Here ================
