#pragma once
#include <iostream>
namespace My_AVL
{
template <typename T>
struct AVLTreeNode {
    AVLTreeNode<T>* _left;
    AVLTreeNode<T>* _right;
    AVLTreeNode<T>* _parent;
    int _bf;
    T _val;
};
template<typename T>
class AVL {
    typedef AVLTreeNode<T> Node;
    private:
    Node* _node;
};
}
