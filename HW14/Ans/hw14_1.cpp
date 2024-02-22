// HW14.cpp : �w�q�D���x���ε{�����i�J�I�C
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <queue>
#include <stack>

#include "BFS.h"

using namespace std;

void display(int &aVertex)
{
	cout << " v" << aVertex;
}

void input(string sMessage, int &inputValue)
{
	do
	{
		cout << sMessage << endl;
		cin >> inputValue;
	} while (cin.fail());

	return;
}

void input(string sMessage, string &sInputString)
{
	do
	{
		cout << sMessage << endl;
		cin >> sInputString;
	} while (cin.fail());

	return;
}

void showAdjMatrix(int **matrixGraph, int numVertices)
{
	for (int i = 0; i < numVertices; i++)
	{
		for (int j = 0; j < numVertices; j++)
		{
			if (matrixGraph[i][j] == INT_MAX)
				cout << " - ";
			else
				cout << ' ' << matrixGraph[i][j];
		}
		cout << '\n';
	}
}

void DFS_Recu(int **matrixGraph, int numVertices, int vertexNo, bool *visited, vector<int> &parents)
{
	visited[vertexNo] = true;
	cout << " v" << vertexNo;

	for (int j = 0; j < numVertices; j++)
	{
		if (matrixGraph[vertexNo][j] < INT_MAX)
			if (!visited[j])
			{
				parents[j] = vertexNo;
				DFS_Recu(matrixGraph, numVertices, j, visited, parents);
			}
	}
}

void DFS_Iter(int **matrixGraph, int numVertices, int vertexNo, bool *visited, vector<int> &parents) //* add your code here
{
	stack<int> stack;

	stack.push(vertexNo);

	while (!stack.empty())
	{
		int top = stack.top();
		stack.pop();

		if (!visited[top])
		{
			cout << " v" << top;
			visited[top] = true;
		}

		for (int i = numVertices - 1; i >= 0; i--)
		{
			if (matrixGraph[top][i] != INT_MAX && !visited[i])
			{
				parents[i] = top;
				stack.push(i);
			}
		}
	}
}

vector<int> doDFS(int **matrixGraph, int numVertices, int vertexNo)
{
	bool *visited = new bool[numVertices];
	vector<int> parents(numVertices, -1);

	for (int i = 0; i < numVertices; i++)
		visited[i] = false;

	cout << "\nDFS:";
	DFS_Recu(matrixGraph, numVertices, vertexNo, visited, parents);

	for (int i = 0; i < numVertices; i++)
		visited[i] = false;

	cout << "\nDFS:";
	DFS_Iter(matrixGraph, numVertices, vertexNo, visited, parents);

	delete[] visited;

	return parents;
}

void doBFS(Graph &listGraph, int vertexNo)
{
	cout << "BFS:";
	BFS myBFS(listGraph);
	myBFS.startSearch(vertexNo, display);
	cout << '\n';
}

vector<int> doBFS(int **matrixGraph, int numVertices, int vertexNo) //* add your code here
{
	vector<int> parents(numVertices, -1);
	vector<bool> visited(numVertices, false);
	queue<int> queue;

	cout << "BFS: ";

	queue.push(vertexNo);
	visited[vertexNo] = true;

	while (!queue.empty())
	{
		vertexNo = queue.front();
		cout << " v" << vertexNo;
		queue.pop();

		for (size_t i = 0; i < numVertices; i++)
		{
			if (matrixGraph[vertexNo][i] < INT_MAX && !visited[i])
			{
				parents[i] = vertexNo;
				queue.push(i);
				visited[i] = true;
			}
		}
	}

	return parents;
}

bool checkCycle(int parent[], int u, int v) //* add your code here
{
	bool cycle = false;

	if (parent[v] == -1)
		parent[v] = u;
	else
	{
		int u_origin = u;
		int v_origin = v;

		while (parent[u_origin] != -1)
			u_origin = parent[u_origin];

		while (parent[v_origin] != -1)
			v_origin = parent[v_origin];

		if (u_origin == v_origin)
			cycle = true;
		else
			parent[v] = u;
	}

	return cycle;
}

