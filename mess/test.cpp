#include <iostream>
#include<functional>
using namespace std;
// // 终止函数，用于处理最后一个参数
// template<typename T>
// int printArgs(T arg) 
// {
//     std::cout << arg << " ";
//     return 0;
// }
// // 递归函数，用于展开参数包
// template<typename T, typename... Args>
// int printArgs(T head, Args... tail)
// {
//     std::cout << head << " ";
//     printArgs(tail...);
//     return 0;
// }
// void test()
// {
//     function<int(int,int)> fc=[](int a,int b){return a/b;};
//     auto f1=bind(fc,placeholders::_2,placeholders::_1);
//     cout<<f1(1,2);
// }
// int main() 
// {
//     test();
//     return 0;
// }
// template <class T>
// int PrintArg(T t)
// {
// 	cout << t << " ";
// 	return 0;
// }

// template <class ...Args>
// void Cpp_Printf(Args... args)
// {
// 	// 编译时推导，args...参数有几个值，PrintArg就调用几次，就有几个返回值，arr就开多大
// 	int arr[] = { PrintArg(args)... };
// 	cout << endl;
// }

// void Cpp_Printf(int x, char y, std::string z)
// {
// 	int arr[] = { PrintArg(x),PrintArg(y),PrintArg(z) };
// 	cout << endl;
// }
// template<class T>
// void print(T t)
// {
//     cout<<t<<" ";
// }
// template<class ...Args>
// void print(Args... arg)
// {
//     print(arg...);//由于传递下去的还是多个参数，因此还会继续调用自己，因此会发生无限递归
//     cout<<endl;
// }
// int main()
// {
//     print(1,2,3,4);
// }
