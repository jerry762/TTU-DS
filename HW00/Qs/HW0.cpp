// HW0.cpp : 定義主控台應用程式的進入點。
//

#include "stdio.h"
#include "stdlib.h"
#include "iostream"

using namespace std;

#define MAX 5

struct Node
{
	int item;
	Node* next;
};

typedef Node* nodePtr;

Node *inputData(int num, nodePtr headPtr)
{
	nodePtr currentPtr = headPtr;

	nodePtr tmpPtr = (nodePtr) malloc(sizeof(Node)) ; 
	tmpPtr->item = num;
	tmpPtr->next = NULL;

	if(headPtr == NULL)
		return tmpPtr;
	else	{
		while ( currentPtr->next != NULL )
			currentPtr = currentPtr->next;

		currentPtr->next = tmpPtr;

		return headPtr;
	}
}

void printArrayForward(int A[])
{


	// add your code here


}


void printArrayBackward(int A[], int i)
{


	// add your code here


}

void printListForward(nodePtr ptr)
{


	// add your code here


}

void printListBackward(nodePtr ptr)
{


	// add your code here


}

int main()
{
	int num;
	int A[MAX] = {0};
	nodePtr headPtr = NULL;

	printf("Input %d numbers: ", MAX);
	
	for ( int i=0; i<MAX; i++ ) {
		cin >> num;
		A[i] = num;
		headPtr = inputData( num, headPtr );
	}

	printf("\nArray Forward Iteratively:  ");
	printArrayForward(A);
	printf("\nArray Backward Recursively: ");
	printArrayBackward(A, 0);

	printf("\nList Forward Iteratively:  ");
	printListForward(headPtr);
	printf("\nList Backward Recursively: ");
	printListBackward(headPtr);

	printf("\n");
	system("PAUSE");
	return 0;
}
