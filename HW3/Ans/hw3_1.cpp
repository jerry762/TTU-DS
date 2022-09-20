// HW3.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include <iostream>
using namespace std;

#define MAX_TERMS 10

typedef struct
{
	int coef;
	int expo;
} polynomialTerm;

void clear(polynomialTerm t[])
{
	for (int i = 0; i < MAX_TERMS; i++)
	{
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void printArrayBasedPoly(polynomialTerm t[])
{
	if (t[0].coef == 0)
		return;

	if (t[0].expo == 0)
		cout << t[0].coef;
	else
		cout << t[0].coef << "X^" << t[0].expo;

	for (int i = 1; i < MAX_TERMS; i++)
	{
		if (t[i].coef == 0)
			return;

		if (t[i].expo == 0)
			cout << " + " << t[i].coef;
		else
			cout << " + " << t[i].coef << "X^" << t[i].expo;
	}
}

void inputTerm(polynomialTerm t[], int coef, int expo) //* add your code here
{
	if (coef == 0)
		return;

	int size = 0;

	for (int i = 0; i < MAX_TERMS; i++)
	{
		if (t[i].coef != 0)
		{
			size++;
		}
	}

	t[size].expo = expo;
	t[size].coef = coef;

	if (size == 0)
		return;

	for (int i = 0; i < size; i++)
	{
		if (expo > t[i].expo)
		{
			for (int j = 0; j < size - i; j++)
				t[size - j] = t[size - 1 - j];

			t[i].expo = expo;
			t[i].coef = coef;

			break;
		}
		else if (expo == t[i].expo)
		{
			t[i].coef = coef;
			t[size].expo = 0;
			t[size].coef = 0;
			break;
		}
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
			d[pointD].expo = a[pointA].expo;
			d[pointD].coef = a[pointA].coef + b[pointB].coef;

			pointA++;
			pointB++;
			pointD++;
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

int main()
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	int coef, expo;

	while (1)
	{
		clear(a);
		clear(b);
		clear(d);

		for (int i = 0; i < MAX_TERMS; i++)
		{
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerm(a, coef, expo);
		}

		cout << "\n\na = ";
		printArrayBasedPoly(a);
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++)
		{
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerm(b, coef, expo);
		}

		cout << "\n\nb = ";
		printArrayBasedPoly(b);
		cout << "\n";

		// d =a + b, where a, b, and d are polynomials
		addArrayBasedPoly(a, b, d);
		cout << "\na + b = ";
		printArrayBasedPoly(d);
		cout << "\n";
	}

	return 0;
}
