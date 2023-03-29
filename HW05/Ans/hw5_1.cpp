// HW5.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include <iostream>
#include <cmath>

using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

class PolynomialTerm
{
public:
	int coef;
	int expo;
};

class ArrayPolynomial
{
public:
	PolynomialTerm terms[MAX_TERMS];

	void clear()
	{
		for (int i = 0; i < MAX_TERMS; i++)
		{
			terms[i].coef = 0;
			terms[i].expo = 0;
		}

		return;
	}

	void inputTerms(int coef, int expo) //* add your code here
	{
		int size = 0;

		for (int i = 0; i < MAX_TERMS; i++)
		{
			if (terms[i].coef != 0)
				size++;
		}

		if (coef != 0)
		{
			terms[size].expo = expo;
			terms[size].coef = coef;
		}

		for (int i = 0; i < size; i++)
		{
			if (expo > terms[i].expo && coef != 0)
			{
				for (int j = size - 1; j >= i; j--)
					terms[j + 1] = terms[j];

				terms[i].expo = expo;
				terms[i].coef = coef;
				break;
			}
			else if (expo == terms[i].expo)
			{
				if (coef == 0)
				{
					for (int j = i; j < size; j++)
						terms[j] = terms[j + 1];
				}
				else
				{
					terms[i].coef = coef;
					terms[size].expo = 0;
					terms[size].coef = 0;
				}
				break;
			}
		}
	}

	void addArrayBasedPoly(ArrayPolynomial &a, ArrayPolynomial &b) //* add your code here
	{
		int pointA = 0;
		int pointB = 0;
		int pointD = 0;

		while (a.terms[pointA].coef != 0 && b.terms[pointB].coef != 0)
		{
			if (a.terms[pointA].expo > b.terms[pointB].expo)
			{
				terms[pointD].expo = a.terms[pointA].expo;
				terms[pointD].coef = a.terms[pointA].coef;
				pointA++;
				pointD++;
			}
			else if (a.terms[pointA].expo < b.terms[pointB].expo)
			{
				terms[pointD].expo = b.terms[pointB].expo;
				terms[pointD].coef = b.terms[pointB].coef;
				pointB++;
				pointD++;
			}
			else
			{
				if (a.terms[pointA].coef + b.terms[pointB].coef != 0)
				{
					terms[pointD].expo = a.terms[pointA].expo;
					terms[pointD].coef = a.terms[pointA].coef + b.terms[pointB].coef;
					pointD++;
				}
				pointA++;
				pointB++;
			}
		}

		while (a.terms[pointA].coef != 0)
		{
			terms[pointD].expo = a.terms[pointA].expo;
			terms[pointD].coef = a.terms[pointA].coef;
			pointD++;
			pointA++;
		}

		while (b.terms[pointB].coef != 0)
		{
			terms[pointD].expo = b.terms[pointB].expo;
			terms[pointD].coef = b.terms[pointB].coef;
			pointB++;
			pointD++;
		}
	}

	void reverseArrayBasedPoly() //* add your code here
	{
		int size = 0;

		for (int i = 0; i < MAX_TERMS; i++)
		{
			if (terms[i].coef != 0)
			{
				size++;
			}
		}

		for (int i = 0; i < size / 2; i++)
			swap(terms[i], terms[size - 1 - i]);
	}

	void printArrayBasedPoly()
	{
		if (terms[0].coef == 0)
			return;

		if (terms[0].expo == 0)
			std::cout << terms[0].coef;
		else
			std::cout << terms[0].coef << "X^" << terms[0].expo;

		for (int i = 1; i < MAX_TERMS; i++)
		{
			if (terms[i].coef == 0)
				return;

			if (terms[i].expo == 0)
				std::cout << " + " << terms[i].coef;
			else
				std::cout << " + " << terms[i].coef << "X^" << terms[i].expo;
		}

		return;
	}

	double compute(int x) //* add your code here
	{
		double sum = 0;
		int size = 0;

		for (int i = 0; i < MAX_TERMS; i++)
		{
			if (terms[i].coef != 0)
			{
				size++;
			}
		}

		for (int i = 0; i < size; i++)
		{
			if (terms[i].expo >= 0 || x != 0)
				sum += terms[i].coef * pow(x, terms[i].expo);
		}

		return sum;
	}
};

class LinkedPolynomialTerm
{
public:
	int coef;
	int expo;
	LinkedPolynomialTerm *nextTermPtr;
};

class LinkPolynomial
{
public:
	LinkedPolynomialTerm *polynomialTermPtr = nullptr;