bool doCheckCycles(int **matrixGraph, int numVertices)
{
	int *parent = new int[numVertices];

	for (int i = 0; i < numVertices; i++)
		parent[i] = -1;

	for (int u = 0; u < numVertices; u++)
	{
		for (int v = u + 1; v < numVertices; v++)
		{
			if (matrixGraph[u][v] < INT_MAX)
			{
				cout << "( " << u << ", " << v << " )";

				if (checkCycle(parent, u, v))
					cout << " <= cycle created!";

				cout << "\n";
			}
		}
	}

	return false;
}

void printPathRecu(int **matrixGraph, vector<int> &parents, int vertex)
{
	if (parents[vertex] != -1 && parents[vertex] != vertex)
	{
		printPathRecu(matrixGraph, parents, parents[vertex]);
		cout << " -> v" << vertex << ":" << matrixGraph[parents[vertex]][vertex];
	}
	else
		cout << 'v' << vertex;
}

void printPathIter(int **matrixGraph, vector<int> &parents, int vertex)
{
	cout << 'v' << vertex;
}

void doFindPaths(int **matrixGraph, int numVertices, int vertexStartNo, int vertexEndNo)
{
	vector<int> parents;

	parents = doBFS(matrixGraph, numVertices, vertexStartNo);

	cout << "\nPath: ";
	printPathRecu(matrixGraph, parents, vertexEndNo);
	cout << "\nPath: ";
	printPathIter(matrixGraph, parents, vertexEndNo);
	cout << '\n';

	parents = doDFS(matrixGraph, numVertices, vertexStartNo);

	cout << "\nPath: ";
	printPathRecu(matrixGraph, parents, vertexEndNo);
	cout << "\nPath: ";
	printPathIter(matrixGraph, parents, vertexEndNo);

	return;
}

int main()
{
	ifstream inFile("graph.txt", ifstream::in);
	string sInput;
	int numVertices, u, v, weight, vertexStartNo, vertexEndNo;

	if (!inFile)
	{
		cerr << "Error: Failed to open graph.txt" << endl;
		return 1;
	}
	else
	{
		cout << "Success: Succeed to open graph.txt" << endl;
	}

	if (inFile.peek() == EOF)
	{
		cerr << "Error: Empty input file! \n";
		return 1;
	}

	inFile >> numVertices;

	Graph listGraph(numVertices);
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
		{
			Edge anEdge(u, v, weight);
			listGraph.add(anEdge);
			matrixGraph[u][v] = matrixGraph[v][u] = weight;
		}
	}

	while (1)
	{
		input("\nEnter B to BFS, D to DFS, F to Find Paths, C to Check Cycles,\n      M to Find MST_K, S to Find Shortest Paths, or X to Exit", sInput);

		if (sInput == "B" || sInput == "b")
		{
			input("Enter start vertex no: ", vertexStartNo);

			if (vertexStartNo < numVertices)
			{
				doBFS(listGraph, vertexStartNo);
				doBFS(matrixGraph, numVertices, vertexStartNo);
			}
			else
				cerr << "Error: Vertex no out of range!  \n";
		}
		else if (sInput == "D" || sInput == "d")
		{
			input("Enter start vertex no: ", vertexStartNo);

			if (vertexStartNo < numVertices)
				doDFS(matrixGraph, numVertices, vertexStartNo);
			else
				cerr << "Error: Vertex no out of range!  \n";
		}
		else if (sInput == "F" || sInput == "f")
		{
			input("Enter start vertex no: ", vertexStartNo);
			input("Enter end vertex no: ", vertexEndNo);

			if (vertexStartNo < numVertices && vertexEndNo < numVertices)
			{
				//				doBFS( matrixGraph, numVertices, vertexStartNo );
				doFindPaths(matrixGraph, numVertices, vertexStartNo, vertexEndNo);
				cout << '\n';
			}
			else
				cerr << "Error: Vertex out of range!  \n";
		}
		else if (sInput == "C" || sInput == "c")
		{
			doCheckCycles(matrixGraph, numVertices);
		}
		else if (sInput == "X" || sInput == "x")
		{
			if (inFile.is_open())
				inFile.close();

			for (int i = 0; i < numVertices; i++)
				delete[] matrixGraph[i];

			delete matrixGraph;

			return 0;
		}
		else
			cout << "Unknown command!\r" << endl;
	}

	return 0;
}
