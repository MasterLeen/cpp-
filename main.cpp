#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include "binary-tree.h"
using namespace std;
using namespace teaching_test;
int main()
{
	ifstream ifs("input.data");
	vector<int> m_vec;
	int i;
	while (ifs >> i)
		m_vec.push_back(i);
	ifs.close();
	BinaryTree* obj = BinaryTree::GetObject();
	int tmp = -1;
	/*obj->CreateBinary(m_vec,tmp);
	obj->PreOrder();*/

	vector<int> m_vec1 = {5,2,6,9,3};
	obj->CreateVer2(m_vec);
	obj->InsertFunc(m_vec1);
	obj->PreOrder();
	obj->InOrder();
	obj->PostOrder();
	obj->ReverseOrder();
	cout << "tree height = "<<obj->GetTreeHeight(obj->GetRoot())<<endl;

	obj->HuffmanTree(m_vec1);
	obj->PreHuffCode(obj->GetHuffmanRoot());
	
	obj->Destroy();

	system("pause");
	return 0;
}