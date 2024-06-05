// Final202312.cpp: 定義主控台應用程式的進入點。
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
	if (size == PQSIZE)
		cout << "ARRAY Priority queue full!" << endl;

	// add your code here

	// pqArray[size].setItem(word);
	// pqArray[size].countUp();
	// size++;
}

BinaryNode<string> pqArrayMaxWord(BinaryNode<string> *pqArray, int &size)
{
	string word = "";
	BinaryNode<string> entry;

	// add your code here

	return entry;
}

int pqArrayWordCount(BinaryNode<string> *pqArray, int &size, int index)
{

	// add your code here

	return 0;
}

int pqArrayDelete(BinaryNode<string> *pqArray, int &size, const string word)
{
	if (size == 0)
	{
		cout << "ARRAY Priority queue empty!" << endl;
		return -1;
	}

	// add your code here

	// pqArray[size].countDown();
	// size--;

	return -1;
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

			cout << endl
				 << pqArrayWordCount(pqItems, size, 0)
				 << " words in the text." << endl;
			BinaryNode<string> word = pqArrayMaxWord(pqItems, size);
			displayWordCount(word);
			cout << "has the highest word count.";

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

int RemoveMaxEdges(int **matrixGraph, int numVertices)
{

	// add your code here

	return INT_MAX;
}

int MaxDegree(int **matrixGraph, int numVertices)
{

	// add your code here

	return 0;
}

void BFS(int **matrixGraph, int numVertices, int vertexNo, bool *visited)
{
	visited[vertexNo] = true;
	cout << " v" << vertexNo;

	// add your code here

	return;
}

void doBFS(int **matrixGraph, int numVertices, int vertexNo)
{
	bool *visited = new bool[numVertices];

	for (int i = 0; i < numVertices; i++)
		visited[i] = false;

	cout << "\nBFS:";
	BFS(matrixGraph, numVertices, vertexNo, visited);
	cout << "\n";
	delete[] visited;

	return;
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

	cout << "\nThe adjacency matrix:\n";
	showAdjMatrix(matrixGraph, numVertices);
	cout << "\nThe nodes of the graph has at most " << MaxDegree(matrixGraph, numVertices) << " edges" << endl;

	while (1)
	{
		input("\nEnter command: B to do BFS, R to Remove maximun weight edges , or X to Exit", sInput);

		if (sInput == "R" || sInput == "r")
		{
			int n = RemoveMaxEdges(matrixGraph, numVertices);

			if (n < INT_MAX)
				cout << "\nThe edge(s) with maximun weight " << n << " is(are) removed" << endl;
			else
				cout << "\nNo edge is removed\n";

			cout << "\nThe adjacency matrix:\n";
			showAdjMatrix(matrixGraph, numVertices);
			cout << "\nThe nodes of the graph has at most " << MaxDegree(matrixGraph, numVertices) << " edges" << endl;
		}
		else if (sInput == "B" || sInput == "b")
		{
			input("Enter start vertex no: ", vertexStartNo);

			if (vertexStartNo < numVertices)
				doBFS(matrixGraph, numVertices, vertexStartNo);
			else
				cerr << "Error: Vertex no. out of range! \r\n";
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
		input("\nEnter command: A to Add,  L to NonLeaf, N to Count, C to Clear, or X to Exit", sInput);

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

			if (myBST.isBalanced())
				cout << endl
					 << "The tree is balanced";
			else
				cout << endl
					 << "The tree is not balanced";
			cout << endl;
		}
		else if (sInput == "L" || sInput == "l")
		{
			input("Enter a word: ", aString);

			if (myBST.isNonLeaf(aString, "i"))
				cout << endl
					 << aString << " is a nonleaf node. (Iteration)";
			else
				cout << endl
					 << aString << " is not a nonleaf node. (Iteration)";

			if (myBST.isNonLeaf(aString, "r"))
				cout << endl
					 << aString << " is a nonleaf node. (Recursion)" << endl;
			else
				cout << endl
					 << aString << " is not a nonleaf node. (Recursion)" << endl;
		}
		else if (sInput == "N" || sInput == "n")
		{
			cout << endl
				 << "The iterative nonleaf count of the BST is " << myBST.countNonLeaves("i");
			cout << endl
				 << "The recursive nonleaf count of the BST is " << myBST.countNonLeaves("r") << endl;
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
		input("\nEnter A to Add, R to Remove, Q to Query, C to Clear, or X to Exit", sInput);

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
			cout << "\\nWords in buckets are cleared." << endl;
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
