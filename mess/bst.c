#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 创建新节点
TreeNode* createNode(char data) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (!newNode) {
        printf("内存分配失败\n");
        exit(0);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 插入节点
TreeNode* insertNode(TreeNode *root, char data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// 前序遍历
void preorder(TreeNode *root) {
    if (root != NULL) {
        printf("%c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// 中序遍历
void inorder(TreeNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%c ", root->data);
        inorder(root->right);
    }
}

// 后序遍历
void postorder(TreeNode *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->data);
    }
}
int countLeaves(TreeNode *root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return countLeaves(root->left) + countLeaves(root->right);
}
int main() {
    TreeNode *root = NULL;
    root = insertNode(root, 'E');
    insertNode(root, 'B');
    insertNode(root, 'A');
    insertNode(root, 'D');
    insertNode(root, 'C');
    insertNode(root, 'F');

    printf("前序遍历: ");
    preorder(root);
    printf("\n");

    printf("中序遍历: ");
    inorder(root);
    printf("\n");

    printf("后序遍历: ");
    postorder(root);
    printf("\n");
    int leafNUM=countLeaves(root);
    printf("叶子节点个数：%d\n",leafNUM);
    return 0;
}
