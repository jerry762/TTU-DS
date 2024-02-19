// Midterm202304.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include <iostream>
#include <string>
#include <cctype>
#include "polynomial1.h"
#include "BagInterface.h"
#include "ArrayBag.h"
#include "LinkedBag.h"

#define SIZE 5

void input(string sMessage, string& sInputString)
{
	cout << sMessage << endl;
	cin >> sInputString;
	return;
}

void output(string sMessage)
{
	if (sMessage.length() > 0)
		cout << endl << sMessage << endl;

	return;
}

int inputNumber(string sMessage, int A[])
{
	int i;

	for (i = 0; i < SIZE; i++) {
		cout << sMessage;
		cin >> A[i];

		if (A[i] == 0)
			break;
	}

	return i;
}

// ================ Question 1 Begins Here ==================

void insertR(int A[], int entry, int index)
{

}

void doQ1()
{
	int aArray[SIZE];
	int number, size = 0;

	for (int i = 0; i < SIZE; i++)
		aArray[i] = 0;

	while (true) {
		cout << endl << "Enter a number (0 to end): ";
		cin >> number;

		if (number == 0) return;

		insertR(aArray, number, 0);

		cout << endl << "Numbers in Aarry: ";

		for (int i = 0; aArray[i] != 0 && i < SIZE; i++)
			cout << aArray[i] << " ";
		cout << endl;
	}
}

// ================ Question 1 Ends Here ==================

// ================ Question 2 Begins Here =================
void doQ2()
{
	ArrayPolynomial aArrPoly;
	LinkedPolynomial aLinkPol;

	int coef, expo;

	aArrPoly.clear();

	for (int i = 0; i < MAX_TERMS; i++) {
		cout << "\ninput a's coefficient and exponent: ";
		cin >> coef >> expo;

		if (expo == 0 && coef == 0)
			break;

		aArrPoly.inputArrayBasedTerms(coef, expo);
		aLinkPol.inputLinkBasedTerms(coef, expo);
	}

	cout << "\n\nArray Based Polynomial";

	cout << "\n\na = ";
	aArrPoly.printArrayBasedPoly();
	cout << "\nAfter reversal: \na = ";
	aArrPoly.arrayBasedReverse();
	aArrPoly.printArrayBasedPoly();
	cout << "\ncomputeI(1) = " << aArrPoly.computeI(1);
	cout << "\ncomputeR(1) = " << aArrPoly.computeR(1, 0);

	aArrPoly.arrayBasedDifferentiation();
	cout << "\n\na' = ";
	aArrPoly.printArrayBasedPoly();
	cout << "\nAfter reversal: \na' = ";
	aArrPoly.arrayBasedReverse();
	aArrPoly.printArrayBasedPoly();
	cout << "\ncomputeI(2) = " << aArrPoly.computeI(2);
	cout << "\ncomputeR(2) = " << aArrPoly.computeR(2);

	aArrPoly.arrayBasedDifferentiation();
	cout << "\n\na'' = ";
	aArrPoly.printArrayBasedPoly();
	cout << "\nAfter reversal: \na'' = ";
	aArrPoly.arrayBasedReverse();
	aArrPoly.printArrayBasedPoly();
	cout << "\ncomputeI(10) = " << aArrPoly.computeI(10);
	cout << "\ncomputeR(10) = " << aArrPoly.computeR(10);

	cout << "\n\nLink Based Polynomial";

	cout << "\n\na = ";
	aLinkPol.printLinkBasedPoly();
	cout << "\nAfter reversal: \na = ";
	aLinkPol.linkBasedReverse();
	aLinkPol.printLinkBasedPoly();
	cout << "\ncomputeI(1) = " << aLinkPol.computeI(1);
	cout << "\ncomputeR(1) = " << aLinkPol.computeR(1);

	aLinkPol.linkBasedDifferentiation();
	cout << "\n\na' = ";
	aLinkPol.printLinkBasedPoly();
	cout << "\nAfter reversal: \na' = ";
	aLinkPol.linkBasedReverse();
	aLinkPol.printLinkBasedPoly();
	cout << "\ncomputeI(2) = " << aLinkPol.computeI(2);
	cout << "\ncomputeR(2) = " << aLinkPol.computeR(2);

	aLinkPol.linkBasedDifferentiation();
	cout << "\n\na'' = ";
	aLinkPol.printLinkBasedPoly();
	cout << "\nAfter reversal: \na'' = ";
	aLinkPol.linkBasedReverse();
	aLinkPol.printLinkBasedPoly();
	cout << "\ncomputeI(10) = " << aLinkPol.computeI(10);
	cout << "\ncomputeR(10) = " << aLinkPol.computeR(10);

	cout << "\n";
}
// ================ Question 2 Ends Here ==================

