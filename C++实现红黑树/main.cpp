#include <iostream>
#include "red-black-tree.h"

using namespace std;
using namespace RedBlackTree;
int main() {
	RBTree<int, char>* tree = new RBTree<int, char>();
	//tree->DeleteMin();
	tree->Insert(1,'a');
	tree->Insert(4, 'd');
	tree->Insert(2, 'b');
	tree->Insert(7, 'e');
	tree->Insert(5, 'h');
	tree->Insert(3, 'f');
    cout<<(tree->Search(tree->GetRoot(),4))->val<<endl;
	tree->Print();
	tree->DeleteMin();
	tree->DeleteNode(7);
	delete tree;
	cout << "hello world!" << endl;
	system("pause");
	return 0;
}