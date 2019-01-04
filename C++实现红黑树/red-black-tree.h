/*
*authored by xlfu 1/9/2019
*/
#pragma once
#include <assert.h>
#include <exception>
#include <stdexcept>
#include <queue>
namespace RedBlackTree {

	struct MyException :public std::exception {
		const char* what() const throw(std::invalid_argument) {
			return "called func with invalid parameter!";
		}
	};
	enum RBTColor
	{
		RED = 0,
		BLACK
	};

	template <typename T1, typename T2>
	struct RBTNode {
		RBTColor color;
		T1 key;
		T2 val;
		RBTNode* right;
		RBTNode* left;
		RBTNode(T1 _key, T2 _val, RBTColor _c, RBTNode* _l, RBTNode* _r)
			:key(_key), val(_val), color(_c), right(_r), left(_l) {}
	};

	template <typename T1, typename T2>
	class RBTree {
	public:
		explicit RBTree();
		~RBTree();
		RBTNode<T1, T2>* GetRoot() { return this->root; }
		void Print();//打印红黑树
		RBTNode<T1, T2>* Search(RBTNode<T1, T2>* _root, T1 key);//递归查找键值为key的节点
		RBTNode<T1, T2>* rotateLeft(RBTNode<T1, T2>* x);//左旋
		RBTNode<T1, T2>* rotateRight(RBTNode<T1, T2>* x);//右旋
		void FlipColors(RBTNode<T1, T2>* x);//颜色转换
		void FlipCorInDele(RBTNode<T1, T2>* x);//删除节点过程中的颜色转换，需要考虑将二节点扩充为三节点或四节点
		void Insert(const T1 &k, const T2 &v);//红黑树插入算法
		void DeleteMin();//删除最小键
		void DeleteNode(T1 k);//删除任意键对应的节点
	private:
		RBTNode<T1, T2>* root;
		bool isEmpty();
		bool isRed(RBTNode<T1, T2>* node);
		RBTNode<T1, T2>* Insert(RBTNode<T1, T2>* node, const T1 &k, const T2 &v);
		RBTNode<T1, T2>* DeleteMin(RBTNode<T1, T2>* x);
		RBTNode<T1, T2>* moveRedLeft(RBTNode<T1, T2>* x);//确保向下搜索的过程中将二节点扩充为3节点
		RBTNode<T1, T2>* moveRedRight(RBTNode<T1, T2>* x);
		RBTNode<T1, T2>* InverseBalance(RBTNode<T1, T2>* x);//向上分解所有临时的4节点
		RBTNode<T1, T2>* DeleteNode(RBTNode<T1, T2>* x, T1 k);
		RBTNode<T1, T2>* Successor(RBTNode<T1, T2>* x);//寻找需要删除节点的后继节点
	};

