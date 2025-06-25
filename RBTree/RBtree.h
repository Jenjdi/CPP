#pragma once
#include <iostream>
#include <utility>
#include<algorithm>
enum Color {
    Red,
    Black
};
template <class T>
struct TreeNode {
    Color _col;
    TreeNode<T>* _parent;
    TreeNode<T>* _left;
    TreeNode<T>* _right;
    T _data;
    TreeNode(const T& data)
        : _data(data)
        , _left(nullptr)
        , _right(nullptr)
        , _parent(nullptr)//别忘了把parent结点也置空，防止后续判定时出现异常
        , _col(Red)
    {
    }
};
template<class T,class Ref,class Ptr>
struct __RBIterator
{
    typedef TreeNode<T> Node;
    typedef __RBIterator<T, Ref, Ptr> Self;
    Node* _node;
    __RBIterator(Node* node)
        : _node(node)
    {
    }
    Ref operator*()
    {
        return _node->_data;
    }
    Ptr operator->()
    {
        return &_node->_data;
    }
    bool operator!=(const Self& s)
    {
        return _node != s._node;
    }
    bool operator==(const Self& s)
    {
        return _node == s._node;
    }
    Self& operator++()
    {
        if (_node->_right) {
            // 下一个，右树最左节点
            Node* leftMin = _node->_right;
            while (leftMin->_left) {
                leftMin = leftMin->_left;
            }

            _node = leftMin;
        } else {
            // 下一个，孩子等于父亲左的那个祖先
            Node* cur = _node;
            Node* parent = cur->_parent;
            while (parent && cur == parent->_right) {
                cur = parent;
                parent = parent->_parent;
            }

            _node = parent;
        }

        return *this;
    }
    Self& operator--()
    {
        if (_node->_left)
        {
            Node* leftMax = _node->_left;
            while (leftMax->_right)
            {
                leftMax = leftMax->_right;
            }
            _node = leftMax;
        }
        else
        {
            _node = _node->_parent;
        }
        return _node;
    }
    
};

template<class K, class T, class KeyofT>
class RBtree {
    typedef TreeNode<T> Node;
    

private:
    Node* _root = nullptr;
    
    bool check(Node* root, int blacknum, int refNum)
    {
        if (root == nullptr)
            return true;
        if (root->_col == Black)
            blacknum++;
        return check(root->_left, blacknum, refNum) && check(root->_right, blacknum, refNum);
    }
    Node* Copy(Node* root)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        Node* newroot = new Node(root->_data);
        newroot->_col = root->_col;
        newroot->_left=Copy(root->_left);
        if (newroot->_left)
            newroot->_left->_parent = newroot;
        newroot->_left=Copy(root->_right);
        if (newroot->_right)
            newroot->_right->_parent = newroot;
        return newroot;
    }
    void Delete(Node* root)
    {
        if (root == nullptr)
        {
            return;
        }
        Delete(root->_left);
        Delete(root->_right);
        delete root;
        root = nullptr;
    }
