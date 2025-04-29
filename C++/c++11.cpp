//#include <iostream>
//#include <list>
//#include <string>
//#include <vector>
//using namespace std;
////// template<class T>
////// class A
//////{
////// public:
//////     T* func()
//////     {
//////         return new T;
//////     }
//////
////// private:
//////     int _a=10;
////// };
////// auto func()
//////{
//////     list<int> l;
//////     return l.begin();
////// }
////string func()
////{
////    string s1 = ("123");
////    return s1;
////}
////template <typename T>
////class NoMove {
////public:
////    NoMove()
////    {
////        cout << "constructor function" << endl;
////    }
////    NoMove(const T& t)
////    {
////        cout << "copy constructor" << endl;
////        cout << t;
////    } // 只有拷贝构造函数
////    NoMove(T&& t)
////    {
////        cout << "move constructor" << endl;
////        cout << t;
////    }
////};
////struct S {
////    int i : 4;
////};
////template <class T>
////void fun(const T&& t)
////{
////    cout << t;
////}
////
////// int main()
//////{
//////     /*list<int>::iterator it1;
//////     cout << typeid(it1).name() << endl;
//////     decltype(it1) it2;
//////     cout << typeid(it2).name();
//////     auto i = func();
//////     A<decltype(i)> a;
//////     std::vector<int> vl({12,545,989,12});
//////     vl.push_back(123);*/
//////     string&& ref1 = string("123");
//////     string&& ref2 = to_string(123);
//////     int&& ref3 = 10;
//////     const int& leftref = 10;
//////     int a = 10;
//////     int&& rightref = move(a);//a中的值还是10，说明只是拷贝，并没有移动
//////     //cout << a;
//////     //cout << rightref;
//////     const std::string s = "Hello";
//////     std::string s2 = std::move(s); // 调用拷贝构造函数，s中的值还是Hello，说明没有移动，只是进行了拷贝
//////
//////     NoMove<int> obj;
//////     NoMove<int> obj2 = std::move(obj); // 调用拷贝构造函数
//////     NoMove<int> obj3(123);
//////     int&& b = 10;
//////     cout << typeid(b).name();
//////
////// }
////
////template <class T>
////void func(T&& t)
////{
////    cout << typeid(t).name() << endl;
////}
////int main()
////{
////    /*func(10);
////    auto e = [](int a, int b) { return a + b; };
////    cout << typeid(e).name() << endl;
////    auto e1 = [] { cout << "123"; };
////    cout << typeid(e1).name();*/
////
////    /*auto swap1 = [a, b]() mutable {
////        int tmp = a;
////        a = b;
////        b = tmp;
////    }; */
////    // 可以进行交换
////    int a = 10;
////    int b = 20;
////    auto swap2 = [=](int a, int b) {
////        int tmp = a;
////        a = b;
////        b = tmp;
////    };
////    
////    /*auto f = [=]() mutable {
////        int tmp = a;
////        a = b;
////        b = tmp;
////    };*/
////    auto f = [&a, &b]() {
////        int tmp = a;
////        a = b;
////        b = tmp;
////    };
////    f();
////    cout << a << b;
////    //    auto swap2 = [a, b]() {
////    //        int tmp = a;
////    //        a = b;
////    //        b = tmp;
////    //    }; // 不能进行交换
////    //}
////}
////class Person
////{
////public:
////    //Person(Person&& p) = default;
////    Person(const Person& p) = default;
////    Person& operator=(const Person& p) = default;
////    //Person& operator=(Person&& p) = default;
////    Person()
////        {}
////private:
////    string s1;
////    int i1;
////};
////void func(int* p)
////{
////    cout << "func int *p" << endl;
////}
////void func(int p)
////{
////    cout << "func int p" << endl;
////}
////class A
////{
////public:
////    static void func()
////    {
////        A();
////    }
////private:
////    int _a;
////    A()
////    {
////    }
////};
////int main()
////{
////    Person p1;
////    Person p2 = p1;
////    Person p3 = move(p2);
////    
////}
//class HeapOnly {
//public:
//    static HeapOnly* CreateObj()
//    {
//        return new HeapOnly; // 静态
//    }
//    // C++11:使用delete关键字，将拷贝构造删除
//    HeapOnly(const HeapOnly& obj) = delete;
//
//private:
//    // C++98:私有+只声明不实现
//    HeapOnly(const HeapOnly& obj);
//    HeapOnly()
//    {
//    }
//};
//int main()
//{
//    HeapOnly h; // 构造函数私有，不能访问
//    HeapOnly* h2 = HeapOnly::CreateObj();
//    HeapOnly h3(h2); // 拷贝构造被禁止，无法构造
//}