#include"stack.h"
#include"queue.h"
#include<stack>
using namespace std;
using namespace My_Stack;
int main()
{
    std::stack<int> st1;
    My_Stack::stack<int> st;
    st1.push(123);
    cout << st1.top();
    My_queue::queue<int> q;
    q.push(123);
    cout << q.top();
    q.pop();
    
}