	void clear()
	{
		LinkedPolynomialTerm *tmpPtr;

		while (polynomialTermPtr != nullptr)
		{
			tmpPtr = polynomialTermPtr;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	void inputLinkTerms(int coef, int expo) //* add your code here
	{
		LinkedPolynomialTerm *newNode = nullptr;

		if (coef != 0)
		{
			newNode = new LinkedPolynomialTerm;

			newNode->expo = expo;
			newNode->coef = coef;
			newNode->nextTermPtr = nullptr;
		}

		if (!polynomialTermPtr)
			polynomialTermPtr = newNode;
		else
		{
			LinkedPolynomialTerm *currNode = polynomialTermPtr;
			LinkedPolynomialTerm *prevNode = nullptr;

			while (currNode)
			{
				if (expo > currNode->expo && coef != 0)
				{
					if (currNode == polynomialTermPtr)
						polynomialTermPtr = newNode;
					else
						prevNode->nextTermPtr = newNode;

					newNode->nextTermPtr = currNode;
					break;
				}
				else if (expo == currNode->expo)
				{
					if (coef == 0)
					{
						if (currNode == polynomialTermPtr)
							polynomialTermPtr = currNode->nextTermPtr;
						else
							prevNode->nextTermPtr = currNode->nextTermPtr;
						delete currNode;
					}
					else
					{
						currNode->coef = coef;
						delete newNode;
					}
					break;
				}
				else if (!currNode->nextTermPtr)
				{
					currNode->nextTermPtr = newNode;
					break;
				}
				prevNode = currNode;
				currNode = currNode->nextTermPtr;
			}
		}
	}

	void addLinkBasedPoly(LinkPolynomial &aPol, LinkPolynomial &bPol) //* add your code here
	{
		LinkedPolynomialTerm *pointA = aPol.polynomialTermPtr;
		LinkedPolynomialTerm *pointB = bPol.polynomialTermPtr;
		LinkedPolynomialTerm *pointD = polynomialTermPtr;

		while (pointA && pointB)
		{
			LinkedPolynomialTerm *newNode = new LinkedPolynomialTerm;

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

			if (!polynomialTermPtr)
			{
				polynomialTermPtr = newNode;
				pointD = polynomialTermPtr;
			}
			else
			{
				pointD->nextTermPtr = newNode;
				pointD = pointD->nextTermPtr;
			}
		}

		while (pointA)
		{
			LinkedPolynomialTerm *newNode = new LinkedPolynomialTerm;

			newNode->expo = pointA->expo;
			newNode->coef = pointA->coef;
			newNode->nextTermPtr = nullptr;

			if (!polynomialTermPtr)
			{
				polynomialTermPtr = newNode;
				pointD = polynomialTermPtr;
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
			LinkedPolynomialTerm *newNode = new LinkedPolynomialTerm;

			newNode->expo = pointB->expo;
			newNode->coef = pointB->coef;
			newNode->nextTermPtr = nullptr;

			if (!polynomialTermPtr)
			{
				polynomialTermPtr = newNode;
				pointD = polynomialTermPtr;
			}
			else
			{
				pointD->nextTermPtr = newNode;
				pointD = pointD->nextTermPtr;
			}
			pointB = pointB->nextTermPtr;
		}
	}

	void reverseLinkBasedPoly() //* add your code here
	{
		if (!polynomialTermPtr || !polynomialTermPtr->nextTermPtr)
			return;

		LinkedPolynomialTerm *prevNode = nullptr;
		LinkedPolynomialTerm *currNode = polynomialTermPtr;
		LinkedPolynomialTerm *postNode = polynomialTermPtr->nextTermPtr;

		while (postNode)
		{
			currNode->nextTermPtr = prevNode;
			prevNode = currNode;
			currNode = postNode;
			postNode = postNode->nextTermPtr;
		}
		currNode->nextTermPtr = prevNode;

		polynomialTermPtr = currNode;
	}

	void printLinkBasedPoly()
	{
		LinkedPolynomialTerm *termPtr = polynomialTermPtr;

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

		return;
	}

	double compute(int x) //* add your code here
	{
		double sum = 0;

		LinkedPolynomialTerm *currNode = polynomialTermPtr;

		while (currNode)
		{
			if (currNode->expo >= 0 || x != 0)
				sum += currNode->coef * pow(x, currNode->expo);

			currNode = currNode->nextTermPtr;
		}

		return sum;
	}
};

int main()
{
	ArrayPolynomial a, b, d;
	LinkPolynomial aPol, bPol, dPol;

	int coef, expo, x;

	// aPtr = bPtr = dPtr = nullptr;

	while (1)
	{
		a.clear();
		b.clear();
		d.clear();
		// aPtr->clear(aPtr); bPtr->clear(bPtr); dPtr->clear(dPtr);

		for (int i = 0; i < MAX_TERMS; i++)
		{
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			a.inputTerms(coef, expo);
			aPol.inputLinkTerms(coef, expo);
		}

		cout << "\n\na = ";
		a.printArrayBasedPoly();
		cout << "\na = ";
		aPol.printLinkBasedPoly();
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++)
		{
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			b.inputTerms(coef, expo);
			bPol.inputLinkTerms(coef, expo);
		}

		cout << "\n\nb = ";
		b.printArrayBasedPoly();

		cout << "\nb = ";
		bPol.printLinkBasedPoly();

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		d.addArrayBasedPoly(a, b);
		cout << "\na + b = ";
		d.printArrayBasedPoly();

		dPol.addLinkBasedPoly(aPol, bPol);
		cout << "\na + b = ";
		dPol.printLinkBasedPoly();

		cout << "\n";

		d.reverseArrayBasedPoly();
		cout << "\nreversed d = ";
		d.printArrayBasedPoly();

		dPol.reverseLinkBasedPoly();
		cout << "\nreversed d = ";
		dPol.printLinkBasedPoly();

		cout << "\n";

		cout << "\ninput X: ";
		cin >> x;

		cout << "\nd = ";
		cout << d.compute(x);

		cout << "\nd = ";
		cout << dPol.compute(x);

		cout << "\n";

		aPol.clear();
		bPol.clear();
		dPol.clear();
	}

	return 0;
}
