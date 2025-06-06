#pragma once
#include <algorithm>
#include <iostream>
namespace My_BST_Key_Val_Version {
template <typename K, typename V>
struct BSTNode {
    K _key;
    V _val;
    BSTNode<K, V>* _left;
    BSTNode<K, V>* _right;
    BSTNode(const K& key, const V& val)
        : _key(key)
        , _val(val)
        , _left(nullptr)
        , _right(nullptr)
    {
    }
};
template <typename K, typename V>
class BinarySearchTree {
    typedef BSTNode<K, V> Node;

private:
    Node* _root = nullptr;
    void _Inorder(Node* node)
    {
        if (node == nullptr) {
            return;
        }
        _Inorder(node->_left);
        std::cout << node->_val << " ";
        _Inorder(node->_right);
    }

public:
    bool insert(const K& key, const V& val)
    {
        if (_root == nullptr) {
            _root = new Node(key, val);
            return true;
        }
        Node* cur = _root;
        Node* parent = nullptr;
        while (cur) {
            if (cur->_key < key) {
                parent = cur;
                cur = cur->_right;
            } else if (cur->_key > key) {
                parent = cur;
                cur = cur->_left;
            } else {
                return false;
            }
        }
        cur = new Node(key, val);
        if (parent->_key < key) {
            parent->_right = cur;
        } else {
            parent->_left = cur;
        }
        return true;
    }
    V& operator[](const K& key)
    {
        return find(key)->_val;
    }
    bool operator=(std::pair<K, V> p)
    {
        return insert(p.first, p.second);
    }
    // bool erase(const K& key)
    //{
    //     if (_root == nullptr) {
    //         return false;
    //     }
    //     Node* cur = _root;
    //     Node* parent = nullptr;
    //     while (cur) {
    //         if (cur->_key < key) {
    //             parent = cur;
    //             cur = cur->_right;
    //         } else if (cur->_key > key) {
    //             parent = cur;
    //             cur = cur->_left;
    //         } else {
    //             // 左为空，父节点指向自己的右边
    //             if (cur->_left == nullptr) {
    //                 if (cur == _root) {
    //                     _root = cur->_right; // 左为空，令右边成为新的根结点
    //                 } else {
    //                     if (cur == parent->_left) {
    //                         parent->_left = cur->_right;
    //                     } else {
    //                         parent->_right = cur->_right;
    //                     }
    //                 }
    //                 delete cur;
    //                 return true;
    //             }
    //             // 右为空，父节点指向自己的左边
    //             else if (cur->_right == nullptr) {
    //                 if (cur == _root) {
    //                     _root = cur->_left; // 右为空，令左边成为新的根节点
    //                 } else {
    //                     if (cur == parent->_left) {
    //                         parent->_left = cur->_left;
    //                     } else if (cur == parent->_right) {
    //                         parent->_right = cur->_left;
    //                     }
    //                 }
    //                 delete cur;
    //                 return true;
    //             } else {
    //                 // 左右都不为空，替换法删除
    //                 Node* rightMinParent = cur;
    //                 // 查找右子树的最左结点替换删除
    //                 Node* rightMin = cur->_right;
    //                 while (rightMin->_left) {
    //                     rightMinParent = rightMin;
    //                     rightMin = rightMin->_left;
    //                 }
    //                 std::swap(cur->_key, rightMin->_key);
    //                 // 需要判断rightMin是parent的左节点还是右节点，防止野指针
    //                 if (rightMinParent->_right == rightMin) {
    //                     rightMinParent->_right = rightMin->_right;
    //                 } else {
    //                     rightMinParent->_left = rightMin->_right;
    //                 }
    //                 delete rightMin;
    //                 return true;
    //             }
    //         }
    //     }
    //     return false;
    // }
    bool erase(K& key, V& val)
    {
        if (_root == nullptr) {
            return false;
        }
        Node* cur = _root;
        Node* parent = nullptr;
        while (cur) {
            if (cur->_key > key) {
                parent = cur;
                cur = cur->_left;
            } else if (cur->_key < key) {
                parent = cur;
                cur = cur->_right;
            } else {
                if (cur->_left == nullptr) // 左为空，即使是两边都为空，parent直接指向nullptr，因此不需要判断两边都为空的情况
                {
                    if (cur == _root) {
                        _root = cur->_right;
                    } else {
                        if (parent->_left == cur) {
                            parent->_left = cur->_right;
                        } else if (parent->_right == cur) {
                            parent->_right = cur->_right;
                        }
                    }
                    delete cur;
                    return true;

                } else if (cur->_right == nullptr) {
                    if (cur == _root) {
                        _root = cur->_left;
                    } else {
                        if (parent->_left == cur) {
                            parent->_left = cur->_left;
                        } else if (parent->_right == cur) {
                            parent->_right = cur->_left;
                        }
                    }

                    delete cur;
                    return true;
                } else {
                    Node* LeftMax = cur->_left;
                    Node* parent = cur;
                    while (LeftMax->_right) {
                        parent = LeftMax;
                        LeftMax = LeftMax->_right;
                    }
                    std::swap(cur->_key, LeftMax->_key);
                    std::swap(cur->_val, LeftMax->_val);
                    if (parent->_left == LeftMax)
                        parent->_left = LeftMax->_left;
                    else
                        parent->_right = LeftMax->_left;

                    delete LeftMax;
                    return true;
                }
            }
        }
    }
    void inorder()
    {
        _Inorder(_root);
    }
    Node* find(const K& key)
    {
        Node* cur = _root;
        while (cur) {
            if (cur->_key > key) {
                cur = cur->_left;
            } else if (cur->_key < key) {
                cur = cur->_right;
            } else {
                return cur;
            }
        }
        return cur;
    }
};
}

