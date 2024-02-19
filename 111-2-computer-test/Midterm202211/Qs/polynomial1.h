#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

class PolynomialTerm {
public:
	int coef;
	int expo;
};

class ArrayPolynomial {
public:
	PolynomialTerm terms[MAX_TERMS];

	void clear() /////
	{
		for (int i = 0; i < MAX_TERMS; i++) {
			terms[i].coef = 0;
			terms[i].expo = 0;
		}

		return;
	}

	void inputTerms(int coef, int expo)
	{
		// modify the following code and add your code here
		int i = 0;

		for (; terms[i].coef != 0 && i < MAX_TERMS; i++);

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

		for (int i = 1; i < MAX_TERMS; i++) {
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

	PolynomialTerm findArrayBasedPolyMaxTerm(int i)
	{
		PolynomialTerm term;
		term.coef = 0;
		term.expo = 0;


		// add yor code here


		return term;


	}

	void ArrayBasedRotateTerms() {


		// add yor code here


	}

	void copy(ArrayPolynomial& poly)
	{


		// add yor code here


	}

	void compactCopy(ArrayPolynomial& poly)
	{


		// add yor code here


	}
};

class LinkedPolynomialTerm {
public:
	int coef;
	int expo;
	LinkedPolynomialTerm* nextTermPtr;
};

class LinkedPolynomial {
public:
	LinkedPolynomialTerm* polynomialTermPtr = nullptr;

	void clear()
	{
		LinkedPolynomialTerm* tmpPtr;

		while (polynomialTermPtr != nullptr) {
			tmpPtr = polynomialTermPtr;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	void inputTerms(int coef, int expo)
	{
		LinkedPolynomialTerm* tmpPtr;

		tmpPtr = new LinkedPolynomialTerm;
		tmpPtr->coef = coef;
		tmpPtr->expo = expo;
		tmpPtr->nextTermPtr = polynomialTermPtr;

		polynomialTermPtr = tmpPtr;

		// add your code here 


		return;
	}

	void printLinkBasedPoly()
	{
		LinkedPolynomialTerm* termPtr = polynomialTermPtr;

		if (termPtr == nullptr)
			return;

		if (termPtr->expo == 0)
			cout << termPtr->coef;
		else
			cout << termPtr->coef << "X^" << termPtr->expo;

		termPtr = termPtr->nextTermPtr;

		while (termPtr != nullptr) {
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
		LinkedPolynomialTerm* termPtr = findLinkBasedPolyMaxTerm(polynomialTermPtr);

		if (termPtr == nullptr)
			return;

		if (termPtr->expo == 0)
			cout << termPtr->coef;
		else
			cout << termPtr->coef << "X^" << termPtr->expo;
	}

	LinkedPolynomialTerm* findLinkBasedPolyMaxTerm(LinkedPolynomialTerm* currPtr)
	{

		// add yor code here


		return nullptr;
	}

	void LinkBasedRotateTerms() {


		// add yor code here


	}
	
	void copy(LinkedPolynomial& poly)
	{


		// add yor code here


	}

	void compactCopy(LinkedPolynomial& poly)
	{


		// add yor code here


	}
};
