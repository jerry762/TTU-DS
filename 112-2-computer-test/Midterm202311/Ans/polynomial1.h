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

	void inputArrayBasedTerms(int coef, int expo)
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
	bool isIncreasingOrder()
	{
		return isIncreasingOrder(0);
	}

	bool isIncreasingOrder(int index)
	{
		if (terms[index].coef == 0)
			return false;

		if (index == MAX_TERMS - 2 || terms[index + 1].coef == 0)
			return true;

		if (terms[index].expo >= terms[index + 1].expo)
			return false;

		return isIncreasingOrder(index + 1);
	}

	void updateArrayBasedTerm(int coef, int expo) 
	{
		bool flag = false;

		for (int i = 0; terms[i].coef != 0; i++)
		{
			if (expo == terms[i].expo)
			{
				flag = true;

				if (coef != 0)
					terms[i].coef = coef;
				else
				{
					terms[i].coef = 0;
					terms[i].expo = 0;
				}

				for (int j = i + 1; terms[j].coef != 0; j++)
				{
					if (expo == terms[j].expo)
					{
						terms[j].expo = 0;
						terms[j].coef = 0;
					}
				}
				
				for (int j = 0; j < MAX_TERMS; j++)
				{
					if (terms[j].expo == 0 && terms[j].coef == 0)
					{
						for (int k = j + 1; k < MAX_TERMS; k++)
						{
							if (terms[k].coef != 0)
							{
								swap(terms[j], terms[k]);
								break;
							}
						}
					}
				}
				break;
			}
		}

		if (!flag)
			inputArrayBasedTerms(coef, expo);
	}

	void swapArrayBasedTerms(int expo1, int expo2) 
	{
		int pos1 = -1;
		int pos2 = -1;

		for (int i = 0; terms[i].coef != 0; i++)
		{
			if (expo1 == terms[i].expo)
				pos1 = i;

			if (expo2 == terms[i].expo)
				pos2 = i;
		}

		if (pos1 != -1 && pos2 != -1)
			swap(terms[pos1], terms[pos2]);
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

	void inputLinkBasedTerms(int coef, int expo)
	{
		if (coef != 0)
		{
			LinkedPolynomialTerm* tmpPtr;

			tmpPtr = new LinkedPolynomialTerm;
			tmpPtr->coef = coef;
			tmpPtr->expo = expo;
			tmpPtr->nextTermPtr = polynomialTermPtr;

			polynomialTermPtr = tmpPtr;
		}

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

	bool isIncreasingOrder()
	{
		return isIncreasingOrder(polynomialTermPtr);
	}

	bool isIncreasingOrder(LinkedPolynomialTerm *currentPtr)
	{
		if (!polynomialTermPtr)
			return false;

		if (!currentPtr->nextTermPtr)
			return true;

		if (currentPtr->expo >= currentPtr->nextTermPtr->expo)
			return false;

		return isIncreasingOrder(currentPtr->nextTermPtr);
	}

	void updateLinkBasedTerm(int coef, int expo) 
	{
		LinkedPolynomialTerm* currPtr1 = polynomialTermPtr;
		LinkedPolynomialTerm* prePtr1 = nullptr;
		bool flag = false;

		while (currPtr1)
		{
			if (expo == currPtr1->expo)
			{
				LinkedPolynomialTerm* currPtr2 = currPtr1->nextTermPtr;
				LinkedPolynomialTerm* prePtr2 = currPtr1;

				flag = true;

				while (currPtr2)
				{
					if (expo == currPtr2->expo)
					{
						prePtr2->nextTermPtr = currPtr2->nextTermPtr;
						delete currPtr2;
						currPtr2 = prePtr2;
					}

					prePtr2 = currPtr2;
					currPtr2 = currPtr2->nextTermPtr;
				}

				if (coef != 0)
					currPtr1->coef = coef;
				else
				{
					if (currPtr1 == polynomialTermPtr)
						polynomialTermPtr = currPtr1->nextTermPtr;
					else
						prePtr1->nextTermPtr = currPtr1->nextTermPtr;

					delete currPtr1;
				}
				break;
			}
			prePtr1 = currPtr1;
			currPtr1 = currPtr1->nextTermPtr;
		}

		if (!flag)
			inputLinkBasedTerms(coef, expo);

	}

	void swapLinkBasedTerms(int expo1, int expo2) 
	{
		LinkedPolynomialTerm* currPtr = polynomialTermPtr;
		LinkedPolynomialTerm* pos1 = nullptr;
		LinkedPolynomialTerm* pos2 = nullptr;

		while (currPtr)
		{
			if (expo1 == currPtr->expo)
				pos1 = currPtr;

			if (expo2 == currPtr->expo)
				pos2 = currPtr;

			currPtr = currPtr->nextTermPtr;
		}

		if (pos1 && pos2)
		{
			swap(pos1->expo, pos2->expo);
			swap(pos1->coef, pos2->coef);
		}
	}

	void linkBasedReverse()
	{
		// add yor code here

		return;
	}

	void linkBasedDifferentiation()
	{
		// add yor code here

		return;
	}

	int computeI(int x)
	{
		// add yor code here

		return 0;
	}

	int computeR(int x)
	{
		return computeR(x, polynomialTermPtr);;
	}

	int computeR(int x, LinkedPolynomialTerm *currPtr)
	{
		// add yor code here

		return 0;
	}
};