public:
    typedef __RBIterator<T, T&, T*> iterator;
    typedef __RBIterator<T, T&, T*> const_iterator;
    const_iterator begin() const
    {
        Node* leftMin = _root;
        while (leftMin&&leftMin->_left)
        {
            leftMin = leftMin->_left;
        }
        return const_iterator(leftMin);
    }
    iterator begin()
    {
        Node* leftMin = _root;
        while (leftMin && leftMin->_left)
        {
            leftMin = leftMin->_left;
        }
        return iterator(leftMin);
    }
    iterator end()
    {
        return iterator(nullptr);
    }
    const_iterator end() const
    {
        return const_iterator(nullptr);
    }
    bool isbalance()
    {
        if (_root == Red) {
            return false;
        }
        int refNum = 0;
        Node* cur = _root;
        while (cur) {
            if (cur->_col == Black) {
                refNum++;
            }
        }
        return check(_root, 0, refNum);
    }
    RBtree() = default;
    RBtree(const RBtree& t)
    {
        _root = Copy(t._root);
    }
    ~RBtree()
    {
        Delete(_root);
        _root = nullptr;
    }
    RBtree<K, T, KeyofT>& operator=(const RBtree<K, T, KeyofT>& t)
    {
        std::swap(_root, t._root);
        return this;
    }
    std::pair<iterator,bool> Insert(const T& data)
    {
        if (_root == nullptr) {
            _root = new Node(data);
            _root->_col = Black; // 根节点直接为黑色
            return std::make_pair(iterator(_root), true);
        }
        KeyofT kot;
        Node* cur = _root;
        Node* newnode = cur;
        Node* parent = nullptr;
        while (cur) {
            if (kot(_root->_data) > kot(data)) {
                parent = cur;
                cur = cur->_left;
            } else if (kot(_root->_data) < kot(data)) {
                parent = cur;
                cur = cur->_right;
            } else {
                return std::make_pair(iterator(newnode), true);
            }
        }

        cur = new Node(data);
        cur->_col = Red;
        if (kot(parent->_data) < kot(data)) {
            parent->_right = cur;
        } else {
            parent->_left = cur;
        }
        cur->_parent = parent;
        while (parent && parent->_col == Red) // 当父亲的颜色时黑色时就结束了
        {
            Node* grandparent = parent->_parent;
            if (parent == grandparent->_left) {
                Node* uncle = grandparent->_right;
                if (uncle && uncle->_col == Red) // 叔叔存在且为红，变色即可
                {
                    parent->_col=uncle->_col = Black;
                    grandparent->_col = Red;
                    cur = grandparent;
                    parent = cur->_parent;
                } else // 叔叔不存在或者存在且为黑，右旋+变色
                {
                    if (cur == parent->_left) {
                        RotateR(grandparent);
                        parent->_col = Black;
                        grandparent->_col = Red;
                    } else {
                        RotateL(cur);
                        RotateR(grandparent);
                        cur->_col = Black;
                        grandparent->_col = Red;
                    }
                    break;
                }
            } else {
                Node* uncle = grandparent->_left;
                if (uncle && uncle->_col == Red) // 叔叔存在且为红，变色即可
                {
                    parent->_col = uncle->_col = Black;
                    grandparent->_col = Red;
                    cur = grandparent;
                    parent = cur->_parent;
                } else // 叔叔不存在或者存在且为黑，右旋+变色
                {
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
        return std::make_pair(iterator(newnode), true);
    }
    /*void RotateL(Node* parent)
    {
        Node* subR = parent->_right;
        Node* subRL = subR->_left;
        Node* grandparent = parent->_parent;
        subR->_left = parent;
        parent->_parent = subR;
        parent->_right = subRL;
        if (subRL) {
            subRL->_parent = parent;
        }
        subR->_parent = grandparent;
        if (parent == _root) {
            _root = subR;
            _root->_parent = nullptr;
        } else {
            if (parent == grandparent->_left) {
                grandparent->_left = subR;
            } else {
                grandparent->_right = subR;
            }
        }
    }
    void RotateR(Node* parent)
    {
        Node* subL = parent->_left;
        Node* subLR = subL->_right;
        Node* grandparent = parent->_parent;
        subL->_right = parent;
        parent->_parent = subL;
        parent->_left = subLR;
        if (subLR) {
            subLR->_parent = parent;
        }
        subL->_parent = grandparent;
        if (parent == _root) {
            _root = subL;
            _root->_parent = nullptr;
        } else {
            if (parent == grandparent->_left) {
                grandparent->_left = subL;
            } else {
                grandparent->_right = subL;
            }
        }
    }*/
    void RotateR(Node* parent)
    {
        Node* subL = parent->_left;
        Node* subLR = subL->_right;

        parent->_left = subLR;
        if (subLR)
            subLR->_parent = parent;

        subL->_right = parent;

        Node* ppNode = parent->_parent;
        parent->_parent = subL;

        if (parent == _root) {
            _root = subL;
            _root->_parent = nullptr;
        } else {
            if (ppNode->_left == parent) {
                ppNode->_left = subL;
            } else {
                ppNode->_right = subL;
            }

            subL->_parent = ppNode;
        }
    }

    void RotateL(Node* parent)
    {
        Node* subR = parent->_right;
        Node* subRL = subR->_left;

        parent->_right = subRL;
        if (subRL)
            subRL->_parent = parent;

        subR->_left = parent;
        Node* ppNode = parent->_parent;

        parent->_parent = subR;

        if (parent == _root) {
            _root = subR;
            _root->_parent = nullptr;
        } else {
            if (ppNode->_right == parent) {
                ppNode->_right = subR;
            } else {
                ppNode->_left = subR;
            }
            subR->_parent = ppNode;
        }
    }
};
//#include<iostream>
//enum Color {
//    Black,
//    Red
//};
//template<class T>
//struct TreeNode
//{
//    TreeNode<T>* _left;
//    TreeNode<T>* _right;
//    TreeNode<T>* _parent;
//    Color _col;
//    T _data;
//    TreeNode(const T& data)
//        : _left(nullptr)
//        , _right(nullptr)
//        , _parent(nullptr)
//        , _col(Red)
//        , _data(data)
//    {
//    }
//};
//template<class K,class T,class KoT>
//class RBtree
//{
//    typedef TreeNode<T> Node;
//
//private:
//    Node* _root;
//    KoT _kot;
//
//public:
//    bool insert(const T& data)
//    {
//        if (_root == nullptr)
//        {
//            _root = new TreeNode<T>(data);
//            _root->_col = Black;
//            return true;
//        }
//        
//        Node* cur = _root;
//        Node* parent=nullptr;
//        while (cur)
//        {
//            if (_kot(cur->_data) > _kot(data))
//            {
//                parent = cur;
//                cur = cur->_left;
//            }
//            else if (_kot(cur->_data) < _kot(data))
//            {
//                parent = cur;
//                cur = cur->_right;
//            }
//            else
//            {
//                return false;
//            }
//        }
//        cur = new Node(data);
//        cur->_parent = parent;
//        if (parent->_left == cur)
//        {
//            parent->_left = cur;
//        }
//        else
//        {
//            parent->_right = cur;
//        }
//        while (parent && parent->_col != Black)
//        {
//            Node* grandparent = parent->_parent;
//            if (grandparent->_left == parent)
//            {
//                //叔叔存在且为红
//                Node* uncle = grandparent->_right;
//                if (uncle && uncle->_col == Red)
//                {
//                    parent->_col = uncle->_col = Black;
//                    grandparent->_col = Red;
//                    cur = grandparent;
//                    parent = cur->_parent;
//                }
//                else//叔叔不存在或者叔叔为黑
//                {
//                    if (cur == parent->_left)
//                    {
//                        RotateR(grandparent);
//
//                    }
//                }
//            }
//            else
//            {
//
//            }
//        }
//    }
//
//};