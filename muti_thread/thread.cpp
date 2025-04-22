//////#include<thread>
//////#include<iostream>
//////#include<mutex>
//////#include<vector>
//////#include<condition_variable>
//////using namespace std;
//////void print(int a, int b, mutex& mut)
//////{
//////    mut.lock();
//////    for (int i = a;i <= b;i++)
//////    {
//////        cout << "thread is printing" << endl;
//////    }
//////    mut.unlock();
//////}
////////int main()
////////{
////////    mutex m;
////////    thread t(print, 1, 5,&m);
////////    t.join();
////////}
//////int main()
//////{
//////    vector<thread> vthd;
//////    mutex m;
//////    for (auto& thd : vthd)
//////    {
//////        //移动赋值
//////        //thread是个匿名对象，为右值，通过移动赋值传给thd
//////        thd = thread(print, 0, 5, ref(m));
//////    }
//////
//////    condition_variable cv;
//////    unique_lock<mutex> ul;
//////    cv.wait(ul);
//////    
//////}
////#include<iostream>
////#include<exception>
////using namespace std;
////class Exception
////{
////	public:
////		Exception()
////		{
////
////		}
////		void what(const char* msg)
////		{
////			cout << " occur exception " << "num="<<msg;
////            throw msg;
////		}
////        
////};
////class HttpException:public Exception
////{
////public:
////	HttpException()
////	{
////            cout << 111;
////	}
////	virtual void what(const char* msg,int num)
////	{
////		cout << "http exception" << msg << "num=" << num << endl;
////        throw msg;
////	}
////};
////void Divide(int a,int b)
////{
////	if (b == 0)
////	{
////        throw HttpException();
////	}
////    int c = a / b;
////    cout << c << endl;
////}
////int main()
////{
////    int a = 0;
////    int b = 0;
////	try
////	{
////        Divide(a, b);
////	}
////	catch (const Exception& e)
////	{
////            e.what("123");
////	}
////}
//#define _CRT_SECURE_NO_WARNINGS 1
#include<fstream>
#include<iostream>
//#include<thread>
//#include<memory>
//#include<list>
using namespace std;
//struct Node {
//    shared_ptr<Node> _prev;
//    shared_ptr<Node> _next;
//    int _val;
//    ~Node()
//    {
//        cout << "~Node()" << endl;
//    }
//};
//int main()
//{
//    shared_ptr<FILE> f(fopen("./test.txt", "w"), [](FILE* f) { fclose(f); });
//
//
//   
//}
//class ConfigInfo
//{
//public:
//    static ConfigInfo* getInstance()
//    {
//        return &_sInfo;
//    }
//
//private:
//    static ConfigInfo _sInfo;//声明
//    //静态成员存在于静态区，和类不在同一个位置
//    // 相当于在静态区创建了一个类
//    // 不会造成无限递归的问题
//};
//int main()
//{
//    ifstream ifs("D:\\Pictures\\新建画布1.jpg",ifstream::in|ifstream::binary);
//    ofstream ofs("tst.jpg", ofstream::out | ofstream::binary);
//    char a=ifs.get();
//    while (ifs.good())
//    {
//        ofs << a;
//        a = ifs.get();
//    }
//}