﻿// Final.cpp : 定義主控台應用程式的進入點。
//

// #include "stdafx.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include "BinarySearchTree.h"
#include "HashedDictionary.h"

using namespace std;

void displayWordCount(BinaryNode<string> &entry)
{
	cout << entry.getItem() << "(" << entry.getCount() << ")  ";
}

void displayWordCount(HashedEntry<string, string> &entryPtr)
{
	cout << entryPtr.getItem() << "(" << entryPtr.getCount() << ")  ";
}

void input(string sMessage, string &sInputString)
{
	do
	{
		cout << sMessage << endl;
		cin >> sInputString;
	} while (cin.fail());
}

void input(string sMessage, int &inputNum)
{
	do
	{
		cout << sMessage << endl;
		cin >> inputNum;
	} while (cin.fail());
}

void stringToTokens(queue<string> &aQueue, string aString)
{
	string token, theDelimters = ".,!?;: ";
	int end = 0;
	int start = aString.find_first_not_of(theDelimters, end);

	while (start != string::npos)
	{
		end = aString.find_first_of(theDelimters, start);
		token = aString.substr(start, end - start);
		aQueue.push(token);
		start = aString.find_first_not_of(theDelimters, end);
	}
}

// ================ Q1 Begins Here ==================
#define PQSIZE 10

void pqArrayInsert(BinaryNode<string> *pqArray, int &size, const string word)
{
	if (size == PQSIZE)
		cout << "ARRAY Priority queue full!" << endl;

	bool isFound = false;

	for (size_t i = 0; i < size; i++)
	{
		if (pqArray[i].getItem() == word)
		{
			pqArray[i].countUp();
			isFound = true;
			break;
		}
	}

	if (!isFound)
	{
		pqArray[size] = word;
		size++;
	}
	else
	{
		for (int i = size - 1; i >= 1; i--)
		{
			if (pqArray[i - 1].getCount() < pqArray[i].getCount())
			{
				swap(pqArray[i - 1], pqArray[i]);
			}
		}
	}
}

int pqArrayDelete(BinaryNode<string> *pqArray, int &size, const string word)
{
	if (size == 0)
	{
		cout << "ARRAY Priority queue empty!" << endl;
		return -1;
	}

	size_t pos = 0;
	bool isZero = false;
	bool isFound = false;

	for (size_t i = 0; i < size; i++)
	{
		if (pqArray[i].getItem() == word)
		{
			pqArray[i].countDown();

			if (pqArray[i].getCount() == 0)
				isZero = true;

			pos = i;
			isFound = true;

			break;
		}
	}

	if (isFound)
	{
		if (isZero)
		{
			for (size_t i = pos; i < size - 1; i++)
				pqArray[i] = pqArray[i + 1];

			size--;
		}
		else
		{
			for (size_t i = pos; i < size - 1; i++)
			{
				if (pqArray[i].getCount() < pqArray[i + 1].getCount())
				{
					swap(pqArray[i], pqArray[i + 1]);
				}
			}
		}

		return 1;
	}
	else
	{
		return -1;
	}
}

void doQ1()
{
	BinaryNode<string> pqItems[PQSIZE];
	queue<string> myTokenQueue;
	string sInput, aLine, aWord;
	int i, size = 0;

	while (1)
	{
		input("\nEnter A to Add words, R to Remove a word, or X to Exit", sInput);

		if (sInput == "A" || sInput == "a")
		{
			cin.ignore();
			cout << "Enter a line of text: ";
			getline(cin, aLine);
			stringToTokens(myTokenQueue, aLine);

			while (!myTokenQueue.empty())
			{
				aWord = myTokenQueue.front();
				myTokenQueue.pop();
				pqArrayInsert(pqItems, size, aWord);
			}

			for (i = 0; i < size; i++)
				displayWordCount(pqItems[i]);

			cout << endl;
		}
		else if (sInput == "R" || sInput == "r")
		{
			if (size == 0)
				cout << "PQ is empty!" << endl;
			else
			{
				input("Enter word: ", aWord);

				if (pqArrayDelete(pqItems, size, aWord) < 0)
					cout << "Not exist in PQ!" << endl;
				else if (size == 0)
					cout << "Last word deleted!" << endl;
				else
				{
					for (i = 0; i < size; i++)
						displayWordCount(pqItems[i]);

					cout << endl;
				}
			}
		}
		else if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "Unknown command!\r" << endl;
	}
}

