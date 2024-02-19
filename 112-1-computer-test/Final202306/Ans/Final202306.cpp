// Final202306.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>
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

bool pqArrayAdd(BinaryNode<string> *pqArray, int &size, const string word) //* add your code here
{
	bool find = false;
	int i = 0;

	for (; i < size; i++)
	{
		if (pqArray[i].getItem() == word)
		{
			find = true;
			pqArray[i].countUp();
			break;
		}
	}

	if (!find)
	{
		pqArray[size].setItem(word);
		pqArray[size].setCount(1);
		size++;
	}

	for (int j = i - 1; j >= 0; j--)
	{
		if (pqArray[i].getCount() > pqArray[j].getCount())
		{
			swap(pqArray[i], pqArray[j]);
			i = j;
		}
		else if (pqArray[i].getCount() == pqArray[j].getCount())
		{
			if (pqArray[i].getItem().size() > pqArray[j].getItem().size())
			{
				swap(pqArray[i], pqArray[j]);
				i = j;
			}
			else if (pqArray[i].getItem().size() == pqArray[j].getItem().size())
			{
				if (pqArray[i].getItem() > pqArray[j].getItem())
				{
					swap(pqArray[i], pqArray[j]);
					i = j;
				}
			}
		}
	}

	return true;
}

bool pqArrayRemove(BinaryNode<string> *pqArray, int &size) //* add your code here
{
	if (size == 0)
		return false;
	else if (size == 1)
	{
		if (pqArray[0].getCount() == 1)
			size--;
		else
			pqArray[0].countDown();
	}
	else
	{
		int i = 0;

		pqArray[0].countDown();

		for (int j = i + 1; j < size; j++)
		{
			if (pqArray[i].getCount() < pqArray[j].getCount())
			{
				swap(pqArray[i], pqArray[j]);
				i = j;
			}
			else if (pqArray[i].getCount() == pqArray[j].getCount())
			{
				if (pqArray[i].getItem().size() < pqArray[j].getItem().size())
				{
					swap(pqArray[i], pqArray[j]);
					i = j;
				}
				else if (pqArray[i].getItem().size() == pqArray[j].getItem().size())
				{
					if (pqArray[i].getItem() < pqArray[j].getItem())
					{
						swap(pqArray[i], pqArray[j]);
						i = j;
					}
				}
			}
		}

		if (pqArray[i].getCount() == 0)
			size--;
	}

	return true;
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
				pqArrayAdd(pqItems, size, aWord);
			}

			for (i = 0; i < size; i++)
				displayWordCount(pqItems[i]);

			cout << endl;
		}
		else if (sInput == "R" || sInput == "r")
		{
			if (!pqArrayRemove(pqItems, size))
				cout << "PQ is empty!" << endl;
			else if (size == 0)
				cout << "Last word deleted!" << endl;
			else
			{
				for (i = 0; i < size; i++)
					displayWordCount(pqItems[i]);

				cout << endl;
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

int findMinimumWeight(int **matrixGraph, int numVertices) //* add your code here
{
	int minEdge = INT_MAX;

	for (size_t i = 0; i < numVertices - 1; i++)
	{
		for (size_t j = i + 1; j < numVertices; j++)
		{
			if (minEdge > matrixGraph[i][j])
				minEdge = matrixGraph[i][j];
		}
	}

	return minEdge;
}

void updateWeight(int **matrixGraph, int numVertices, int vertexNo1, int vertexNo2, int weight) //* add your code here
{
	if (vertexNo1 != vertexNo2 && vertexNo1 < numVertices && vertexNo2 < numVertices)
	{
		matrixGraph[vertexNo1][vertexNo2] = weight;
		matrixGraph[vertexNo2][vertexNo1] = weight;
	}
	return;
}

void removeEdge(int **matrixGraph, int numVertices, int vertexNo1, int vertexNo2) //* add your code here
{
	if (vertexNo1 != vertexNo2 && vertexNo1 < numVertices && vertexNo2 < numVertices)
	{
		matrixGraph[vertexNo1][vertexNo2] = INT_MAX;
		matrixGraph[vertexNo2][vertexNo1] = INT_MAX;
	}
	return;
}

int countEdges(int **matrixGraph, int numVertices) //* add your code here
{
	int count = 0;

	for (size_t i = 0; i < numVertices - 1; i++)
	{
		for (size_t j = i + 1; j < numVertices; j++)
		{
			if (matrixGraph[i][j] != INT_MAX)
				count++;
		}
	}

	return count;
}
void doQ2()
{
	string sInput;
	int numVertices, u, v, weight, vertexNo, vertexStartNo;

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
		input("\nEnter command: C to count edges, M to find minimum weight, R to remove edge, U to update weight, or X to Exit", sInput);

		if (sInput == "C" || sInput == "c")
			cout << "The number of edges is " << countEdges(matrixGraph, numVertices) << endl;
		else if (sInput == "M" || sInput == "m")
			cout << "The minimum edge weight is " << findMinimumWeight(matrixGraph, numVertices) << endl;
		else if (sInput == "R" || sInput == "r")
		{
			int vertexNo1, vertexNo2, weight;

			input("Enter vertex1 no: ", vertexNo1);
			input("Enter vertex1 no: ", vertexNo2);
			removeEdge(matrixGraph, numVertices, vertexNo1, vertexNo2);

			cout << "The graph after removing edge\r\n";
			showAdjMatrix(matrixGraph, numVertices);
			cout << "The number of edges is " << countEdges(matrixGraph, numVertices) << endl;
			cout << "The minimum edge weight is " << findMinimumWeight(matrixGraph, numVertices) << endl;
		}
		else if (sInput == "u" || sInput == "U")
		{
			int vertexNo1, vertexNo2, weight;
			input("Enter vertex1 no: ", vertexNo1);
			input("Enter vertex1 no: ", vertexNo2);
			input("Enter new weight: ", weight);
			updateWeight(matrixGraph, numVertices, vertexNo1, vertexNo2, weight);

			cout << "The graph after updating edge weight:\r\n";
			showAdjMatrix(matrixGraph, numVertices);
			cout << "The number of edges is " << countEdges(matrixGraph, numVertices) << endl;
			cout << "The minimum edge weight is " << findMinimumWeight(matrixGraph, numVertices) << endl;
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

void display(BinaryNode<int> &aNode)
{
	cout << aNode.getItem() << "  ";
}

void doQ3()
{
	string sInput, aString, aLine;
	BinarySearchTree<int> myBST;
	int key;

	while (1)
	{
		input("\nEnter command: A to Add, T for isAllTwoChildren, N for nodesOfTwoChildren, C to Clear, or X to Exit", sInput);

		if (sInput == "A" || sInput == "a")
		{
			while (true)
			{
				cout << "Enter a value, 0 to end: ";
				cin >> key;

				if (key == 0)
					break;

				myBST.add(key);
			}

			cout << endl
				 << "The inoder traversal of the BST is " << endl;
			myBST.inorderTraverse(display);
			cout << endl;
		}
		else if (sInput == "T" || sInput == "t")
		{
			input("Enter a value: ", key);

			if (myBST.isAllTwoChildrenR(key))
				cout << endl
					 << "R: " << key << " and it's decendent have two children." << endl;
			else
				cout << endl
					 << "R: " << key << " or it's decendent do not have two children." << endl;

			if (myBST.isAllTwoChildrenI(key))
				cout << endl
					 << "I: " << key << " and it's decendent have two children.";
			else
				cout << endl
					 << "I: " << key << " or it's decendent do not have two children." << endl;
		}
		else if (sInput == "N" || sInput == "n")
		{
			cout << endl
				 << "I: Number of the nodes with two children is " << myBST.nodesOfTwoChildrenI();
			cout << endl
				 << "R: Number of the nodes with two children is " << myBST.nodesOfTwoChildrenR() << endl;
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
