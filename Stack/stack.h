#pragma once
#include <iostream>
namespace My_Stack {
template <class T, class Container=std::deque<T>>
class stack {
public:
    void push(const T& val)
    {
        _con.push_back(val);
    }
    void pop()
    {
        _con.pop_back();
    }
    size_t size()
    {
        return _con.size();
    }
    bool empty()
    {
        return _con.empty();
    }
    const T& top()
    {
        return _con.back();
    }
private:
    Container _con;
};
}