	template<typename T1, typename T2>
	inline RBTree<T1, T2>::RBTree()
	{
	}
	//层序法释放红黑树所有节点
	template<typename T1, typename T2>
	inline RBTree<T1, T2>::~RBTree()
	{
		std::queue<RBTNode<T1, T2>*> m_queue;
		m_queue.push(root);
		while (!m_queue.empty())
		{
			root = m_queue.front();
			m_queue.pop();
			if (root->left) m_queue.push(root->left);
			if (root->right) m_queue.push(root->right);
			delete root;
		}
	}
	//按层遍历打印
	template<typename T1, typename T2>
	void RBTree<T1, T2>::Print()
	{
		if (!root)
			std::cout << "This is an empty red-black tree!" << std::endl;
		else {
			std::queue<RBTNode<T1, T2>*> m_queue;
			m_queue.push(root);
			while (!m_queue.empty()) {
				int m_size = m_queue.size();
				while (m_size != 0) {
					RBTNode<T1, T2>* node = m_queue.front();
					m_queue.pop();
					if (node->left) m_queue.push(node->left);
					if (node->right) m_queue.push(node->right);
					std::cout << '<' << node->key << ',' << node->val << ">:" << (isRed(node)?"red":"black") << '\t';
					m_size--;
				}
				std::cout << std::endl;
			}
		}
	}
	template<typename T1, typename T2>
	inline RBTNode<T1, T2>* RBTree<T1, T2>::Search(RBTNode<T1, T2>* _root, T1 key)
	{
		if (!_root)
			return NULL;
		if (_root->key == key)
			return _root;
		else if (_root->key < key)
			return Search(_root->right, key);
		else
			return Search(_root->left, key);
	}
	template<typename T1, typename T2>
	inline RBTNode<T1, T2>* RBTree<T1, T2>::rotateLeft(RBTNode<T1, T2>* x)
	{
		if (!x->right)
			return x;
		RBTNode<T1, T2>* cur = x->right;
		x->right = cur->left;
		cur->left = x;
		cur->color = x->color;
		x->color = RED;
		return cur;
	}
	template<typename T1, typename T2>
	inline RBTNode<T1, T2>* RBTree<T1, T2>::rotateRight(RBTNode<T1, T2>* x)
	{
		if (!x->left)
			return NULL;
		RBTNode<T1, T2>* cur = x->left;
		x->left = cur->right;
		cur->right = x;
		cur->color = x->color;
		x->color = RED;
		return cur;
	}
	template<typename T1, typename T2>
	inline void RBTree<T1, T2>::FlipColors(RBTNode<T1, T2>* x)
	{
		x->color = RED;
		x->left->color = BLACK;
		x->right->color = BLACK;
	}
	template<typename T1, typename T2>
	inline void RBTree<T1, T2>::FlipCorInDele(RBTNode<T1, T2>* x)
	{
		x->color = x->color == 1 ? RBTColor(0) : RBTColor(1);
		x->left->color = x->left->color == 1 ? RBTColor(0) : RBTColor(1);
		x->right->color = x->right->color == 1 ? RBTColor(0) : RBTColor(1);
	}
	template<typename T1, typename T2>
	inline void RBTree<T1, T2>::Insert(const T1 &k, const T2 &v)
	{
		assert(k != NULL);
		try
		{
			if (NULL == v)
				throw MyException();
		}
		catch (const MyException& e)
		{
			std::cerr << e.what() << std::endl;
			DeleteNode(k);
		}
		root = Insert(root, k, v);
		root->color = BLACK;//点的颜根节色一定为黑
	}
	template<typename T1, typename T2>
	inline void RBTree<T1, T2>::DeleteMin()
	{
		try
		{
			if (this->isEmpty())
				throw "the tree root is nullptr!";
		}
		catch (const char* msg)
		{
			std::cerr << msg << std::endl;
			abort();
		}
		if (!isRed(root->left) && !isRed(root->right))
			root->color = RED;
		root = DeleteMin(root);
		if (!isEmpty())
			root->color = BLACK;
	}
	template<typename T1, typename T2>
	inline void RBTree<T1, T2>::DeleteNode(T1 k)
	{
		try
		{
			if (NULL == k)
				throw MyException();
			if (!Search(root, k))
				throw "emerge run time error!";
		}
		catch (const MyException& e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (const char* msg)
		{
			std::cerr << msg << std::endl;
			return;
		}
		if (!isRed(root->left) && !isRed(root->right))
			root->color = RED;
		root = DeleteNode(root, k);
		if (!isEmpty())
			root->color = BLACK;
	}
	template<typename T1, typename T2>
	inline bool RBTree<T1, T2>::isEmpty()
	{
		return root == NULL;
	}
	template<typename T1, typename T2>
	inline bool RBTree<T1, T2>::isRed(RBTNode<T1, T2>* node)
	{
		if (!node)
			return false;
		else
			return RED == node->color;
	}
	template<typename T1, typename T2>
	inline RBTNode<T1, T2>* RBTree<T1, T2>::Insert(RBTNode<T1, T2>* node, const T1 & k, const T2 & v)
	{
		if (node == NULL)
			return new RBTNode<T1, T2>(k, v, RED, NULL, NULL);
		if (k > node->key)
			node->right = Insert(node->right, k, v);
		else if (k < node->key)
			node->left = Insert(node->left, k, v);
		else
			node->val = v;
		if (isRed(node->right) && !isRed(node->left))
			node = rotateLeft(node);
		if (isRed(node->left) && isRed(node->left->left))
			node = rotateRight(node);
		if (isRed(node->left) && isRed(node->right))
			FlipColors(node);
		return node;
	}
	template<typename T1, typename T2>
	inline RBTNode<T1, T2>* RBTree<T1, T2>::DeleteMin(RBTNode<T1, T2>* x)
	{
		if (x->left == NULL)
			return NULL;
		if (!isRed(x->left) && !isRed(x->left->left))//假设节点x是红色节点
			x = moveRedLeft(x);
		x->left = DeleteMin(x->left);
		return InverseBalance(x);
	}
	template<typename T1, typename T2>
	inline RBTNode<T1, T2>* RBTree<T1, T2>::moveRedLeft(RBTNode<T1, T2>* x)
	{
		FlipCorInDele(x);
		if (isRed(x->right->left)) {
			x->right = rotateRight(x->right);
			x = rotateLeft(x);
			FlipCorInDele(x);
		}
		return x;
	}
	template<typename T1, typename T2>
	inline RBTNode<T1, T2>* RBTree<T1, T2>::moveRedRight(RBTNode<T1, T2>* x)
	{
		FlipCorInDele(x);
		if (isRed(x->left->left)) {
			x = rotateRight(x);
			FlipCorInDele(x);
		}
		return x;
	}
	template<typename T1, typename T2>
	inline RBTNode<T1, T2>* RBTree<T1, T2>::InverseBalance(RBTNode<T1, T2>* x)
	{
		if (isRed(x->right))	x = rotateLeft(x);
		if (isRed(x->left) && isRed(x->left->left))	x = rotateRight(x);
		if (isRed(x->left) && isRed(x->right))	FlipColors(x);
		return x;
	}
	template<typename T1, typename T2>
	inline RBTNode<T1, T2>* RBTree<T1, T2>::DeleteNode(RBTNode<T1, T2>* x, T1 k)
	{
		if (k < x->key) {
			if (!isRed(x->left) && !isRed(x->left->left))
				x = moveRedLeft(x);
			x->left = DeleteNode(x->left, k);
		}
		else {
			if (isRed(x->left))
				x = rotateRight(x);
			if (k == x->key && x->right == NULL)
				return NULL;
			if (!isRed(x->right) && !isRed(x->right->left))//确保向下查找时无2节点
				x = moveRedRight(x);
			if (k == x->key) {
				RBTNode<T1, T2>* node = Successor(x->right);
				x->key = node->key;
				x->val = node->val;
				x->right = DeleteMin(x->right);
			}
			else
				x->right = DeleteNode(x->right, k);
		}
		return InverseBalance(x);
	}
	template<typename T1, typename T2>
	inline RBTNode<T1, T2>* RBTree<T1, T2>::Successor(RBTNode<T1, T2>* x)
	{
		if (!x)
			return NULL;
		while (x->left)
		{
			x = x->left;
		}
		return x;
	}
}//RedBlackTree