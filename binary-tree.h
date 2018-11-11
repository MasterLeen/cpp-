#pragma once
#include <vector>
namespace teaching_test {

	template<typename T>
	struct bnode {
		T data;
		std::string code = {};
		struct bnode* lchild = nullptr;
		struct bnode* rchild = nullptr;
		~bnode() { std::cout << "��������" << std::endl; };
	};
	typedef bnode<int> bnode_type;
	class BinaryTree
	{
	public:
		static BinaryTree* GetObject();//����ģʽ
		void Destroy();

		bnode_type* CreateBinary(std::vector<int>& m_vec,int& tmp);//�������������

		void CreateVer2(std::vector<int>& m_vec);//���򷨽���������

		void PreOrder();//�������
		void InOrder();//�������
		void PostOrder();//�������

		bnode_type* GetRoot() { return root; };
		void InsertFunc(std::vector<int>& m_vec);
		int GetTreeHeight(bnode_type* node);//����������
		void ReverseOrder();//�����������������

		void HuffmanTree(std::vector<int>& m_vec);
		bnode_type* GetHuffmanRoot() { return m_huffrootvec[0]; };//��ȡhuffman�����ڵ�Ľӿں���
		void PreHuffCode(bnode_type* huffnode);//����������Huffman��ӦȨֵ�ı���
	private:
		void CreateBinaryVer2(bnode_type* node,const int& m_tmp);
		void Pre_Order(bnode_type* node);
		void In_Order(bnode_type* node);
		void Post_Order(bnode_type* node);
		void Reverse_Order(bnode_type* node);
		void HuffmanBuild();
		static bool LowerWeight(bnode_type* a,bnode_type* b);//��׼��涨sort�еıȽϺ�����Ϊ��̬������ȫ�ֺ�����sort�޷�����������thisָ��ָ��ĺ���
	protected:
		explicit BinaryTree();
		~BinaryTree();//��ֹջ�ϴ�������

	private:	
		bnode_type* root;//���ڵ�
		std::vector<bnode_type*> m_huffrootvec;
	};

}//teaching_test