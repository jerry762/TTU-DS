// HW4.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include <iostream>

using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

typedef struct
{
	int coef;
	int expo;
} polynomialTerm;

typedef struct linkedTerm
{
	int coef;
	int expo;
	linkedTerm *nextTermPtr;
} linkedPolynomialTerm;

void clear(polynomialTerm t[])
{
	for (int i = 0; i < MAX_TERMS; i++)
	{
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void clear(linkedPolynomialTerm *&polynomialTermPtr)
{
	linkedPolynomialTerm *tmpPtr;

	while (polynomialTermPtr != nullptr)
	{
		tmpPtr = polynomialTermPtr;
		polynomialTermPtr = polynomialTermPtr->nextTermPtr;
		delete tmpPtr;
	}
}

void inputTerms(polynomialTerm terms[], int coef, int expo) //* add your code here
{
	if (coef == 0)
		return;

	int size = 0;

	for (int i = 0; i < MAX_TERMS; i++)
	{
		if (terms[i].coef != 0)
		{
			size++;
		}
	}

	terms[size].expo = expo;
	terms[size].coef = coef;

	if (size == 0)
		return;

	for (int i = 0; i < size; i++)
	{
		if (expo > terms[i].expo)
		{
			for (int j = 0; j < size - i; j++)
				terms[size - j] = terms[size - 1 - j];

			terms[i].expo = expo;
			terms[i].coef = coef;

			break;
		}
		else if (expo == terms[i].expo)
		{
			terms[i].coef = coef;
			terms[size].expo = 0;
			terms[size].coef = 0;
			break;
		}
	}
}

void inputLinkTerms(linkedPolynomialTerm *&polyPtr, int coef, int expo) //* add your code here
{
	if (coef == 0)
		return;

	linkedPolynomialTerm *newNode = new linkedPolynomialTerm;

	newNode->expo = expo;
	newNode->coef = coef;
	newNode->nextTermPtr = nullptr;

	if (!polyPtr)
		polyPtr = newNode;
	else
	{
		linkedPolynomialTerm *currNode = polyPtr;
		linkedPolynomialTerm *prevNode = nullptr;

		while (currNode)
		{
			if (expo > currNode->expo)
			{
				if (currNode == polyPtr)
					polyPtr = newNode;
				else
					prevNode->nextTermPtr = newNode;

				newNode->nextTermPtr = currNode;
				break;
			}
			else if (expo == currNode->expo)
			{
				currNode->coef = coef;
				delete newNode;
				break;
			}
			prevNode = currNode;
			currNode = currNode->nextTermPtr;
		}
		if (!currNode)
			prevNode->nextTermPtr = newNode;
	}
}

void addArrayBasedPoly(polynomialTerm a[], polynomialTerm b[], polynomialTerm d[]) //* add your code here
{
	int pointA = 0;
	int pointB = 0;
	int pointD = 0;

	while (a[pointA].coef != 0 && b[pointB].coef != 0)
	{
		if (a[pointA].expo > b[pointB].expo)
		{
			d[pointD].expo = a[pointA].expo;
			d[pointD].coef = a[pointA].coef;
			pointA++;
			pointD++;
		}
		else if (a[pointA].expo < b[pointB].expo)
		{
			d[pointD].expo = b[pointB].expo;
			d[pointD].coef = b[pointB].coef;
			pointB++;
			pointD++;
		}
		else
		{
			if (a[pointA].coef + b[pointB].coef != 0)
			{
				d[pointD].expo = a[pointA].expo;
				d[pointD].coef = a[pointA].coef + b[pointB].coef;
				pointD++;
			}
			pointA++;
			pointB++;
		}
	}

	while (a[pointA].coef != 0)
	{
		d[pointD].expo = a[pointA].expo;
		d[pointD].coef = a[pointA].coef;

		pointD++;
		pointA++;
	}

	while (b[pointB].coef != 0)
	{
		d[pointD].expo = b[pointB].expo;
		d[pointD].coef = b[pointB].coef;

		pointB++;
		pointD++;
	}
}

linkedPolynomialTerm *addLinkBasedPoly(linkedPolynomialTerm *aPtr, linkedPolynomialTerm *bPtr) //* add your code here
{
	linkedPolynomialTerm *dPtr = nullptr;

	linkedPolynomialTerm *pointA = aPtr;
	linkedPolynomialTerm *pointB = bPtr;
	linkedPolynomialTerm *pointD = dPtr;

	while (pointA && pointB)
	{
		linkedPolynomialTerm *newNode = new linkedPolynomialTerm;

		newNode->nextTermPtr = nullptr;

		if (pointA->expo > pointB->expo)
		{
			newNode->expo = pointA->expo;
			newNode->coef = pointA->coef;
			pointA = pointA->nextTermPtr;
		}
		else if (pointA->expo < pointB->expo)
		{
			newNode->expo = pointB->expo;
			newNode->coef = pointB->coef;
			pointB = pointB->nextTermPtr;
		}
		else
		{
			if (pointA->coef + pointB->coef == 0)
			{
				pointA = pointA->nextTermPtr;
				pointB = pointB->nextTermPtr;
				delete newNode;
				continue;
			}
			newNode->expo = pointA->expo;
			newNode->coef = pointA->coef + pointB->coef;
			pointA = pointA->nextTermPtr;
			pointB = pointB->nextTermPtr;
		}

		if (!dPtr)
		{
			dPtr = newNode;
			pointD = dPtr;
		}
		else
		{
			pointD->nextTermPtr = newNode;
			pointD = pointD->nextTermPtr;
		}
	}

	while (pointA)
	{
		linkedPolynomialTerm *newNode = new linkedPolynomialTerm;

		newNode->expo = pointA->expo;
		newNode->coef = pointA->coef;
		newNode->nextTermPtr = nullptr;

		if (!dPtr)
		{
			dPtr = newNode;
			pointD = dPtr;
		}
		else
		{
			pointD->nextTermPtr = newNode;
			pointD = pointD->nextTermPtr;
		}
		pointA = pointA->nextTermPtr;
	}

	while (pointB)
	{
		linkedPolynomialTerm *newNode = new linkedPolynomialTerm;

		newNode->expo = pointB->expo;
		newNode->coef = pointB->coef;
		newNode->nextTermPtr = nullptr;

		if (!dPtr)
		{
			dPtr = newNode;
			pointD = dPtr;
		}
		else
		{
			pointD->nextTermPtr = newNode;
			pointD = pointD->nextTermPtr;
		}
		pointB = pointB->nextTermPtr;
	}

	return dPtr;
}

void printArrayBasedPoly(polynomialTerm terms[])
{
	if (terms[0].coef == 0)
		return;

	if (terms[0].expo == 0)
		cout << terms[0].coef;
	else
		cout << terms[0].coef << "X^" << terms[0].expo;

	for (int i = 1; i < MAX_TERMS; i++)
	{
		if (terms[i].coef == 0)
			return;

		if (terms[i].expo == 0)
			cout << " + " << terms[i].coef;
		else
			cout << " + " << terms[i].coef << "X^" << terms[i].expo;
	}
}

void printLinkBasedPoly(linkedPolynomialTerm *polyPtr)
{
	linkedPolynomialTerm *termPtr = polyPtr;

	if (termPtr == nullptr)
		return;

	if (termPtr->expo == 0)
		cout << termPtr->coef;
	else
		cout << termPtr->coef << "X^" << termPtr->expo;

	termPtr = termPtr->nextTermPtr;

	while (termPtr != nullptr)
	{
		if (termPtr->coef == 0)
			return;

		if (termPtr->expo == 0)
			cout << " + " << termPtr->coef;
		else
			cout << " + " << termPtr->coef << "X^" << termPtr->expo;

		termPtr = termPtr->nextTermPtr;
	}
}

int main()
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	linkedPolynomialTerm *aPtr, *bPtr, *dPtr;

	int coef, expo;

	aPtr = bPtr = dPtr = nullptr;

	while (1)
	{
		clear(a);
		clear(b);
		clear(d);
		clear(aPtr);
		clear(bPtr);
		clear(dPtr);

		for (int i = 0; i < MAX_TERMS; i++)
		{
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerms(a, coef, expo);
			inputLinkTerms(aPtr, coef, expo);
		}

		cout << "\n\na = ";
		printArrayBasedPoly(a);
		cout << "\na = ";
		printLinkBasedPoly(aPtr);
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++)
		{
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerms(b, coef, expo);
			inputLinkTerms(bPtr, coef, expo);
		}

		cout << "\n\nb = ";
		printArrayBasedPoly(b);

		cout << "\nb = ";
		printLinkBasedPoly(bPtr);

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		addArrayBasedPoly(a, b, d);
		cout << "\na + b = ";
		printArrayBasedPoly(d);

		dPtr = addLinkBasedPoly(aPtr, bPtr);
		cout << "\na + b = ";
		printLinkBasedPoly(dPtr);

		cout << "\n";
	}
	return 0;
}
