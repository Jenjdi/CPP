#include<vector>
#include<iostream>
#include<string>
#include"vector.h"
//using namespace std;
int main()
{
    //my_vector::vector<int> arr;
    //arr.push_back(12);
    //arr.push_back(12);
    //arr.push_back(12);
    //arr.push_back(12);
    //arr.insert(arr.begin(), 10);
    ///*for (int i = 0; i < arr.size();i++)
    //{
    //    std::cout << arr[i];
    //}*/
    //my_vector::vector<int> arr2(arr);
    //for (int i = 0; i < arr2.size(); i++) {
    //    std::cout << arr2[i];
    //}
    //std::cout << std::endl;
    //for (auto e : arr)
    //{
    //    std::cout << e;
    //}
    //my_vector::vector<int> arr3(arr2.begin(), arr2.end());
    ////my_vector::vector<int> arr3(++arr2.begin(), --arr2.end());这里是传值返回，返回的是返回对象的拷贝，因此无法进行修改
    //my_vector::vector<std::string> vs;
    my_vector::vector<int> v1({ 1, 2, 5, 0, 6, 5, 5, 2 });
    for (auto e : v1)
    {
        std::cout << e << " ";
    }
}