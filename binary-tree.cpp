#include "binary-tree.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <assert.h>

namespace teaching_test {

	BinaryTree::BinaryTree():root(nullptr){
	}

	BinaryTree * BinaryTree::GetObject()
	{
		return new BinaryTree();
	}

	void BinaryTree::Destroy()
	{
		delete this->root;
		if (!m_huffrootvec.empty()) {
			assert(m_huffrootvec.size() == 1);
			delete *m_huffrootvec.begin();
		}
		delete this;	
	}

	bnode_type * BinaryTree::CreateBinary(std::vector<int>& m_vec,int& tmp)
	{
		tmp++;
		bnode_type* node = nullptr;//需初始化为空指针，否则会调用无参构造函数
		if ((unsigned)tmp < m_vec.size()) {
			node = new bnode_type;
			node->data = m_vec[tmp];
			if (this->root == nullptr)
				this->root = node;
			node->lchild = CreateBinary(m_vec, tmp);
			node->rchild = CreateBinary(m_vec,tmp);
		}
		return node;
	}

	void BinaryTree::CreateVer2(std::vector<int>& m_vec)
	{
		if (m_vec.size() < 1)
			return;
		std::vector<int>::iterator iter = m_vec.begin();
		root = new bnode_type;
		root->data = *m_vec.begin();
		iter++;
		bnode_type* node;
		for (; iter != m_vec.end(); iter++) {
			node = root;
   			CreateBinaryVer2(node,*iter);
		}	
	}

	void BinaryTree::PreOrder()
	{
		std::cout << "先序遍历结果："<<std::endl;
		Pre_Order(root);
		std::cout << std::endl;
	}

	void BinaryTree::InOrder()
	{
		std::cout << "中序遍历结果：" << std::endl;
		In_Order(root);
		std::cout << std::endl;
	}

	void BinaryTree::PostOrder()
	{
		std::cout << "后序遍历结果：" << std::endl;
		Post_Order(root);
		std::cout << std::endl;
	}

	void BinaryTree::InsertFunc(std::vector<int>& m_vec)
	{
		if(this->root == nullptr)
			CreateVer2(m_vec);
		else {
			std::vector<int>::iterator iter = m_vec.begin();
			for (;iter!=m_vec.end();iter++) {
				CreateBinaryVer2(root, *iter);
			}
		}
	}

	int BinaryTree::GetTreeHeight(bnode_type* node)
	{
		if (node == nullptr)
			return 0;
		int lheight = GetTreeHeight(node->lchild);
		int rheight = GetTreeHeight(node->rchild);
		return lheight > rheight ? ++lheight : ++rheight;
	}

	void BinaryTree::ReverseOrder()
	{
		std::cout << "反序遍历结果是：" << std::endl;
		Reverse_Order(root);
		std::cout<<std::endl;
	}

	void BinaryTree::HuffmanTree(std::vector<int>& m_vec)
	{
		sort(m_vec.begin(),m_vec.end());
		for (unsigned int i = 0; i < m_vec.size(); i++) {
			bnode_type* node = new bnode_type;
			node->data = m_vec[i];
			m_huffrootvec.push_back(node);
		}
		HuffmanBuild();
	}

	void BinaryTree::PreHuffCode(bnode_type * huffnode)
	{
		if (huffnode != nullptr) {
			if(huffnode->lchild == nullptr && huffnode->rchild == nullptr)
				std::cout << "权值：" << huffnode->data << '\t' << "编码：" << huffnode->code << std::endl;
			if (huffnode->lchild != nullptr) {
				huffnode->lchild->code = huffnode->code + '0';
				PreHuffCode(huffnode->lchild);
			}
			if (huffnode->rchild != nullptr) {
				huffnode->rchild->code = huffnode->code + '1';
				PreHuffCode(huffnode->rchild);
			}
			
		}
	}

	void BinaryTree::CreateBinaryVer2(bnode_type* node,const int& m_tmp)
	{
		if (m_tmp < node->data) {
			if (node->lchild == nullptr) {
				node->lchild = new bnode_type;
				node->lchild->data = m_tmp;
				return;
			}
			else
				CreateBinaryVer2(node->lchild, m_tmp);
		}
			
		else if (m_tmp > node->data) {
			if (node->rchild == nullptr) {
				node->rchild = new bnode_type;
				node->rchild->data = m_tmp;
				return;
			}
			else
				CreateBinaryVer2(node->rchild,m_tmp);
		}			
	}

	void BinaryTree::Pre_Order(bnode_type * node)
	{
		if (node != nullptr) {
			std::cout << node->data << '\t';
			Pre_Order(node->lchild);
			Pre_Order(node->rchild);
		}
	}

	void BinaryTree::In_Order(bnode_type * node)
	{
		if (node != nullptr) {
			In_Order(node->lchild);
			std::cout << node->data << '\t';
			In_Order(node->rchild);
		}
	}

	void BinaryTree::Post_Order(bnode_type * node)
	{
		if (node != nullptr) {
			Post_Order(node->lchild);
			Post_Order(node->rchild);
			std::cout << node->data << '\t';
		}
	}

	void BinaryTree::Reverse_Order(bnode_type * node)
	{
		if (node != nullptr) {
			Reverse_Order(node->rchild);
			std::cout << node->data << '\t';
			Reverse_Order(node->lchild);
		}
	}

	void BinaryTree::HuffmanBuild()
	{
		std::vector<bnode_type*>::iterator iter = m_huffrootvec.begin();
		if(m_huffrootvec.size() > 1) {
			bnode_type* fnode = new bnode_type;
			fnode->lchild = *iter;
			iter = m_huffrootvec.erase(iter);
			fnode->rchild = *iter;
			iter = m_huffrootvec.erase(iter);
			fnode->data = fnode->lchild->data + fnode->rchild->data;
			m_huffrootvec.insert(m_huffrootvec.begin(),fnode);
			std::sort(m_huffrootvec.begin(),m_huffrootvec.end(),&LowerWeight);
			HuffmanBuild();
		}
	}

	bool BinaryTree::LowerWeight(bnode_type * a, bnode_type * b)
	{
		return a->data < b->data;
	}

	BinaryTree::~BinaryTree()
	{
	}
	
}//teaching_test