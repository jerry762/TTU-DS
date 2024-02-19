// Midterm202311.cpp: 定義主控台應用程式的進入點。
//

#include <iostream>
#include <string>
#include <cctype>
#include "polynomial1.h"
#include "BagInterface.h"
#include "ArrayBag.h"
#include "LinkedBag.h"

using namespace std;

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

int inputNumber(string sMessage, int A[])
{
    int i;

    for (i = 0; i < SIZE; i++)
    {
        cout << sMessage;
        cin >> A[i];

        if (A[i] == 0)
            break;
    }

    return i;
}

// ================ Question 1 Begins Here ==================

int sumOdd(int A[], int size, int pos)
{
    if (pos == size)
        return 0;

    if (A[pos] % 2)
        cout << A[pos] << " ";

    return (A[pos] % 2) ? sumOdd(A, size, pos + 1) + A[pos] : sumOdd(A, size, pos + 1);
}

void doQ1()
{
    int aArray[SIZE];
    int size = inputNumber("Enter a number (0 to end): ", aArray);

    cout << "Input numbers are  ";

    for (int i = 0; i < size; i++)
        cout << aArray[i] << " ";

    cout << endl
         << "The odd numbers are ";
    cout << endl
         << "The sum of the odd numbers is " << sumOdd(aArray, size, 0) << endl
         << endl;

    return;
}

// ================ Question 1 Ends Here ==================

// ================ Question 2 Begins Here =================
void doQ2()
{
    ArrayPolynomial aArrPoly;
    LinkedPolynomial aLinkPol;

    int coef, expo;

    aArrPoly.clear();

    for (int i = 0; i < MAX_TERMS; i++)
    {
        cout << "\ninput a's coefficient and exponent: ";
        cin >> coef >> expo;

        if (expo == 0 && coef == 0)
            break;

        aArrPoly.inputArrayBasedTerms(coef, expo);
        aLinkPol.inputLinkBasedTerms(coef, expo);
    }

    for (int i = 0; i < 3; i++)
    {
        cout << "\n\ninput coefficient and exponent for update and swap: ";
        cin >> coef >> expo;

        cout << "\nBefor update: ";
        aArrPoly.printArrayBasedPoly();

        if (aArrPoly.isIncreasingOrder())
            cout << "\nIncreasing Order\n";
        else
            cout << "\nNot Increasing Order\n";

        aArrPoly.updateArrayBasedTerm(coef, expo); //
        cout << "\nAfter update: ";
        aArrPoly.printArrayBasedPoly();

        if (aArrPoly.isIncreasingOrder())
            cout << "\nIncreasing Order\n";
        else
            cout << "\nNot Increasing Order\n";

        // aArrPoly.swapArrayBasedTerms(expo, coef);   //
        cout << "\nAfter swap:   ";
        aArrPoly.printArrayBasedPoly();

        if (aArrPoly.isIncreasingOrder())
            cout << "\nIncreasing Order\n";
        else
            cout << "\nNot Increasing Order\n";

        cout << "\nBefor update: ";
        aLinkPol.printLinkBasedPoly();

        if (aLinkPol.isIncreasingOrder())
            cout << "\nIncreasing Order\n";
        else
            cout << "\nNot Increasing Order\n";

        aLinkPol.updateLinkBasedTerm(coef, expo); //
        cout << "\nAfter update: ";
        aLinkPol.printLinkBasedPoly();

        if (aLinkPol.isIncreasingOrder())
            cout << "\nIncreasing Order\n";
        else
            cout << "\nNot Increasing Order\n";

        // aLinkPol.swapLinkBasedTerms(expo, coef); //
        cout << "\nAfter swap:   ";
        aLinkPol.printLinkBasedPoly();

        if (aLinkPol.isIncreasingOrder())
            cout << "\nIncreasing Order\n";
        else
            cout << "\nNot Increasing Order\n";
    }

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
    {
        cout << bagItems[i] << " ";
    } // end for

    cout << endl;
} // end displayBag

void bagTester(ArrayBag<string> &bag)
{
    string items[] = {"5E", "1A", "5E", "3C", "5E", "3C", "5E", "3C", "2B", "5E"};
    string otherItems[] = {"5E", "3C", "4D"};

    cout << "After adding 10 items to the bag: " << endl;

    for (int i = 0; i < 10; i++)
        bag.add(items[i]);

    cout << "Before removing " << endl;
    displayBag(bag);
    bag.removeDuplicate();
    cout << endl
         << "After removing " << endl;
    displayBag(bag);
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
    string items[] = {"5E", "1A", "5E", "3C", "5E", "3C", "5E", "3C", "2B", "5E"};
    string otherItems[] = {"5E", "3C", "4D"};

    cout << "After adding 10 items to the bag: " << endl;

    for (int i = 0; i < 10; i++)
        bagPtr->add(items[i]);

    displayBag(bagPtr);
    cout << "Before removing " << endl;
    displayBag(bagPtr);
    bagPtr->removeDuplicate();
    cout << endl
         << "After removing " << endl;
    displayBag(bagPtr);
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
            bagTester(bag);
        }
        else
        {
            LinkedBag<string> *bagPtr = nullptr;
            bagPtr = new LinkedBag<string>();
            cout << "\nTesting the Link-Based Bag:" << endl;
            bagTester(bagPtr);
            delete bagPtr;
            bagPtr = nullptr;
        } // end if

        cout << "All done!\n"
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
        cout << "1. Print and Sum odd numbers recursively" << endl;
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
