#pragma once
#include <deque>
namespace My_queue {
template <class T, class Container = std::deque<T>>
class queue {
public:
    void push(const T& val)
    {
        _con.push_back(val);
    }
    void pop()
    {
        _con.erase(_con.begin());
    }
    void size()
    {
        return _con.size();
    }
    void empty()
    {
        return _con.empty();
    }
    T& top()
    {
        return _con.front();
    }
private:
    Container _con;
};
}