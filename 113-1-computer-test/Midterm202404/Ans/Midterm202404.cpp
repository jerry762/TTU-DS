// Midterm202404.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
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

int findMax(int A[], int size)
{
    if (size == 0)
        return 0;

    if (size == 1)
        return A[--size];

    return max(A[size], findMax(A, --size));
}

int findSum(int A[], int size)
{
    if (size == 0)
        return 0;

    if (size == 1)
        return A[--size];

    return A[size] + findSum(A, --size);
}

void doQ1()
{
    int aArray[SIZE];
    int size = inputNumber("Enter a number (0 to end): ", aArray);

    cout << endl
         << "\nInput numbers: ";

    for (int i = 0; i < size; i++)
        cout << aArray[i] << " ";

    cout << endl
         << "Maximum: " << findMax(aArray, size);
    cout << endl
         << "    Sum: " << findSum(aArray, size) << endl;

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

    for (int i = 0; i < MAX_TERMS; i++)
    {
        cout << "\ninput a's coefficient and exponent: ";
        cin >> coef >> expo;

        if (expo == 0 && coef == 0)
            break;

        aArrPoly.inputTerms(coef, expo);
        aLinkPoly.inputTerms(coef, expo);
    }

    cout << "\nArray Polynomial";
    cout << "\na(X) = ";
    aArrPoly.printArrayBasedPoly();

    bArrPoly.copyRecursively(aArrPoly);
    cout << "\nb(X) = ";
    bArrPoly.printArrayBasedPoly();

    cArrPoly.reverseCopy(aArrPoly);
    cout << "\nc(X) = ";
    cArrPoly.printArrayBasedPoly();
    cout << "\n";

    cout << "\nLink Polynomial";
    cout << "\na(X) = ";
    aLinkPoly.printLinkBasedPoly();

    bLinkPoly.copyRecursively(aLinkPoly);
    cout << "\nb(x) = ";
    bLinkPoly.printLinkBasedPoly();

    cLinkPoly.reverseCopy(aLinkPoly);
    cout << "\nc(X) = ";
    cLinkPoly.printLinkBasedPoly();
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

    cout << "Add 10 items to the bag: " << endl;

    for (int i = 0; i < 10; i++)
        bag.add(items[i]);
    displayBag(bag);

    bag.removeDuplicate();
    cout << "After removing duplicate => ";
    displayBag(bag);

    for (int i = 0; i < 5; i++)
    {
        bag.remove(otherItems[i]);
        cout << "After removing item " << otherItems[i] << " => ";
        displayBag(bag);
    }
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
    string otherItems[] = {"1A", "2B", "4D", "5E", "3C"};

    cout << "Add 10 items to the bag: " << endl;

    for (int i = 0; i < 10; i++)
        bagPtr->add(items[i]);
    displayBag(bagPtr);

    bagPtr->removeDuplicate();
    cout << "After removing duplicate => ";
    displayBag(bagPtr);

    for (int i = 0; i < 5; i++)
    {
        bagPtr->remove(otherItems[i]);
        cout << "After removing item " << otherItems[i] << " => ";
        displayBag(bagPtr);
    }
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
        cout << "1. Find maximum and sum recursively" << endl;
        cout << "2. Polynomial functions" << endl;
        cout << "3. Bag remove functions" << endl;
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
