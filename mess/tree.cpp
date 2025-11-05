#define _CRT_SECURE_NO_WARNINGS 1
#include<time.h>
#include<stdlib.h>
#include<iostream>
#include<utility>
#include<assert.h>
#include<vector>
using namespace std;

namespace AVL
{
	template<class K, class V>
	struct AVLTreeNode
	{
		AVLTreeNode<K, V>* _left;
		AVLTreeNode<K, V>* _right;
		AVLTreeNode<K, V>* _parent;
		pair<K, V> _val;
		int _bf;

		struct AVLTreeNode(const pair<K, V>& val)
			:_val(val)
			, _left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
			,_bf(0)
		{}
	};

	

	template<class K, class V>
	struct AVLTree
	{
		typedef struct AVLTreeNode<K, V> Node;
	private:
		Node* _root = nullptr;
	public:
		//����һ������ǰ�������: "abd##e#h##cf##g##"; ǰ�������: �� ������ ������
		Node* _creattree(const char* a, int* i)
		{
			//�����'#', �����Ǿ�����
			if (a[*i] == '#')
			{
				(*i)++;
				return nullptr;
			}

			//�������'#'��, �������ȴ������, �ٽ�������. 
			Node* newnode = new Node({a[*i], a[*i]});
			(*i)++;
			newnode->_left = _creattree(a, i);
			newnode->_right = _creattree(a, i);
			if(newnode->_left)
			newnode->_left->_parent = newnode;
			if(newnode->_right)
			newnode->_right->_parent = newnode;

			return newnode;
		}
		Node* creattree(const string& s)
		{
			int i = 0;
			return _root = _creattree(s.c_str(), &i);
		}

