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

    ArrayPolynomial()
    {
        for (int i = 0; i < MAX_TERMS; i++)
            terms[i].coef = terms[i].expo = 0;
    }

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
        if (coef == 0)
            return;

        int i = 0;

        while (terms[i].coef != 0)
        {
            if (terms[i].expo == expo)
            {
                if ((terms[i].coef + coef) == 0)
                {
                    while (terms[i].coef != 0)
                    {
                        terms[i].coef = terms[i + 1].coef;
                        terms[i].expo = terms[i + 1].expo;
                        i++;
                    }
                }
                else
                    terms[i].coef += coef;

                return;
            }
            i++;
        }

        terms[i].coef = coef;
        terms[i].expo = expo;
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

    void copyRecursively(ArrayPolynomial &poly)
    {
        copyRecursively(poly, 0);
    }

    void copyRecursively(ArrayPolynomial &poly, int i)
    {
        if (poly.terms[i].coef == 0)
            return;

        copyRecursively(poly, i + 1);

        terms[i].coef = poly.terms[i].coef;
        terms[i].expo = poly.terms[i].expo;
    }

    void reverseCopy(ArrayPolynomial &poly)
    {
        int len = 0;
        int i = 0;

        while (poly.terms[len].coef != 0)
            len++;

        while (poly.terms[i].coef != 0)
        {
            terms[len - 1 - i].coef = poly.terms[i].coef;
            terms[len - 1 - i].expo = poly.terms[i].expo;
            i++;
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
        if (coef == 0)
            return;

        LinkedPolynomialTerm *currPtr = polynomialTermPtr;
        LinkedPolynomialTerm *prevPtr = nullptr;
        LinkedPolynomialTerm *tmpPtr;

        while (currPtr)
        {
            if (currPtr->expo == expo)
            {
                if ((currPtr->coef + coef) == 0)
                {
                    if (currPtr == polynomialTermPtr)
                        polynomialTermPtr = currPtr->nextTermPtr;
                    else
                        prevPtr->nextTermPtr = currPtr->nextTermPtr;

                    delete currPtr;
                    currPtr = nullptr;
                }
                else
                    currPtr->coef += coef;

                return;
            }
            prevPtr = currPtr;
            currPtr = currPtr->nextTermPtr;
        }

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

    void copyRecursively(LinkedPolynomial &poly)
    {
        copyRecursively(poly.polynomialTermPtr);
    }

    void copyRecursively(LinkedPolynomialTerm *currPtr)
    {
        if (!currPtr)
            return;

        copyRecursively(currPtr->nextTermPtr);

        LinkedPolynomialTerm *tmpPtr = new LinkedPolynomialTerm;
        tmpPtr->coef = currPtr->coef;
        tmpPtr->expo = currPtr->expo;

        tmpPtr->nextTermPtr = polynomialTermPtr;
        polynomialTermPtr = tmpPtr;
    }

    void reverseCopy(LinkedPolynomial &poly)
    {
        LinkedPolynomialTerm *currPtr = poly.polynomialTermPtr;

        while (currPtr)
        {
            LinkedPolynomialTerm *tmpPtr = new LinkedPolynomialTerm;
            tmpPtr->coef = currPtr->coef;
            tmpPtr->expo = currPtr->expo;

            tmpPtr->nextTermPtr = polynomialTermPtr;
            polynomialTermPtr = tmpPtr;

            currPtr = currPtr->nextTermPtr;
        }
    }
};
