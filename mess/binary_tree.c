// #include<stdio.h>
// #include<stdlib.h>
// typedef struct binary_tree
// {
//     int _val;
//     struct binary_tree *_left;
//     struct binary_tree *_right;
// }Tree;
// Tree* createNode(int data)
// {
//     Tree *root = (Tree*)malloc(sizeof(Tree));
//     root->_left=NULL;
//     root->_right=NULL;
//     root->_val=data;
//     return root;
// }
// Tree* buildTree() {
//     int data;
//     scanf("%d", &data);

//     // 输入-1表示空节点
//     if (data == -1) {
//         return NULL;
//     }
//     // 创建根节点
//     Tree* root = createNode(data);

//     // 递归建立左子树
//     root->_left = buildTree();

//     // 递归建立右子树
//     root->_right = buildTree();

//     return root;
// }
// void preOrderTraversal(Tree* root) {
//     if (root == NULL) {
//         return;
//     }
//     printf("%d ", root->_val);
//     preOrderTraversal(root->_left);
//     preOrderTraversal(root->_right);
// }
// void midOrderTraversal(Tree* root) {
//     if (root == NULL) {
//         return;
//     }
//     midOrderTraversal(root->_left);
//     printf("%d ", root->_val);
//     midOrderTraversal(root->_right);
// }
// void postOrderTraversal(Tree* root) {
//     if (root == NULL) {
//         return;
//     }
//     postOrderTraversal(root->_left);
//     postOrderTraversal(root->_right);
//     printf("%d ", root->_val);
// }
// int countLeaf(Tree* root)
// {
//     if(root==NULL)
//     {
//         return 0;
//     }
//     if(root->_left==NULL&&root->_right==NULL)
//     {
//         return 1;
//     }
//     return countLeaf(root->_left)+countLeaf(root->_right);
// }
// int getHeight(Tree* root)
// {
//     if (root == NULL)
//     {
//         return 0;
//     }
//     int leftHeight = getHeight(root->_left);
//     int rightHeight = getHeight(root->_right);
//     return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef char BTDataType;

typedef struct BinaryTreeNode
{
	BTDataType _data;
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
}BTNode;

// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
BTNode* BinaryTreeCreate(BTDataType* a, int n, int* pi)
{
    BTNode* node=(BTNode*)malloc(sizeof(BTNode));
    
}
// 二叉树销毁
void BinaryTreeDestory(BTNode** root);
// 二叉树节点个数
int BinaryTreeSize(BTNode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    return BinaryTreeSize(root->_left)+BinaryTreeSize(root->_right)+1;
}
// 二叉树叶子节点个数
int BinaryTreeLeafSize(BTNode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->_left==NULL&&root->_right==NULL)
    {
        return 1;
    }
    return BinaryTreeLeafSize(root->_left)+BinaryTreeLeafSize(root->_right);
}
// 二叉树第k层节点个数
int BinaryTreeLevelKSize(BTNode* root, int k)
{
    if(root==NULL)
    {
        return 0;
    }
    if(k==1)
    {
        return 1;
    }
    return BinaryTreeLevelKSize(root->_left,k-1)+BinaryTreeLevelKSize(root->_right,k-1);
}
// 二叉树查找值为x的节点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
    if(root==NULL)
    {
        return NULL;
    }
    if(root->_data==x)
    {
        return root;
    }
    BTNode* left=BinaryTreeFind(root->_left,x);
    if(left!=NULL)
    {
        return left;
    }
    if(root->_right!=NULL)
    {
        return BinaryTreeFind(root->_right,x);
    }
    return NULL;
}
// 二叉树前序遍历
void BinaryTreePrevOrder(BTNode* root)
{
    if(root==NULL)
    {
        return;
    }
    printf("%c",root->_data);
    BinaryTreePrevOrder(root->_left);
    BinaryTreePrevOrder(root->_right);
}
// 二叉树中序遍历
void BinaryTreeInOrder(BTNode* root)
{
    if(root==NULL)
    {
        return;
    }
    BinaryTreeInOrder(root->_left);
    printf("%c",root->_data);
    BinaryTreeInOrder(root->_right);

}
// 二叉树后序遍历
void BinaryTreePostOrder(BTNode* root)
{
    if(root==NULL)
    {
        return;
    }
    BinaryTreeInOrder(root->_left);
    BinaryTreeInOrder(root->_right);
    printf("%c",root->_data);
}
// 层序遍历
void BinaryTreeLevelOrder(BTNode* root)
{
    
}
// 判断二叉树是否是完全二叉树
int BinaryTreeComplete(BTNode* root);