		bool Push(const pair<K, V>& val)
		{
			if (_root == nullptr)
			{
				_root = new Node(val);
				return true;
			}

			Node* parent = _root;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_val.first < val.first)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_val.first > val.first)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					//���������Kֵ��ͬ, ���˵����ʧ��~ 
					return false;
				}
			}

			//�ߵ�����, ��ʾcur�ߵ�����, Ȼ��parentָ��Ҫ����λ�õĸ���. 
			cur = new Node(val);
			if (parent->_val.first < val.first)
			{
				parent->_right = cur;
			}
			else if (parent->_val.first > val.first)
			{
				parent->_left = cur;
			}
			else
			{
				cout << "δ֪����" << endl;
			}
			cur->_parent = parent;

			//����ƽ������~ 
			while (parent)
			{
				if (parent->_val.first > cur->_val.first) //��������, ƽ������--
				{
					parent->_bf--;
				}
				else if (parent->_val.first < cur->_val.first) //������ұ�, ƽ������++
				{
					parent->_bf++;
				}

				//���ݸ��ڵ��bf������ֱ���~ 
				if (parent->_bf == 0)
				{
					//��ʱ���½���, ֱ��break����
					break;
				}
				else if (parent->_bf == 1 || parent->_bf == -1)
				{
					//��ʱ��Ҫ����үү�Ľ��bf.
					cur = parent;
					parent = parent->_parent;
				}
				else if (parent->_bf == 2 || parent->_bf == -2)
				{
					//��ʱ��Ҫ��ת���д���~ 
					//��ת�����Ļ�, ��Ҫ���������
					if (parent->_bf == -2 && cur->_bf == -1)
					{
						if (parent->_left == nullptr)
						{
							int b = 20;
							cout << "parent->_bf == -2 && cur->_bf == -1 --> parent->_left == nullptr" << endl;
						}
						RotateR(parent);
						//cout << "RotateR();//��ʱҪ��������." << endl;
						//RotateR();//��ʱҪ��������. 
					}
					else if (parent->_bf == 2 && cur->_bf == 1)
					{
						RotateL(parent);
						//cout << "RotateL();//��ʱҪ��������." << endl;
						//RotateL();//��ʱҪ��������. 
					}
					else if (parent->_bf == -2 && cur->_bf == 1)
					{
						RotateLR(parent);
						//cout << "RotateLR();//��ʱҪ����������." << endl;
					}
					else if (parent->_bf == 2 && cur->_bf == -1)
					{
						RotateRL(parent);
						//cout << "RotateRL();//��ʱҪ����������." << endl;
					}
					else
					{
						assert(false);
						//cout << "��ת~, δ֪����~" << endl;
					}

					break;
				}//��ת
			}//����ƽ������~ 

			return true;
		}//Push

		void RotateR(Node* node)
		{
			Node* pparent = node->_parent;
			Node* parent = node;
			Node* SubL = node->_left;
			Node* SubLR = node->_left->_right;

			parent->_left = SubLR;
			if (SubLR) SubLR->_parent = parent;
			
			SubL->_right = parent;
			parent->_parent = SubL;

			if (parent == _root)
			{
				_root = SubL;
				SubL->_parent = nullptr;
			}
			else
			{
				SubL->_parent = pparent;
				
				if (pparent->_left == parent)
				{
					pparent->_left = SubL;
				}
				else
				{
					pparent->_right = SubL;
				}
			}

			parent->_bf = SubL->_bf = 0;
		}

		void RotateL(Node* node)
		{
			Node* pparent = node->_parent;
			Node* parent = node;
			Node* SubR = node->_right;
			if (SubR == nullptr) 
				int a = 10;
			Node* SubRL = node->_right->_left;

			parent->_right = SubRL;
			if (SubRL) SubRL->_parent = parent;

			SubR->_left = parent;
			parent->_parent = SubR;

			if (parent == _root)
			{
				_root = SubR;
				SubR->_parent = nullptr;
			}
			else
			{
				SubR->_parent = pparent;

				if (pparent->_left == parent)
				{
					pparent->_left = SubR;
				}
				else
				{
					pparent->_right = SubR;
				}
			}

			parent->_bf = SubR->_bf = 0;
		}

		void RotateRL(Node* node)
		{
			Node* pparent = node->_parent;
			Node* parent = node;
			Node* SubR = node->_right;
			Node* SubRL = node->_right->_left;
			int bf = SubRL->_bf;

			RotateR(SubR);
			RotateL(parent);
			SubRL->_bf = 0;

			if (bf == 1)
			{
				SubR->_bf = 0;
				parent->_bf = -1;
			}
			else if (bf == -1)
			{
				parent->_bf = 0;
				SubR->_bf = 1;
			}
			else
			{
				parent->_bf = 0;
				SubR->_bf = 0;
			}
		}

		void RotateLR(Node* node)
		{
			Node* pparent = node->_parent;
			Node* parent = node;
			Node* SubL = node->_left;
			Node* SubLR = node->_left->_right;
			int bf = SubLR->_bf;

			RotateL(SubL);
			RotateR(parent);
			SubLR->_bf = 0;

			if (bf == 1)
			{
				parent->_bf = 0;
				SubL->_bf = -1;
			}
			else if (bf == -1)
			{
				parent->_bf = 1;
				SubL->_bf = 0;
			}
			else
			{
				parent->_bf = 0;
				SubL->_bf = 0;
			}
		}

		Node* Find(const K& k)
		{
			Node* cur = _root;

			while (cur)
			{
				if (cur->_val.first == k)
				{
					return cur;
				}
				else if (cur->_val.first < k)
				{
					cur = cur->_right;
				}
				else
				{
					cur = cur->_left;
				}
			}

			return nullptr;
		}//Find

		void InOrder()
		{
			_InOrder(_root);
		}//InOrder

		void _InOrder(Node* node)
		{
			if (node == nullptr)
			{
				//cout << "N" << " ";
				return;
			}

			_InOrder(node->_left);
			cout << node->_val.first << " " << node->_val.second << endl;
			_InOrder(node->_right);
		}//_InOrder

		int Height()
		{
			return _Height(_root);
		}

		int _Height(Node* root)
		{
			if (root == nullptr) return 0;

			int left = _Height(root->_left);
			int right = _Height(root->_right);

			return (left > right ? left : right) + 1;
		}

		bool isBalance()
		{
			return _isBalance(_root);
		}

		int Size()
		{
			return _Size(_root);
		}

		int _Size(Node* root)
		{
			if (root == nullptr) return 0;

			return _Size(root->_left) + _Size(root->_right) + 1;
		}

		bool _isBalance(Node* root)
		{
			if (root == nullptr) return true;
			bool left = _isBalance(root->_left);
			bool right = _isBalance(root->_right);

			int bf = _Height(root->_right) - _Height(root->_left);
			if(abs(bf) >= 2) return false;
			if (root->_bf != bf) return false;
			
			return left && right;
		}

	};
	void TestAVLTree4()
	{
		//ע��: ��ʱAVL��������ƽ�����, ��Ϊ������ǿ������һ����~ 
		AVLTree<char, int> tree;
		string s = "abd##e#h##cf##g##";

		tree.creattree(s.c_str());
		tree.InOrder();
	}
};
int main()
{
	AVL::TestAVLTree4();
}