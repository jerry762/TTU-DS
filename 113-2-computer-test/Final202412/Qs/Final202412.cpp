// Final202312.cpp: �w�q�D���x���ε{�����i�J�I�C
//

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <stack>
#include <queue>
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

void displayWordCount(HashedEntry<string, string> *entryPtr)
{
	if (entryPtr)
		cout << entryPtr->getItem() << "(" << entryPtr->getCount() << ")  ";
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

	// add your code here

	return;
}

int pqArrayMaxWordCount(BinaryNode<string> *pqArray, int &size, int index)
{

	// add your code here

	return 0;
}

int pqArrayMaxWordCountNo(BinaryNode<string> *pqArray, int &size, int index)
{

	// add your code here

	return 0;
}

BinaryNode<string> pqArrayMaxWord(BinaryNode<string> *pqArray, int &size)
{
	BinaryNode<string> entry;

	// add your code here

	return entry;
}

void doQ1()
{
	BinaryNode<string> pqItems[PQSIZE];
	queue<string> myTokenQueue;
	string sInput, aLine, aWord;
	int i, size = 0;

	while (1)
	{
		input("\nEnter A to Add words or X to Exit", sInput);

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

			cout << endl
				 << pqArrayMaxWordCountNo(pqItems, size, 0)
				 << " words with highest word count "
				 << pqArrayMaxWordCount(pqItems, size, 0)
				 << endl;
			BinaryNode<string> word = pqArrayMaxWord(pqItems, size);
			displayWordCount(word);
			cout << "has the highest word count.";

			cout << endl;
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

void showDegreeCount(int **matrixGraph, int numVertices)
{

	// add your code here

	return;
}

int RemoveMaxDegreeEdges(int **matrixGraph, int numVertices)
{

	// add your code here

	return 0;
}

bool isConnected(int **matrixGraph, int numVertices)
{

	// add your code here

	return false;
}

void doQ2()
{
	string sInput;
	int numVertices, u, v, weight, vertexNo, vertexStartNo;

	ifstream inFile("graph.txt");

	if (!inFile)
	{
		cerr << "Error: Failed to open " << "graph.txt" << " for input! \n";
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

	while (1)
	{
		cout << "\nThe adjacency matrix:\n";
		showAdjMatrix(matrixGraph, numVertices);
		cout << "\nThe vertices with the degree are ";
		showDegreeCount(matrixGraph, numVertices);
		cout << endl;
		cout << "\nThe graph ";
		if (isConnected(matrixGraph, numVertices))
			cout << "is connected.";
		else
			cout << "is NOT connected.";
		cout << endl;

		input("\nEnter command: R to Remove maximun degree edges or X to Exit", sInput);

		if (sInput == "R" || sInput == "r")
		{
			int n = RemoveMaxDegreeEdges(matrixGraph, numVertices);

			if (n > 0)
				cout << "\n"
					 << n << " edges of the vertices with the maximun degree " << " are removed" << endl;
			else
				cout << "\nNo edge is removed\n";
		}
		else if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "Unknown command!\r\n"
				 << endl;
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
		input("\nEnter command: A to add,  N to nodeDegree, S to singleChildCount, C to clear, or X to Exit", sInput);

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
				 << "Inoder: ";
			myBST.inorderTraverse(display);
			cout << endl
				 << "\nThe height is " << myBST.getHeight();

			if (abs(myBST.getHeightDifference()) < 2)
				cout << endl
					 << "The tree is balanced";
			else
				cout << endl
					 << "The tree is not balanced";
			cout << endl;
		}
		else if (sInput == "N" || sInput == "n")
		{
			input("Enter a word: ", aString);

			int degree = myBST.nodeDegree("i", aString);

			if (degree < 0)
				cout << endl
					 << aString << " does not exist. (Iteration)";
			else if (degree == 0)
				cout << endl
					 << aString << " is a leaf node. (Iteration)";
			else
				cout << endl
					 << aString << " is not a leaf node. (Iteration)";

			degree = myBST.nodeDegree("r", aString);

			if (degree < 0)
				cout << endl
					 << aString << " does not exist. (Recursion)";
			else if (degree == 0)
				cout << endl
					 << aString << " is a leaf node. (Recursion)" << endl;
			else
				cout << endl
					 << aString << " is not a leaf node. (Recursion)" << endl;
		}
		else if (sInput == "S" || sInput == "s")
		{
			cout << endl
				 << "The iterative signle child node count of the BST is " << myBST.singleChildCount("i");
			cout << endl
				 << "The recursive signle child node count of the BST is " << myBST.singleChildCount("r") << endl;
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

// ================ Q4 Begins Here ==================

void doQ4()
{
	queue<string> myTokenQueue;
	string sInput, aLine, aWord;
	HashedEntry<string, string> *itemPtr;
	HashedDictionary<string, string> myHashTable(11);

	while (1)
	{
		input("\nEnter A to Add, Q to Query, C to Clear, or X to Exit", sInput);

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
		else if (sInput == "Q" || sInput == "q")
		{
			input("Enter word: ", aWord);
			itemPtr = myHashTable.getEntry(aWord);

			if (itemPtr == nullptr)
				cout << "\nWord not found!" << endl;
			else
			{
				cout << "\nRetireved word is: ";
				displayWordCount(*itemPtr);
				cout << endl;
			}
		}
		else if (sInput == "C" || sInput == "c")
		{
			myHashTable.clear();
			cout << "\nWords in buckets are cleared." << endl;
		}
		else if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "\nUnknown command!\n"
				 << endl;

		cout << "\nWords in buckets are: " << endl;

		int i, len = myHashTable.getTableSize();

		for (i = 0; i < len; i++)
		{
			cout << i << ": ";
			myHashTable.traverse(i, displayWordCount);
			cout << endl;
		}

		cout << endl
			 << myHashTable.wordCount()
			 << " words in the text" << endl;

		cout << "The buckets with the maximum number of words are" << endl;
		myHashTable.displayMaxBucket();

		cout << endl
			 << myHashTable.maxCountNo()
			 << " words have highest word count."
			 << endl;

		displayWordCount(myHashTable.maxWord());
		cout << " has the highest word count.\n";
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
