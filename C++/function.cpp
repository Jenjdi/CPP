#include <functional>
#include <iostream>
using namespace std;
int func(int a, int b)
{
    return a - b;
}
struct Functor {
    int operator()(int a, int b)
    {
        return a + b;
    }
};
class A
{
public:
    static int plusi(int a, int b)
    {
        return a + b;
    }
    double plusd(double a, double b)
    {
        return a + b;
    }
};
int main()
{
    
    //function<int(int, int)> f1 = func;
    //function<int(int, int)> f2 = Functor();
    //function<int(int, int)> f3 = [](int a, int b) { return a + b; };
    //function<int(int, int)> f4 = &A::plusi;
    //function<double(A*,double, double)> f5 = &A::plusd;//由于内部存在隐含的this指针，因此参数不匹配，需要传入一个A对象
    //cout << f1(12, 34);
    //cout << f2(34, 56);
    //cout << f3(56, 78);
    //cout << f4(98, 76);
    //A a;
    //cout << f5(&a, 54, 32);
    auto f1 = bind(func, placeholders::_2, placeholders::_1);
    auto f2 = bind(&A::plusd, A(), placeholders::_1, placeholders::_2);
    A a;
    auto f3 = bind(&A::plusd,&a, placeholders::_1, placeholders::_2);
    auto f4 = bind<int>(&A::plusd, placeholders::_1, placeholders::_2,placeholders::_3);
    cout<<f2(1.1, 2.1)<<endl;
    cout<<f3(1.1, 2.1)<<endl;
    cout<<f4(A(), 1.1, 2.1);
}