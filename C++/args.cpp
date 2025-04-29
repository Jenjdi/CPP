#include<iostream>
using namespace std;
template <typename T>
void print(T t)
{
    cout << t << " ";
}
template <typename T,typename... Args>
void print(T t,Args... arg)
{
    print(arg...); // 会不断向下传递，当传递为0个参数时，
    // 由于参数包模板的优先级大于特化的模板，因此会继续调用自己，导致无限递归
    cout << endl;
}
int test(int a)
{
    return 2 * a;
}
template<typename ...Args>
void func(Args... arg)
{
    int arr[] = { test(arg)... };
    for (int i : arr)
    {
        cout << i;
    }
}


int doubleValue(int x)
{
    return x * 2;
}

template <typename... Args>
void foo(Args... args)
{
    int arr[] = { doubleValue(args)... };
}

int main()
{
    func(12,12,45,78);
    return 0;
}