// Midterm202411.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <string>
#include <cctype>
#include "polynomial1.h"
#include "BagInterface.h"
#include "ArrayBag.h"
#include "LinkedBag.h"

#define SIZE 10

using namespace std;

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

int inputNumber(string sMessage, int A[])
{
	int i = 0;

	for (; i < SIZE; i++)
	{
		cout << sMessage;
		cin >> A[i];

		if (A[i] == 0)
			break;
	}

	return i;
}

// ================ Question 1 Begins Here ==================

bool isIncreasing(int A[], int size)
{

	// add your code here

	return false;
}

bool isSymmetrical(int A[], int begin, int end)
{

	// add your code here

	return false;
}

void printOddNumbers(int A[], int size)
{

	// add your code here

	return;
}

int SumOddNumbers(int A[], int size)
{
	// add your code here

	return 0;
}

void doQ1()
{
	int n;

	cout << "How many integers? ";
	cin >> n;

	int *A = new int[n];

	cout << "Input integers: ";

	for (int i = 0; i < n; i++)
		cin >> A[i];

	cout << "The intrgers are ";

	if (!isIncreasing(A, n))
		cout << "NOT ";

	cout << "in increasing order\n";

	cout << "The intrgers are ";

	if (!isSymmetrical(A, 0, n - 1))
		cout << "NOT ";

	cout << "symmetrical\n";

	cout << "Odd numbers: ";
	printOddNumbers(A, n);

	cout << "\nSum of odd numbers: ";
	cout << SumOddNumbers(A, n);
	cout << endl;
}

// ================ Question 1 Ends Here ==================

// ================ Question 2 Begins Here =================
void doQ2()
{
	ArrayPolynomial aArrPoly, bArrPoly, cArrPoly;
	LinkedPolynomial aLinkPoly, bLinkPoly, cLinkPoly;

	int coef, expo;

	aArrPoly.clear();

	for (int i = 0; i < MAX_TERMS; i++)
	{
		cout << "\ninput A's coefficient and exponent: ";
		cin >> coef >> expo;

		if (expo == 0 && coef == 0)
			break;

		aArrPoly.inputTerms(coef, expo);
		aLinkPoly.inputTerms(coef, expo);
	}

	cout << endl;

	for (int i = 0; i < MAX_TERMS; i++)
	{
		cout << "\ninput B's coefficient and exponent: ";
		cin >> coef >> expo;

		if (expo == 0 && coef == 0)
			break;

		bArrPoly.inputTerms(coef, expo);
		bLinkPoly.inputTerms(coef, expo);
	}

	cout << "\n\n[Array Polynomial]\n";
	cout << "\na(X) = ";
	aArrPoly.printArrayBasedPoly();
	cout << "\nCoefficient of Max degree's term: " << aArrPoly.maxDgreeCoef();
	cout << "\nb(X) = ";
	bArrPoly.printArrayBasedPoly();
	cout << "\nCoefficient of Max degree's term: " << bArrPoly.maxDgreeCoef();

	if (aArrPoly.contain(bArrPoly))
		cout << "\na(X) contains b(X)\n";
	else
		cout << "\na(X) does NOT contain b(X)\n";

	aArrPoly.difference(bArrPoly);
	cout << "After difference a(X) = ";
	aArrPoly.printArrayBasedPoly();

	cout << "\n\n[Link Polynomial]\n";
	cout << "\na(X) = ";
	aLinkPoly.printLinkBasedPoly();
	cout << "\nCoefficient of Max degree's term: " << aLinkPoly.maxDgreeCoef();
	cout << "\nb(X) = ";
	bLinkPoly.printLinkBasedPoly();
	cout << "\nCoefficient of Max degree's term: " << bLinkPoly.maxDgreeCoef();

	if (aLinkPoly.contain(bLinkPoly))
		cout << "\na(X) contains b(X)\n";
	else
		cout << "\na(X) does NOT contain b(X)\n";

	aLinkPoly.difference(bLinkPoly);
	cout << "After difference a(X) = ";
	aLinkPoly.printLinkBasedPoly();

	cout << "\n";
}
// ================ Question 2 Ends Here ==================

// ================ Question 3 Begins Here ==================

void displayBag(ArrayBag<string> &bag)
{
	cout << "The bag contains " << bag.getCurrentSize() << " items: ";
	vector<string> bagItems = bag.toVector();
	int numberOfEntries = (int)bagItems.size();

	for (int i = 0; i < numberOfEntries; i++)
		cout << bagItems[i] << " ";

	cout << endl;
}

void bagTester(ArrayBag<string> &bag)
{
	string items[] = {"5E", "1A", "5E", "3C", "5E", "3C", "5E", "3C", "5E", "5E"};
	string otherItems[] = {"1A", "5E", "3C", "2B", "4D"};

	cout << "Add 10 items to the bag: ";

	for (int i = 0; i < 10; i++)
	{
		bag.add(items[i]);
		cout << items[i] << ' ';
	}
	cout << endl;
	displayBag(bag);
}

void displayBag(LinkedBag<string> *bagPtr)
{
	cout << "The bag contains " << bagPtr->getCurrentSize() << " items: ";
	vector<string> bagItems = bagPtr->toVector();

	int numberOfEntries = (int)bagItems.size();

	for (int i = 0; i < numberOfEntries; i++)
		cout << bagItems[i] << " ";

	cout << endl;
}

void bagTester(LinkedBag<string> *bagPtr)
{
	string items[] = {"5E", "1A", "5E", "3C", "5E", "3C", "5E", "3C", "5E", "5E"};

	cout << "Add 10 items to the bag: ";

	for (int i = 0; i < 10; i++)
	{
		bagPtr->add(items[i]);
		cout << items[i] << ' ';
	}
	cout << endl;
	displayBag(bagPtr);
}

void doQ3()
{
	char userChoice = ' ';

	while (toupper(userChoice) != 'X')
	{
		cout << "Enter \n 'A' to test the array-based implementation\n"
			 << " 'L' to test the link-based implementation or\n 'X' to exit: ";
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
			LinkedBag<string> *bagPtr = nullptr;
			bagPtr = new LinkedBag<string>();

			cout << "Testing the Link-Based Bag:" << endl;
			cout << "The initial bag is empty." << endl;
			bagTester(bagPtr);
			delete bagPtr;
			bagPtr = nullptr;
		}

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
		cout << "1. Recursive functions" << endl;
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
