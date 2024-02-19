#include <iostream>
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

	void clear() /////
	{
		for (int i = 0; i < MAX_TERMS; i++)
		{
			terms[i].coef = 0;
			terms[i].expo = 0;
		}

		return;
	}

	void inputTerms(int coef, int expo)
	{
		// modify the following code and add your code here
		int i = 0;

		for (; terms[i].coef != 0 && i < MAX_TERMS; i++)
			;

		terms[i].coef = coef;
		terms[i].expo = expo;

		return;
	}

	void printArrayBasedPoly()
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

		return;
	}

	void showArrayBasedPolyMaxTerm()
	{
		PolynomialTerm term = findArrayBasedPolyMaxTerm(0);

		if (term.coef == 0)
			return;

		if (term.expo == 0)
			cout << term.coef;
		else
			cout << term.coef << "X^" << term.expo;
	}

	PolynomialTerm findArrayBasedPolyMaxTerm(int i) //* add yor code here
	{
		if (terms[i + 1].expo == 0)
			return terms[i];

		PolynomialTerm returnTerm = findArrayBasedPolyMaxTerm(i + 1);

		if (returnTerm.expo < terms[i].expo)
			return terms[i];
		else if (returnTerm.expo == terms[i].expo)
		{
			if (returnTerm.coef < terms[i].coef)
				return terms[i];
		}

		return returnTerm;
	}

	void ArrayBasedRotateTerms() //* add yor code here
	{

		int size = 0;

		for (size_t i = 0; i < MAX_TERMS; i++)
		{
			if (terms[i].expo != 0)
				size++;
		}

		if (size > 1)
		{
			PolynomialTerm tempTerm = terms[0];

			for (int i = 0; i < size - 1; i++)
				terms[i] = terms[i + 1];

			terms[size - 1] = tempTerm;
		}
	}

	void copy(ArrayPolynomial &poly) //* add yor code here
	{
		int size = 0;

		for (size_t i = 0; i < MAX_TERMS; i++)
		{
			if (poly.terms[i].expo != 0)
				size++;
		}

		for (size_t i = 0; i < size; i++)
		{
			terms[i].expo = poly.terms[i].expo;
			terms[i].coef = poly.terms[i].coef;
		}
	}

	void compactCopy(ArrayPolynomial &poly) //* add yor code here
	{
		int size = 0;

		for (size_t i = 0; i < MAX_TERMS; i++)
		{
			terms[i].expo = 0;
			terms[i].coef = 0;

			if (poly.terms[i].expo != 0)
				size++;
		}

		int sizeC = 0;

		for (size_t i = 0; i < size; i++)
		{
			if (poly.terms[i].coef == 0)
				continue;

			PolynomialTerm tempTerm = poly.terms[i];

			for (size_t j = i + 1; j < size; j++)
			{
				if (tempTerm.expo == poly.terms[j].expo)
				{
					tempTerm.coef += poly.terms[j].coef;
					poly.terms[j].coef = 0;
				}
			}

			if (tempTerm.coef != 0)
				terms[sizeC++] = tempTerm;
		}
	}
};

class LinkedPolynomialTerm
{
public:
	int coef;
	int expo;
	LinkedPolynomialTerm *nextTermPtr;
};

