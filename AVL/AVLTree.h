#pragma once
#include <cassert>
#include <iostream>
#include <string>
using namespace std;
template <typename K, typename V>
struct AVLNode {
    AVLNode<K, V>* _left;
    AVLNode<K, V>* _right;
    AVLNode<K, V>* _parent;
    pair<K, V> _kv;
    int _bf;
    AVLNode(const pair<K, V>& kv)
        : _left(nullptr)
        , _right(nullptr)
        , _parent(nullptr)
        , _kv(kv)
        , _bf(0)
    {
    }
};
template <typename K, typename V>
class AVLTree {
    typedef AVLNode<K, V> Node;

private:
    Node* _root;
    void _Inorder(Node* node)
    {
        if (node == nullptr) {
            return;
        }
        _Inorder(node->_left);
        cout << node->_kv.first << " " << node->_kv.second << endl;
        _Inorder(node->_right);
    }
    int _Size(Node* root)
    {
        return root == nullptr ? 0 : _Size(root->_left) + _Size(root->_right) + 1;
    }
    void RotateL(Node* parent)
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
        } else {
            if (grandparent->_left == parent) {
                grandparent->_left = subR;
            } else {
                grandparent->_right = subR;
            }
        }

        /*if (subR->_bf == 0) {
            subR->_bf = 1;
            parent->_bf = -1;
        } else {
            subR->_bf = parent->_bf = 0;
        }*/
        subR->_bf = parent->_bf = 0;
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
        } else {
            if (grandparent->_left == parent) {
                grandparent->_left = subL;
            } else {
                grandparent->_right = subL;
            }
        }
        /*if (subL->_bf == 0) {
            subL->_bf = 1;
            parent->_bf = -1;
        } else {
            subL->_bf = parent->_bf = 0;
        }*/
        subL->_bf = parent->_bf = 0;
    }
    void RotateLR(Node* parent)
    {
        Node* subL = parent->_left;
        Node* subLR = subL->_right;
        int bf = subLR->_bf;
        RotateL(subL);
        RotateR(parent);
        if (bf == 0) {
            parent->_bf = subL->_parent->_bf = 0;
        } else if (bf == 1) {
            subL->_bf = 0;
            parent->_bf = -1;
        } else {
            parent->_bf = 0;
            subL->_bf = 1;
        }

        /*if (bf == 0) {
            parent->_bf = 0;
            subL->_bf = 0;
        } else if (bf == 1) {
            subL->_bf = -1;
            parent->_bf = 0;
        } else {
            parent->_bf = 1;
            subL->_bf = 0;
        }
        subLR->_bf = 0;*/
    }
    void RotateRL(Node* parent)
    {
        Node* subR = parent->_right;
        Node* subRL = subR->_left;
        int bf = subRL->_bf;
        RotateR(subR);
        RotateL(parent);
        if (bf == 0) {
            subR->_bf = parent->_bf = 0;
        } else if (bf == 1) {
            subR->_bf = -1;
            parent->_bf = 0;
        } else {
            parent->_bf = 1;
            subR->_bf = 0;
        }
        /*if (bf == 0) {
            parent->_bf = 0;
            subR->_bf = 0;
        } else if (bf == 1) {
            subR->_bf = -1;
            parent->_bf = 0;
        } else {
            parent->_bf = 1;
            subR->_bf = 0;
        }
        subRL->_bf = 0;*/
    }
    int _Height(Node* root)
    {
        if (root == nullptr)
        {
            return 0;
        }
        return max(_Height(root->_left), _Height(root->_right)) + 1;
    }
    bool _Isbalance(Node* root)
    {
        if (root == nullptr)
        {
            return true;
        }
        int left = _Height(root->_left);
        int right = _Height(root->_right);
        if (abs(left - right) >= 2)
        {
            return false;
        }
        return _Isbalance(root->_left) && _Isbalance(root->_right);
    }

public:
    
    AVLTree()
        : _root(nullptr)
    {
    }
    bool insert(const pair<K, V>& kv)
    {
        if (_root == nullptr) {
            _root = new Node(kv);
            return true;
        }
        Node* parent = nullptr;
        Node* cur = _root;
        while (cur) {
            if (kv.first > cur->_kv.first) {
                parent = cur;
                cur = cur->_right;
            } else if (kv.first < cur->_kv.first) {
                parent = cur;
                cur = cur->_left;
            } else {
                return false;
            }
        }
        cur = new Node(kv);
        if (parent->_kv.first < kv.first) {
            parent->_right = cur;
        } else {
            parent->_left = cur;
        }
        cur->_parent = parent;
        while (parent) {
            if (parent->_left == cur) {
                parent->_bf++;
            } else if (parent->_right == cur) {
                parent->_bf--;
            }
            if (parent->_bf == 0) {
                break;
            } else if (parent->_bf == 1 || parent->_bf == -1) {
                cur = parent;
                parent = parent->_parent;
            } else if (parent->_bf == 2 || parent->_bf == -2) {
                if (parent->_bf == 2 && cur->_bf == 1) {
                    RotateR(parent);
                } else if (parent->_bf == -2 && cur->_bf == -1) {
                    RotateL(parent);
                } else if (parent->_bf == 2 && cur->_bf == -1) { // LR–Õ ß∫‚
                    RotateLR(parent);
                } else if (parent->_bf == -2 && cur->_bf == 1) { // RL–Õ ß∫‚
                    RotateRL(parent);
                }
                break;

            } else {
                assert(false);
            }
        }
        return true;
    }
    Node* find(pair<K, V>& kv)
    {
        Node* cur = _root;
        while (cur) {
            if (cur->_kv.first > kv.first) {
                cur = cur->_left;
            } else if (cur->_kv.first < kv.first) {
                cur = cur->_right;
            } else {
                return cur;
            }
        }
        return nullptr;
    }
    bool Delete(pair<K,V>& kv)
    {
        Node* cur = find(kv);
        if (cur==nullptr)
        {
            return true;
        }
        Node* parent = cur->_parent;
    }
    void size()
    {
        _Size(_root);
    }
    void inorder()
    {
        _Inorder(_root);
    }
    bool Isbalance()
    {
        return _Isbalance(_root);
    }
    int Height()
    {
        return _Height(_root);
    }
};