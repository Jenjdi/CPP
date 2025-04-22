#define _CRT_SECURE_NO_WARNINGS 1
//#include<string>
//#include<iostream>
//#include"string.h"
//
//using namespace my_string;
//void urldivide(string& url)
//{
//    size_t u1 = url.find(":");
//    string protocol = url.substr(0, u1);
//    size_t u2 = url.find('.', u1 + 3);
//    string desolve = url.substr(u1 + 3, u2-u1-3);
//    size_t u3 = url.find('/', u2+1);
//    string domain = url.substr(u2 + 1, u3-u2-1);
//    string uri = url.substr(u3 + 1);
//    std::cout << protocol << " " << desolve << " " << domain << " " << uri << std::endl;
//}
//int main()
//{
//    string s = "https://www.bilibili.com/video/BV1zP4y1i7Pz/?spm_id_from=333.337.search-card.all.click&vd_source=a87039d035dfcca596d440348c3c5996";
//    urldivide(s);
//}
#include"string.h"
#include<iostream>
#include<string>
int main()
{
    //my_string::string s1("123456");
    ///*const my_string::string s2("123456");
    //for (auto e : s2) {
    //    std::cout << e;
    //}*/
    //my_string::string s2("122");
    //for (auto e : s1) {
    //    std::cout << e;
    //}
    //std::cout << std::endl;
    //s1.insert(2, "123456");
    //for (auto e : s1) {
    //    std::cout << e;
    //}
    std::string ss("123");
    std::cin >> ss;
    //std::cout << (s1 == "123") << std::endl;//单参数构造支持隐式类型转换，将字符串隐式转换为string类型
    std::cout << ss;
}
