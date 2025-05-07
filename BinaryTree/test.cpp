#include"BinarySearchTree.h"
using namespace std;
int main()
{
    My_BST::BinarySearchTree<int,int> bst;
    int arr[] = { 7, 45, 4, 54 ,95,98,22,223,56,1,3,5,9,13};
    for (auto e : arr)
    {
        bst.insert(e,e+10);
    }
    for (auto e:arr)
    {
        bst.erase(e);
        bst.inorder();
        cout << endl;
    }
    
}
