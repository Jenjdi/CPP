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
    bool check(Node* root,int blacknum,int refNum)
    {
        if (root == nullptr)
            return true;
        if (root->_col == Black)
            blacknum++;
        return check(root->_left, blacknum, refNum) && check(root->_right, blacknum, refNum);
    }
    
public:
    bool isbalance()
    {
        if (_root==Red)
        {
            return false;
        }
        int refNum = 0;
        Node* cur = _root;
        while (cur)
        {
            if (cur->_col == Black)
            {
                refNum++;
            }
        }
        return check(_root, 0, refNum);

    }
    bool Insert(const std::pair<K,V>& kv)
    {
        if (_root == nullptr)
        {
            _root = new Node(kv);
            _root->_col = Black;//根节点直接为黑色
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
        while (parent && parent->_col == Red)//当父亲的颜色时黑色时就结束了
        {
            Node* grandparent = parent->_parent;
            if (parent == grandparent->_left)
            {
                Node* uncle = grandparent->_right;
                if (uncle && uncle->_col == Red)//叔叔存在且为红，变色即可
                {
                    uncle->_col=Black;
                    grandparent->_col = Red;
                    cur=grandparent;
                    parent = cur->_parent;
                }
                else//叔叔不存在或者存在且为黑，右旋+变色
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
                if (uncle && uncle->_col == Red)//叔叔存在且为红，变色即可
                {
                    uncle->_col = Black;
                    grandparent->_col = Red;
                    cur = grandparent;
                    parent = cur->_parent;
                }
                else//叔叔不存在或者存在且为黑，右旋+变色
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
    void RotateL(Node* parent)
    {
        Node* subR = parent->_right;
        Node* subRL=subR->_left;
        Node* grandparent = parent->_parent;
        subR->_left=parent;
        parent->_parent = subR;
        parent->_right = subRL;
        if (subRL)
        {
            subRL->_parent = parent;
        }
        subR->_parent = grandparent;
        if (parent == _root)
        {
            _root = subR;
        }
        else
        {
            if (parent == grandparent->_left)
            {
                grandparent->_left = subR;
            }
            else
            {
                grandparent->_right = subR;
            }
        }
    }
    void RotateR(Node* parent)
    {
        Node* subL=parent->_left;
        Node* subLR = subL->_right;
        Node* grandparent = parent->_parent;
        subL->_right = parent;
        parent->_parent=subL;
        parent->_left=subLR;
        if (subLR)
        {
            subLR->_parent = parent;
        }
        subL->_parent = grandparent;
        if (parent == _root)
        {
            _root = subL;
        }
        else
        {
            if (parent == grandparent->_left) {
                grandparent->_left = subL;
            } else {
                grandparent->_right = subL;
            }
        }
    }
    
};