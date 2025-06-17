#pragma once
#include<iostream>
#include <utility>
enum Color
{
	Red,
	Black
};
template<class K,class V>
struct TreeNode
{
	Color _col;
    TreeNode<K,V>* _parent;
    TreeNode<K,V>* _left;
    TreeNode<K,V>* _right;
    std::pair<K, V> _kv;
    TreeNode(const std::pair<K,V>& kv)
        : _kv()
        , _left(nullptr)
        , _right(nullptr)
        , _col(Red)
    {
    }
};
template<class K,class V>
class RBtree
{
    typedef TreeNode<K, V> Node;

private:
    Node* _root=nullptr;

public:
    bool Insert(const std::pair<K,V>& kv)
    {
        if (_root == nullptr)
        {
            _root = new Node(kv);
            _root->_col = Black;//���ڵ�ֱ��Ϊ��ɫ
            return true;
        }
        Node* cur = _root;
        Node* parent=nullptr;
        while (cur)
        {
            if (_root->_kv.first > kv.first) {
                parent = cur;
                cur = cur->_left;
            } else if (_root->_kv.first < kv.first) {
                parent = cur;
                cur = cur->_right;
            } else {
                return false;
            }
        }
        
        cur = new Node(kv);
        cur->_col = Red;
        if (parent->_kv.first < kv.first)
        {
            parent->_right = cur;
        }
        else
        {
            parent->_left = cur;
        }
        cur->_parent = parent;
        while (parent && parent->_col == Red)//�����׵���ɫʱ��ɫʱ�ͽ�����
        {
            Node* grandparent = parent->_parent;
            if (parent == grandparent->_left)
            {
                Node* uncle = grandparent->_right;
                if (uncle && uncle->_col == Red)//���������Ϊ�죬��ɫ����
                {
                    uncle->_col=Black;
                    grandparent->_col = Red;
                    cur=parent;
                    parent = cur->_parent;
                }
                else//���岻���ڻ��ߴ�����Ϊ�ڣ�����+��ɫ
                {
                    parent->_col=Black;
                    if (cur == parent->_left)
                    {
                        RotateR(grandparent);
                        parent->_col=Black;
                        grandparent->_col = Red;
                    }
                    else
                    {
                        RotateL(cur);
                        RotateR(grandparent);
                        cur->_col=Black;
                        grandparent->_col = Red;
                    }
                    break;
                }
            }
            else
            {
                Node* uncle = grandparent->_left;
                if (uncle && uncle->_col == Red)//���������Ϊ�죬��ɫ����
                {
                    uncle->_col = Black;
                    grandparent->_col = Red;
                    cur = parent;
                    parent = cur->_parent;
                }
                else//���岻���ڻ��ߴ�����Ϊ�ڣ�����+��ɫ
                {
                    parent->_col = Black;
                    if (cur == parent->_left) {
                        RotateL(grandparent);
                        parent->_col = Black;
                        grandparent->_col = Red;
                    } else {
                        RotateR(cur);
                        RotateL(grandparent);
                        cur->_col = Black;
                        grandparent->_col = Red;
                    }
                    break;
                }
            }
            
        }
        return true;
    }
};