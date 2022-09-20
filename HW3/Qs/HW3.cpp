// HW3.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#define MAX_TERMS 10

typedef struct{
	int coef;
	int expo;
} polynomialTerm;

void clear(polynomialTerm t[]) 
{
	for ( int i = 0; i < MAX_TERMS; i++ ) {
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void printArrayBasedPoly(polynomialTerm t[])
{
	if ( t[0].coef == 0 ) 
		return;

	if ( t[0].expo == 0 )
		cout << t[0].coef;
	else
		cout << t[0].coef << "X^" << t[0].expo;

	for ( int i = 1; i < MAX_TERMS; i++ ) {
		if ( t[i].coef == 0 ) 
			return;

		if ( t[i].expo == 0 )
			cout << " + " << t[i].coef;
		else
			cout << " + "<< t[i].coef  << "X^" << t[i].expo;
	}
}

void inputTerm(polynomialTerm t[], int coef, int expo)
{


	// add your code here


	return;
}

void addArrayBasedPoly(polynomialTerm a[], polynomialTerm b[], polynomialTerm d[])
{


	// add your code here


	return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	int coef, expo;

	while (1) {
		clear( a ); clear( b ); clear( d );

		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;

			inputTerm( a, coef, expo );
		}

		cout << "\n\na = ";
		printArrayBasedPoly( a );
		cout << "\n";
		
		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;

			inputTerm( b, coef, expo );
		}

		cout << "\n\nb = ";
		printArrayBasedPoly( b );
		cout << "\n";

		// d =a + b, where a, b, and d are polynomials
		addArrayBasedPoly( a, b, d );
		cout << "\na + b = ";
		printArrayBasedPoly( d );
		cout << "\n";
	}

	return 0;
}
