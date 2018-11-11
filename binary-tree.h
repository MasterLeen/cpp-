#pragma once
#include <vector>
namespace teaching_test {

	template<typename T>
	struct bnode {
		T data;
		std::string code = {};
		struct bnode* lchild = nullptr;
		struct bnode* rchild = nullptr;
		~bnode() { std::cout << "调用析构" << std::endl; };
	};
	typedef bnode<int> bnode_type;
	class BinaryTree
	{
	public:
		static BinaryTree* GetObject();//单例模式
		void Destroy();

		bnode_type* CreateBinary(std::vector<int>& m_vec,int& tmp);//先序遍历创建树

		void CreateVer2(std::vector<int>& m_vec);//排序法建立二叉树

		void PreOrder();//先序遍历
		void InOrder();//中序遍历
		void PostOrder();//后序遍历

		bnode_type* GetRoot() { return root; };
		void InsertFunc(std::vector<int>& m_vec);
		int GetTreeHeight(bnode_type* node);//获得树的深度
		void ReverseOrder();//二叉排序树反序输出

		void HuffmanTree(std::vector<int>& m_vec);
		bnode_type* GetHuffmanRoot() { return m_huffrootvec[0]; };//获取huffman树根节点的接口函数
		void PreHuffCode(bnode_type* huffnode);//先序遍历输出Huffman对应权值的编码
	private:
		void CreateBinaryVer2(bnode_type* node,const int& m_tmp);
		void Pre_Order(bnode_type* node);
		void In_Order(bnode_type* node);
		void Post_Order(bnode_type* node);
		void Reverse_Order(bnode_type* node);
		void HuffmanBuild();
		static bool LowerWeight(bnode_type* a,bnode_type* b);//标准库规定sort中的比较函数需为静态函数或全局函数，sort无法将参数传入this指针指向的函数
	protected:
		explicit BinaryTree();
		~BinaryTree();//阻止栈上创建对象

	private:	
		bnode_type* root;//根节点
		std::vector<bnode_type*> m_huffrootvec;
	};

}//teaching_test