namespace My_BST_Key_Version {
template <typename K>
struct BSTNode {
    K _key;
    BSTNode<K>* _left;
    BSTNode<K>* _right;
    BSTNode(const K& key)
        : _key(key)
        , _left(nullptr)
        , _right(nullptr)
    {
    }
};
template <typename K>
class BinarySearchTree {
    typedef BSTNode<K> Node;

private:
    Node* _root = nullptr;
    void _Inorder(Node* node)
    {
        if (node == nullptr) {
            return;
        }
        _Inorder(node->_left);
        std::cout << node->_val << " ";
        _Inorder(node->_right);
    }

public:
    bool insert(const K& key)
    {
        if (_root == nullptr) {
            _root = new Node(key);
            return true;
        }
        Node* cur = _root;
        Node* parent = nullptr;
        while (cur) {
            if (cur->_key < key) {
                parent = cur;
                cur = cur->_right;
            } else if (cur->_key > key) {
                parent = cur;
                cur = cur->_left;
            } else {
                return false;
            }
        }
        cur = new Node(key);
        if (parent->_key < key) {
            parent->_right = cur;
        } else {
            parent->_left = cur;
        }
        return true;
    }
    bool erase(const K& key)
    {
        if (_root == nullptr) {
            return false;
        }
        Node* cur = _root;
        Node* parent = nullptr;
        while (cur) {
            if (cur->_key < key) {
                parent = cur;
                cur = cur->_right;
            } else if (cur->_key > key) {
                parent = cur;
                cur = cur->_left;
            } else {
                // 左为空，父节点指向自己的右边
                if (cur->_left == nullptr) {
                    if (cur == _root) {
                        _root = cur->_right; // 左为空，令右边成为新的根结点
                    } else {
                        if (cur == parent->_left) {
                            parent->_left = cur->_right;
                        } else {
                            parent->_right = cur->_right;
                        }
                    }
                    delete cur;
                    return true;
                }
                // 右为空，父节点指向自己的左边
                else if (cur->_right == nullptr) {
                    if (cur == _root) {
                        _root = cur->_left; // 右为空，令左边成为新的根节点
                    } else {
                        if (cur == parent->_left) {
                            parent->_left = cur->_left;
                        } else if (cur == parent->_right) {
                            parent->_right = cur->_left;
                        }
                    }
                    delete cur;
                    return true;
                } else {
                    // 左右都不为空，替换法删除
                    Node* rightMinParent = cur;
                    // 查找右子树的最左结点替换删除
                    Node* rightMin = cur->_right;
                    while (rightMin->_left) {
                        rightMinParent = rightMin;
                        rightMin = rightMin->_left;
                    }
                    std::swap(cur->_key, rightMin->_key);
                    // 需要判断rightMin是parent的左节点还是右节点，防止野指针
                    if (rightMinParent->_right == rightMin) {
                        rightMinParent->_right = rightMin->_right;
                    } else {
                        rightMinParent->_left = rightMin->_right;
                    }
                    delete rightMin;
                    return true;
                }
            }
        }
        return false;
    }
    void inorder()
    {
        _Inorder(_root);
    }
    Node* find(const K& key)
    {
        Node* cur = _root;
        while (cur) {
            if (cur->_key > key) {
                cur = cur->_left;
            } else if (cur->_key < key) {
                cur = cur->_right;
            } else {
                return cur;
            }
        }
        return cur;
    }
};
}