// ================ Q2 Begins Here ==================
void showAdjMatrix(int **matrixGraph, int numVertices)
{
	for (int i = 0; i < numVertices; i++)
	{
		for (int j = 0; j < numVertices; j++)
		{
			if (matrixGraph[i][j] == INT_MAX)
				cout << " -";
			else
				cout << ' ' << matrixGraph[i][j];
		}
		cout << '\n';
	}
}

void addEdges(int **matrixGraph, int numVertices, int vertexNo)
{
	for (size_t i = 0; i < numVertices; i++)
	{
		if (i != vertexNo && matrixGraph[vertexNo][i] == INT_MAX)
		{
			matrixGraph[vertexNo][i] = 1;
		}
		if (i != vertexNo && matrixGraph[i][vertexNo] == INT_MAX)
		{
			matrixGraph[i][vertexNo] = 1;
		}
	}
}

void removeEdges(int **matrixGraph, int numVertices, int vertexNo)
{
	for (size_t i = 0; i < numVertices; i++)
	{
		if (i != vertexNo && matrixGraph[vertexNo][i] != INT_MAX)
		{
			matrixGraph[vertexNo][i] = INT_MAX;
		}
		if (i != vertexNo && matrixGraph[i][vertexNo] != INT_MAX)
		{
			matrixGraph[i][vertexNo] = INT_MAX;
		}
	}
}

void doQ2()
{
	string sInput;
	int numVertices, u, v, weight, vertexNo;

	ifstream inFile("graph.txt");

	if (!inFile)
	{
		cerr << "Error: Failed to open "
			 << "graph.txt"
			 << " for input! \n";
		return;
	}

	if (inFile.peek() == EOF)
	{
		cerr << "Error: Empty input file! \n";
		return;
	}

	inFile >> numVertices;

	int **matrixGraph = new int *[numVertices];

	for (int i = 0; i < numVertices; i++)
	{
		matrixGraph[i] = new int[numVertices];

		for (int j = 0; j < numVertices; j++)
			matrixGraph[i][j] = INT_MAX;

		matrixGraph[i][i] = 0;
	}

	while (inFile.peek() != EOF)
	{
		inFile >> u >> v >> weight;

		if (inFile.fail())
			break;

		if (u < numVertices && v < numVertices)
			matrixGraph[u][v] = matrixGraph[v][u] = weight;
	}

	cout << "\nThe adjacency matrix:\n";
	showAdjMatrix(matrixGraph, numVertices);

	while (1)
	{
		input("\nEnter A to Add Edges, R to Remove Edges, or X to Exit", sInput);

		if (sInput == "A" || sInput == "a")
		{
			input("Enter vertex no: ", vertexNo);

			if (vertexNo < numVertices)
			{
				addEdges(matrixGraph, numVertices, vertexNo);
				showAdjMatrix(matrixGraph, numVertices);
			}
			else
				cerr << "Error: Vertex no. out of range!  \n";
		}
		else if (sInput == "R" || sInput == "r")
		{
			input("Enter vertex no: ", vertexNo);

			if (vertexNo < numVertices)
			{
				removeEdges(matrixGraph, numVertices, vertexNo);
				showAdjMatrix(matrixGraph, numVertices);
			}
			else
				cerr << "Error: Vertex no. out of range!  \n";
		}
		else if (sInput == "X" || sInput == "x")
		{
			if (inFile.is_open())
				inFile.close();

			for (int i = 0; i < numVertices; i++)
				delete[] matrixGraph[i];

			delete matrixGraph;

			return;
		}
		else
			cout << "Unknown command!\r" << endl;
	}

	return;
}

// ================ Q3 Begins Here ==================

void display(BinaryNode<string> &aNode)
{
	cout << aNode.getItem() << "  ";
}