class LinkedPolynomial
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

	void inputTerms(int coef, int expo)
	{
		LinkedPolynomialTerm *tmpPtr;

		tmpPtr = new LinkedPolynomialTerm;
		tmpPtr->coef = coef;
		tmpPtr->expo = expo;
		tmpPtr->nextTermPtr = polynomialTermPtr;

		polynomialTermPtr = tmpPtr;

		return;
	}

	void printLinkBasedPoly()
	{
		LinkedPolynomialTerm *termPtr = polynomialTermPtr;

		if (termPtr == nullptr)
			return;

		if (termPtr->coef == 0)
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

	void showLinkBasedPolyMaxTerm()
	{
		LinkedPolynomialTerm *termPtr = findLinkBasedPolyMaxTerm(polynomialTermPtr);

		if (termPtr == nullptr)
			return;

		if (termPtr->expo == 0)
			cout << termPtr->coef;
		else
			cout << termPtr->coef << "X^" << termPtr->expo;
	}

	LinkedPolynomialTerm *findLinkBasedPolyMaxTerm(LinkedPolynomialTerm *currPtr) //* add yor code here
	{
		if (!currPtr)
			return nullptr;

		if (!currPtr->nextTermPtr)
			return currPtr;

		LinkedPolynomialTerm *returnTerm = findLinkBasedPolyMaxTerm(currPtr->nextTermPtr);

		if (returnTerm->expo < currPtr->expo)
			return currPtr;
		else if (returnTerm->expo == currPtr->expo)
		{
			if (returnTerm->coef < currPtr->coef)
				return currPtr;
		}

		return returnTerm;
	}

	void LinkBasedRotateTerms() //* add yor code here
	{

		if (polynomialTermPtr && polynomialTermPtr->nextTermPtr)
		{
			LinkedPolynomialTerm *tempPtr = polynomialTermPtr;
			LinkedPolynomialTerm *currPtr = polynomialTermPtr->nextTermPtr;

			polynomialTermPtr = currPtr;

			while (currPtr->nextTermPtr)
				currPtr = currPtr->nextTermPtr;

			currPtr->nextTermPtr = tempPtr;
			tempPtr->nextTermPtr = nullptr;
		}
	}

	void copy(LinkedPolynomial &poly) //* add yor code here
	{
		clear();

		if (poly.polynomialTermPtr)
		{
			polynomialTermPtr = new LinkedPolynomialTerm;

			polynomialTermPtr->expo = poly.polynomialTermPtr->expo;
			polynomialTermPtr->coef = poly.polynomialTermPtr->coef;
			polynomialTermPtr->nextTermPtr = nullptr;

			LinkedPolynomialTerm *currPtr = poly.polynomialTermPtr->nextTermPtr;
			LinkedPolynomialTerm *currNewPolyPtr = polynomialTermPtr;

			while (currPtr)
			{
				LinkedPolynomialTerm *newPtr = new LinkedPolynomialTerm;

				newPtr->expo = currPtr->expo;
				newPtr->coef = currPtr->coef;
				newPtr->nextTermPtr = nullptr;

				currNewPolyPtr->nextTermPtr = newPtr;

				currNewPolyPtr = currNewPolyPtr->nextTermPtr;
				currPtr = currPtr->nextTermPtr;
			}
		}
	}

	void compactCopy(LinkedPolynomial &poly) //* add yor code here
	{
		clear();

		while (poly.polynomialTermPtr)
		{
			LinkedPolynomialTerm *tempPtr = poly.polynomialTermPtr;

			if (tempPtr->coef != 0)
			{
				LinkedPolynomialTerm *currPtr = tempPtr->nextTermPtr;

				while (currPtr)
				{
					if (tempPtr->expo == currPtr->expo)
					{
						tempPtr->coef += currPtr->coef;
						currPtr->coef = 0;
					}

					currPtr = currPtr->nextTermPtr;
				}

				if (tempPtr->coef != 0)
				{
					LinkedPolynomialTerm *newPtr = new LinkedPolynomialTerm;

					newPtr->expo = tempPtr->expo;
					newPtr->coef = tempPtr->coef;
					newPtr->nextTermPtr = nullptr;

					if (!polynomialTermPtr)
						polynomialTermPtr = newPtr;
					else
					{
						currPtr = polynomialTermPtr;

						while (currPtr->nextTermPtr)
							currPtr = currPtr->nextTermPtr;

						currPtr->nextTermPtr = newPtr;
					}
				}
			}
			poly.polynomialTermPtr = tempPtr->nextTermPtr;
			delete tempPtr;
		}
	}
};
