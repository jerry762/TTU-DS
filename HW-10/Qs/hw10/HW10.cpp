// HW10.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "BinaryNodeTree.h"

void display(int& anItem)
{
	cout << anItem << ' ';
}

int _tmain(int argc, _TCHAR* argv[])
{
   BinaryNodeTree<int> tree1, binTree, leftSubtree, rightSubtree; // empty trees

   for ( int i = 1; i < 5; i ++ ) {
		binTree.add( i + 5 );
		cout << "Inorder traversal: ";
		binTree.inorderTraverse( display );
		cout << endl;

		cout << "Height: " << binTree.getHeight();
		cout << "  Count: " << binTree.getNumberOfNodes();
		cout << "  Maximum: " << binTree.getMaximum();
		cout << "  HighestFullLevel: " << binTree.getHighestFullLevel() << endl;
		cout << endl;

		binTree.add( i );
		cout << "Inorder traversal: ";
		binTree.inorderTraverse( display );
		cout << endl;

		cout << "Height: " << binTree.getHeight();
		cout << "  Count: " << binTree.getNumberOfNodes();
		cout << "  Maximum: " << binTree.getMaximum();
		cout << "  HighestFullLevel: " << binTree.getHighestFullLevel() << endl;
		cout << endl;
   }

	return 0;
}

