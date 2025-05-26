//#include <functional>
//#include <iostream>
//using namespace std;
//int func(int a, int b)
//{
//    return a - b;
//}
//struct Functor {
//    int operator()(int a, int b)
//    {
//        return a + b;
//    }
//};
//class A
//{
//public:
//    static int plusi(int a, int b)
//    {
//        return a + b;
//    }
//    double plusd(double a, double b)
//    {
//        return a + b;
//    }
//};
//int main()
//{
//    
//    //function<int(int, int)> f1 = func;
//    //function<int(int, int)> f2 = Functor();
//    //function<int(int, int)> f3 = [](int a, int b) { return a + b; };
//    //function<int(int, int)> f4 = &A::plusi;
//    //function<double(A*,double, double)> f5 = &A::plusd;//由于内部存在隐含的this指针，因此参数不匹配，需要传入一个A对象
//    //cout << f1(12, 34);
//    //cout << f2(34, 56);
//    //cout << f3(56, 78);
//    //cout << f4(98, 76);
//    //A a;
//    //cout << f5(&a, 54, 32);
//    auto f1 = bind(func, placeholders::_2, placeholders::_1);
//    auto f2 = bind(&A::plusd, A(), placeholders::_1, placeholders::_2);
//    A a;
//    auto f3 = bind(&A::plusd,&a, placeholders::_1, placeholders::_2);
//    auto f4 = bind<int>(&A::plusd, placeholders::_1, placeholders::_2,placeholders::_3);
//    cout<<f2(1.1, 2.1)<<endl;
//    cout<<f3(1.1, 2.1)<<endl;
//    cout<<f4(A(), 1.1, 2.1);
//}
#include<iostream>
using namespace std;

class A {
public:
    int _a;
};
class B :  public A {
};
class C :  public A {
};
class D : public B, public C {
};
class A1 {
public:
    int _a;
};
class B1 : virtual public A1 {
};
class C1 : virtual public A1 {
};
class D1 : public B1, public C1 {
};
int main()
{
    
    D d;
    D1 d1;
    cout << "sizeof:d no virtual version" << sizeof(d) << endl;
    cout << "sizeof:d1 virtual version" << sizeof(d1) << endl;
    cout << "d.B::_a：" << &d.B::_a << endl;
    cout << "d.C::_a" << &d.C::_a << endl;
    cout << "d.A::_a" << &d.A::_a << endl;
    cout << "d.B::A::_a" << &d.B::A::_a << endl;
    cout << "d.C::A::_a" << &d.C::A::_a << endl;
}