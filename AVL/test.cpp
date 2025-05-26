#include"AVLTree.h"
#include<vector>
const long long N = 1000;
int main()
{
    AVLTree<int, int> avl;
    vector<int> t;
    srand(time(nullptr));
    for (int i = 0;i < N;i++)
    {
        avl.insert({ rand(), rand() });
    }
    
    cout << avl.Height();
    cout << endl;
    cout<<avl.Isbalance();
}