void doQ3()
{
	string sInput, aString, aLine;
	BinarySearchTree<string> myBST;

	while (1)
	{
		input("\nEnter command: A to Add,  F to Find, M to Mirror, C to Clear, or X to Exit", sInput);

		if (sInput == "A" || sInput == "a")
		{
			cin.ignore();
			cout << "Enter a line of text: ";
			getline(cin, aLine);

			string token, theDelimters = ".,!?;: ";
			int end = 0;
			int start = aLine.find_first_not_of(theDelimters, end);

			while (start != string::npos)
			{
				end = aLine.find_first_of(theDelimters, start);
				token = aLine.substr(start, end - start);
				myBST.add(token);
				start = aLine.find_first_not_of(theDelimters, end);
			}

			cout << endl
				 << "The inoder traversal of the BST is " << endl;
			myBST.inorderTraverse(display);
			cout << endl
				 << "The reverse levelorder traversal of the BST is " << endl;
			myBST.reverseLevelorderTraverse(display);
			cout << endl;
		}
		else if (sInput == "F" || sInput == "f")
		{
			input("Enter a word: ", aString);

			if (myBST.find(aString))
				cout << endl
					 << aString << " exists in the BST." << endl;
			else
				cout << endl
					 << aString << " does not exist in the BST." << endl;
		}
		else if (sInput == "M" || sInput == "m")
		{
			cout << endl
				 << "The inorder traversal of the input BST is " << endl;
			myBST.inorderTraverse(display);

			myBST.mirror();
			cout << endl
				 << "The inorder traversal of the mirrored BST is " << endl;
			myBST.inorderTraverse(display);
			cout << endl;
		}
		else if (sInput == "C" || sInput == "c")
		{
			myBST.clear();
			cout << endl
				 << "BST is empty." << endl;
		}
		else if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "Unknown command!\r" << endl;
	}

	return;
}

// ================ Q3 Begins Here ==================
void doQ4()
{
	queue<string> myTokenQueue;
	string sInput, aLine, aWord;
	HashedEntry<string, string> *itemPtr;
	HashedDictionary<string, string> myHashTable(11);

	while (1)
	{
		input("\nEnter A to Add, R to Remove, Q to Query, D to Display, C to Clear, or X to Exit", sInput);

		if (sInput == "A" || sInput == "a")
		{
			cin.ignore();
			cout << "Enter a line of text: ";
			getline(cin, aLine);
			stringToTokens(myTokenQueue, aLine);

			while (!myTokenQueue.empty())
			{
				aWord = myTokenQueue.front();
				myTokenQueue.pop();
				myHashTable.add(aWord, aWord);
			}
		}
		else if (sInput == "R" || sInput == "r")
		{
			input("Enter word: ", aWord);

			if (myHashTable.remove(aWord))
				cout << aWord << " is removed." << endl;
			else
				cout << "Word not found!" << endl;
		}
		else if (sInput == "Q" || sInput == "q")
		{
			input("Enter word: ", aWord);
			itemPtr = myHashTable.getEntry(aWord);

			if (itemPtr == nullptr)
				cout << "Word not found!" << endl;
			else
			{
				cout << "Retireved word is: ";
				displayWordCount(*itemPtr);
				cout << endl;
			}
		}
		else if (sInput == "D" || sInput == "d")
		{
			cout << "Words in buckets are: " << endl;

			int i, len = myHashTable.getTableSize();

			for (i = 0; i < len; i++)
			{
				cout << i << ": ";
				myHashTable.traverse(i, displayWordCount);
				cout << endl;
			}
		}
		else if (sInput == "C" || sInput == "c")
		{
			myHashTable.clear();
			cout << "Words in buckets are cleared." << endl;
		}
		else if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "Unknown command!\r" << endl;
	}
}

// =============== Main Begins Here =================

int main()
{
	string sCommand, sName, sNum, sMessage;

	while (1)
	{
		cout << endl;
		cout << "1. Priroity queue operations" << endl;
		cout << "2. Graph operations" << endl;
		cout << "3. Binary search tree operations" << endl;
		cout << "4. Hash table operations" << endl;

		input("Enter Question Number( 1 ~ 4 ) or 0 to Exit:", sNum);

		switch (sNum[0] - '0')
		{
		case 0:
			return 0;
		case 1:
			doQ1();
			break;
		case 2:
			doQ2();
			break;
		case 3:
			doQ3();
			break;
		case 4:
			doQ4();
			break;
		}
	}
}
// ============== Main Program Ends Here ================
