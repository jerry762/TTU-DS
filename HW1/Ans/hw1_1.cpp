// HW1.cpp : �w�q�D���x���ε{�����i�J�I�C
//
#include <iostream>
#include <string>

using namespace std;

void input(string sMessage, string &sInputString)
{
	cout << sMessage << endl;
	cin >> sInputString;

	return;
}

void writeBackwardI(string s)
{
	int length = s.size();

	if (length == 0) // base case
		return;

	for (int i = length - 1; i >= 0; i--)
		cout << s[i];
}

void writeBackwardR1(string s)
{
	int length = s.size();

	if (length == 0) // base case
		return;

	cout << s[length - 1];
	writeBackwardR1(s.substr(0, length - 1));
}

void writeBackwardR2(string s)
{
	int length = s.size();

	if (length == 0) // base case
		return;

	writeBackwardR2(s.substr(1, length - 1));
	cout << s[0];
}

int countI(string s, char c) //* add your code here
{
	int count = 0;

	for (char i : s)
	{
		if (i == c)
			count++;
	}

	return count;
}

int countR(string s, char c) //* add your code here
{
	if (s.size() == 1)
		return (s.at(0) == c) ? 1 : 0;

	return countR(s.substr(1, s.size() - 1), c) + ((s.at(0) == c) ? 1 : 0);
}

unsigned char findI(string s) //* add your code here
{
	char min = s.at(0);

	for (char i : s)
	{
		if (min > i)
			min = i;
	}

	return min;
}

char findR(string s) //* add your code here
{
	if (s.size() == 1)
		return s.at(0);

	return min(findR(s.substr(1, s.size() - 1)), s.at(0));
}

string removeI(string s) //* add your code here
{
	string str;

	for (int i = 0; i < s.size(); i++)
	{
		int repeatCount = 0;

		for (int j = i + 1; j < s.size(); j++)
		{
			if (s.at(i) == s.at(j))
				repeatCount++;
			else
				break;
		}

		str += s.substr(i, 1);

		if (repeatCount != 0)
			i += repeatCount;
	}

	return str;
}

string removeR(string s) //* add your code here
{
	if (s.size() == 1)
		return s.substr(0, 1);

	string str = removeR(s.substr(1, s.size() - 1));

	return (s.at(0) != str.at(0)) ? (s.at(0) + str) : str;
}

int TI(int m, int n) //* add your code here
{
	int value;

	for (int i = 0; i < n; i++)
		value += m;

	return value;
}

int TR(int m, int n) //* add your code here
{
	if (n == 1)
		return m;

	return TR(m, n - 1) + m;
}

int main()
{
	string commandStr;
	string inputStr, appendStr;
	char inputChr;
	int m, n;

	while (1)
	{
		input("\nEnter command: "
			  "\n I to input a string, A to append a string, B to write the string backward, "
			  "\n C to count the given character , F to find the smallest character,"
			  "\n R to remove the repeated characters, T to compute, and X to Exit",
			  commandStr);

		if (commandStr == "I" || commandStr == "i")
		{
			cout << "\nInput the string: ";
			cin >> inputStr;
		}
		else if (commandStr == "A" || commandStr == "a")
		{
			cout << "\nInput the string: ";
			cin >> appendStr;
			inputStr += appendStr;
			cout << "\nThe new string: " << inputStr << endl;
		}
		else if (commandStr == "B" || commandStr == "b")
		{
			if (inputStr.length() > 0)
			{
				cout << endl;
				writeBackwardI(inputStr);
				cout << endl;
				writeBackwardR1(inputStr);
				cout << endl;
				writeBackwardR2(inputStr);
				cout << endl;
			}
		}
		else if (commandStr == "C" || commandStr == "c")
		{
			if (inputStr != "")
			{
				cout << "\nInput the character: ";
				cin >> inputChr;
				cout << "\nCount of " << inputChr << ": " << countI(inputStr, inputChr);
				cout << "\nCount of " << inputChr << ": " << countR(inputStr, inputChr) << endl;
			}
		}
		else if (commandStr == "R" || commandStr == "r")
		{
			if (inputStr != "")
			{
				cout << endl
					 << "Repeated characters removed: " << removeI(inputStr);
				cout << endl
					 << "Repeated characters removed: " << removeR(inputStr) << endl;
			}
		}
		else if (commandStr == "F" || commandStr == "f")
		{
			if (inputStr != "")
			{
				cout << endl
					 << "Smallest character found: " << findI(inputStr);
				cout << endl
					 << "Smallest character found: " << findR(inputStr) << endl;
			}
		}
		else if (commandStr == "T" || commandStr == "t")
		{
			cout << "\nInput two values, m and n: ";
			cin >> m >> n;
			cout << endl
				 << "The result is " << TI(m, n);
			cout << endl
				 << "The result is " << TR(m, n) << endl;
		}
		else if (commandStr == "X" || commandStr == "x")
			return 0;
		else
			cout << "\nUnknown command!";
	}
	return 0;
}