// ================ Question 3 Begins Here ==================

void displayBag(ArrayBag<string>& bag)
{
	cout << "The bag contains " << bag.getCurrentSize() << " items: ";
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
	string items[] = { "5E", "1A", "5E", "3C", "5E", "3C", "5E", "3C", "2B", "5E" };
	string otherItems[] = { "5E", "3C", "4D" };


	cout << "After adding 10 items to the bag: " << endl;

	for (int i = 0; i < 10; i++)
		bag.add(items[i]);

	displayBag(bag);

	ArrayBag<string> anotherBag;

	cout << "After removing ";
	for (int i = 0; i < 3; i++) {
		anotherBag.add(otherItems[i]);
		cout << otherItems[i] << " ";
	}
	cout << endl;

	bag.remove(anotherBag);
	displayBag(bag);
} // end bagTester

void displayBag(LinkedBag<string>* bagPtr)
{
	cout << "The bag contains " << bagPtr->getCurrentSize() << " items: ";
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
	string items[] = { "5E", "1A", "5E", "3C", "5E", "3C", "5E", "3C", "2B", "5E" };
	string otherItems[] = { "5E", "3C", "4D" };

	cout << "After adding 10 items to the bag: " << endl;

	for (int i = 0; i < 10; i++)
		bagPtr->add(items[i]);

	displayBag(bagPtr);

	LinkedBag<string>* anotherBagPtr = nullptr;
	anotherBagPtr = new LinkedBag<string>();

	cout << "After removing ";

	for (int i = 0; i < 3; i++) {
		anotherBagPtr->add(otherItems[i]);
		cout << otherItems[i] << " ";
	}
	cout << endl;

	bagPtr->remove(anotherBagPtr);
	displayBag(bagPtr);
}  // end bagTester

void doQ3()
{
	char userChoice = ' ';

	while (toupper(userChoice) != 'X') {
		cout << "Enter 'A' to test the array-based implementation\n"
			<< " 'L' to test the link-based implementation or 'X' to exit: ";
		cin >> userChoice;

		if (toupper(userChoice) == 'A')
		{
			ArrayBag<string> bag;
			cout << "\nTesting the Array-Based Bag:" << endl;
			bagTester(bag);
		}
		else
		{
			LinkedBag<string>* bagPtr = nullptr;
			bagPtr = new LinkedBag<string>();
			cout << "\nTesting the Link-Based Bag:" << endl;
			bagTester(bagPtr);
			delete bagPtr;
			bagPtr = nullptr;
		}  // end if

		cout << "All done!\n" << endl;
	}
}

// ================ Question 3 Ends Here ==================

// ============== Main Program Begins Here ================

int main()
{
	string sCommand, sName, sNum, sMessage;

	while (1) {
		cout << endl;
		cout << "1. Insert recursively" << endl;
		cout << "2. Polynomial functions" << endl;
		cout << "3. Bag remove functions" << endl;
		input("Enter Question Number( 1 ~ 3 ) or 0 to Exit:", sNum);

		switch (sNum[0] - '0') {
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
