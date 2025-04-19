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

	ArrayPolynomial()
	{
		for (int i = 0; i < MAX_TERMS; i++)
			terms[i].coef = terms[i].expo = 0;
	}

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

	int maxDgreeCoef()
	{

		// add yor code here
		if (terms[0].coef == 0) {
			return -1;
		}

		//find max exponent
		int maxExpo = -1;
		for (int i = 0; i < MAX_TERMS; i++) {
			if (terms[i].coef == 0)
				break;
			maxExpo = max(maxExpo, terms[i].expo);
		}

		//sum max exponent
		int sum = 0;
		for (int i = 0; i < MAX_TERMS; i++) {
			if (terms[i].coef == 0)
				break;

			if (terms[i].expo == maxExpo) {
				sum += terms[i].coef;
			}
		}
		return sum;
	}

	bool contain(ArrayPolynomial& poly)
	{

		// add your code here


		bool used[MAX_TERMS] = {};

		//iterate child
		for (int i = 0; i < MAX_TERMS; i++) {
			if (poly.terms[i].coef == 0) {
				break;
			}

			//search the term in the parent
			bool found = false;
			for (int j = 0; j < MAX_TERMS; j++) {
				if (terms[j].coef == 0) {
					break;
				}
				if (terms[j].coef == poly.terms[i].coef && terms[j].expo == poly.terms[i].expo && !used[j]) {
					found = true;
					used[j] = true;
					break;
				}
			}

			if (!found) {
				return false;
			}
		}
		
		return true;

	}

	void difference(ArrayPolynomial& poly)
	{

		// add your code here

		int newIndex = 0;
		//iterate parent
		for (int i = 0; i < MAX_TERMS; i++) {
			if (terms[i].coef == 0) {
				break;
			}

			//search the term in the child
			bool found = false;
			for (int j = 0; j < MAX_TERMS; j++) {
				if (poly.terms[j].coef == 0) {
					break;
				}
				if (poly.terms[j].coef == terms[i].coef && poly.terms[j].expo == terms[i].expo) {
					found = true;
					break;
				}
			}

			// if not found, preserve the term
			if (!found) {
				terms[newIndex].coef = terms[i].coef;
				terms[newIndex].expo = terms[i].expo;
				newIndex++;
			}
		}
		terms[newIndex].coef = 0;
		terms[newIndex].expo = 0;
	}
};

class LinkedPolynomialTerm {
public:
	int coef;
	int expo;
	LinkedPolynomialTerm *nextTermPtr;
};

class LinkedPolynomial {
public:
	LinkedPolynomialTerm *polynomialTermPtr = nullptr;

	void clear()
	{
		LinkedPolynomialTerm *tmpPtr;

		while (polynomialTermPtr != nullptr) {
			tmpPtr = polynomialTermPtr;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	void inputTerms(int coef, int expo)
	{
		// modify the following code and add your code here

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

	int maxDgreeCoef()
	{

		// add yor code here
		if (polynomialTermPtr == nullptr) {
			return -1;
		}

		int maxExpo = -1;

		//find max exponent
		LinkedPolynomialTerm* cur = polynomialTermPtr;
		while (cur != nullptr) {
			if (cur->coef == 0)
				break;

			maxExpo = max(maxExpo, cur->expo);

			cur = cur->nextTermPtr;
		}

		int sum = 0;

		//sum max exponent
		cur = polynomialTermPtr;
		while (cur != nullptr) {
			if (cur->coef == 0)
				break;

			if (cur->expo == maxExpo) {
				sum += cur->coef;
			}

			cur = cur->nextTermPtr;
		}
		return sum;

	}

	bool contain(LinkedPolynomial& poly)
	{

		// add your code here

		//iterate child
		bool used[MAX_TERMS] = {};
		LinkedPolynomialTerm* cur = poly.polynomialTermPtr;
		while (cur != nullptr) {
			if (cur->coef == 0)
				break;

			//search the term in the parent
			bool found = false;
			LinkedPolynomialTerm* cur2 = polynomialTermPtr;
			int j = 0;
			while(cur2 != nullptr) {
				if (cur2->coef == 0) {
					break;
				}
				if (cur2->coef == cur->coef && cur2->expo == cur->expo && !used[j]) {
					found = true;
					used[j] = true;
					break;
				}
				cur2 = cur2->nextTermPtr;
				j++;
			}

			if (!found) {
				return false;
			}
			cur = cur->nextTermPtr;
		}

		return true;

	}

	void difference(LinkedPolynomial& poly)
	{

		// add your code here

		//new LinkedList
		LinkedPolynomialTerm* newList = nullptr;

		//iterate parent
		LinkedPolynomialTerm* cur = polynomialTermPtr;
		while (cur != nullptr) {
			if (cur->coef == 0) {
				break;
			}

			//search the term in the child
			bool found = false;
			LinkedPolynomialTerm* cur2 = poly.polynomialTermPtr;
			while (cur2 != nullptr) {
				if (cur2->coef == 0) {
					break;
				}
				if (cur2->coef == cur->coef && cur2->expo == cur->expo) {
					found = true;
					break;
				}
				cur2 = cur2->nextTermPtr;
			}

			// if not found, preserve the term
			if (!found) {
				LinkedPolynomialTerm* newNode = new LinkedPolynomialTerm;
				newNode->coef = cur->coef;
				newNode->expo = cur->expo;
				newNode->nextTermPtr = nullptr;

				if (newList == nullptr) {
					newList = newNode;
				} else {
					LinkedPolynomialTerm* cur3 = newList;
					while (cur3->nextTermPtr != nullptr) {
						cur3 = cur3->nextTermPtr;
					}
					cur3->nextTermPtr = newNode;
				}
			}
			cur = cur->nextTermPtr;
		}
		polynomialTermPtr = newList;
	}
};
