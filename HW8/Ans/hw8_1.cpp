// HW8.cpp : �w�q�D���x���ε{�����i�J�I�C
//
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

void input(string sMessage, string &sInputString)
{
	do
	{
		cout << sMessage << endl;
		cin >> sInputString;
	} while (cin.fail());

	return;
}

void pushAndCorrectDeque(string &aString, deque<char> &aDeque) //* add your code here
{
	for (int i = 0; i < aString.size(); i++)
	{
		if (aString[i] == '<')
		{
		}

		else
		{
		}
	}
}

void pushAndCorrectStackQueue(string &aString, stack<char> &aStack, queue<char> &aQueue) //* add your code here
{
	for (int i = 0; i < aString.size(); i++)
	{
	}
}

bool isPalindromeDeque(deque<char> aDeque) //* add your code here
{

	return false;
}

bool isPalindromeStackQueue(stack<char> aStack, queue<char> aQueue) //* add your code here
{

	return false;
}

int main()
{
	string sInput;

	// Queue STL
	queue<char> myQueue;

	for (char j = 0; j < 5; j++)
		myQueue.push(j + 'A');

	cout << "myQueue is a true queue:  ";

	while (!myQueue.empty())
	{
		cout << myQueue.front() << " ";
		myQueue.pop();
	}

	cout << endl;

	// Use Deque STL as Queue
	deque<char> myDeque;

	for (char j = 0; j < 5; j++)
		myDeque.push_back(j + 'A');

	cout << "myDeque is also a queue:  ";

	while (!myDeque.empty())
	{
		cout << myDeque.front() << " ";
		myDeque.pop_front();
	}

	cout << endl;

	for (char j = 0; j < 5; j++)
		myDeque.push_front(j + 'A');

	cout << "myDeque is still a queue: ";

	while (!myDeque.empty())
	{
		cout << myDeque.back() << " ";
		myDeque.pop_back();
	}

	cout << endl;

	// Stack STL

	stack<char> myStack;

	for (char j = 0; j < 5; j++)
		myStack.push(j + 'A');

	cout << "myStack is a true stack:  ";

	while (!myStack.empty())
	{
		cout << myStack.top() << " ";
		myStack.pop();
	}

	cout << endl;

	// Use Deque STL as Stack

	for (char j = 0; j < 5; j++)
		myDeque.push_front(j + 'A');

	cout << "myDeque is also a stack:  ";

	while (!myDeque.empty())
	{
		cout << myDeque.front() << " ";
		myDeque.pop_front();
	}

	cout << endl;

	for (char j = 0; j < 5; j++)
		myDeque.push_back(j + 'A');

	cout << "myDeque is still a stack: ";

	while (!myDeque.empty())
	{
		cout << myDeque.back() << " ";
		myDeque.pop_back();
	}

	cout << endl;

	while (1)
	{
		input("\nEnter a string or X to Exit:", sInput);

		if (sInput.size() == 1 && (sInput == "X" || sInput == "x"))
			return 0;

		pushAndCorrectDeque(sInput, myDeque);
		bool yes = isPalindromeDeque(myDeque);

		for (int i = myDeque.size(); i > 0; i--)
		{
			cout << myDeque.front();
			myDeque.pop_front();
		}

		if (yes)
			cout << " is a palindrome" << endl;
		else
			cout << " is not a palindrome" << endl;

		pushAndCorrectStackQueue(sInput, myStack, myQueue);
		yes = isPalindromeStackQueue(myStack, myQueue);

		for (int i = myQueue.size(); i > 0; i--)
		{
			cout << myQueue.front();
			myQueue.pop();
		}

		if (yes)
			cout << " is a palindrome" << endl;
		else
			cout << " is not a palindrome" << endl;
	}

	return 0;
}
