// HW0.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#define MAX 5

struct Node
{
	int item;
	Node *next;
};

typedef Node *nodePtr;

Node *inputData(int num, nodePtr headPtr)
{
	nodePtr currentPtr = headPtr;

	nodePtr tmpPtr = (nodePtr)malloc(sizeof(Node));
	tmpPtr->item = num;
	tmpPtr->next = NULL;

	if (headPtr == NULL)
		return tmpPtr;
	else
	{
		while (currentPtr->next != NULL)
			currentPtr = currentPtr->next;

		currentPtr->next = tmpPtr;

		return headPtr;
	}
}

void printArrayForward(int A[]) //* add your code here
{
	for (int i = 0; i < MAX; i++)
	{
		cout << A[i] << " ";
	}
}

void printArrayBackward(int A[], int i) //* add your code here
{
	if (i == MAX - 1)
	{
		cout << A[i] << " ";
		return;
	}
	printArrayBackward(A, i + 1);
	cout << A[i] << " ";
}

void printListForward(nodePtr ptr) //* add your code here
{
	while (ptr)
	{
		cout << ptr->item << " ";
		ptr = ptr->next;
	}
}

void printListBackward(nodePtr ptr) //* add your code here
{
	if (ptr->next == nullptr)
	{
		cout << ptr->item << " ";
		return;
	}
	printListBackward(ptr->next);
	cout << ptr->item << " ";
}

int main()
{
	int num;
	int A[MAX] = {0};
	nodePtr headPtr = NULL;

	printf("Input %d numbers: ", MAX);

	for (int i = 0; i < MAX; i++)
	{
		cin >> num;
		A[i] = num;
		headPtr = inputData(num, headPtr);
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
