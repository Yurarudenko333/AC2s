#include<iostream>
#include"RB_Tree.h"
using std::cout;
int main()
{
	RB_Tree tree;

	tree.Insert(7);
	tree.Print();

	tree.Insert(6);
	tree.Insert(5);
	tree.Insert(4);
	tree.Insert(3);
	tree.Insert(2);
	tree.Insert(1);
	tree.Print();

	cout << tree.Search(3) << "\n";
	system("pause");
	return 0;
}