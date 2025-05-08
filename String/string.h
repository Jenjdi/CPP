#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include <cstring>
#include<iostream>
#include<algorithm>
namespace my_string {
class string {
public:
    
    /*string()
        : _str(new char[1])
        , _size(0)
        , _capacity(0)
    {
        _str[0] = '\0';
    }*/
    string(const char* str = "") // 默认空字符串就有一个\0，没有必要再写一个\0
        : _size(strlen(str))
    {
        _capacity = _size;
        _str = new char[_size + 1];
        strcpy(_str, str);
    }
    string(const string& s)
    {
        _str = new char[s._capacity + 1];
        strcpy(_str, s._str);
        _size = s._size;
        _capacity = s._capacity;
    }
    
    string& operator>>(std::istream input)
    {
        
    }
    
    string& operator=(const string& s)
    {
        char* tmp = new char[s._capacity+1];
        strcpy(tmp,s._str);
        delete[] _str;
        _size=s._size;
        _capacity=s._capacity;
        _str = tmp;
        return *this;
    }
    typedef char* iterator;
    iterator begin()
    {
        return _str;
    }
    iterator end()
    {
        return _str + _size;
    }
    typedef const char* const_iterator;
    iterator begin() const
    {
        return _str;
    }
    iterator end() const
    {
        return _str + _size;
    }
    char& operator[](size_t pos)
    {
        return _str[pos];
    }
    char& operator[](size_t pos) const
    {
        return _str[pos];
    }
    char* c_str()
    {
        return _str;
    }
    char* c_str() const
    {
        return _str;
    }
    string substr(size_t pos = 0, size_t len = npos) const
    {
        string sub;
        if (len >= _size - pos)
        {
            for (size_t i = pos;i < _size;i++)
            {
                sub += _str[i];
            }
        }
        else
        {
            for (size_t i = pos;i < pos + len;i++)
            {
                sub += _str[i];
            }
        }
        return sub;
    }
    string& operator+=(const char* str)
    {
        append(str);
        return *this;
    }
    string& operator+=(char str)
    {
        push_back(str);
        return *this;
    }
    string& operator+=(const string& s)
    {
        if (_size + s.size() >= _capacity) {
            reserve(_size + s.size());
        }
        strncpy(_str + _size, s._str, s.size());
        _size += s.size();
        return *this;
    }
    size_t size() const
    {
        return _size;
    }
    size_t capacity() const
    {
        return _capacity;
    }
    void reserve(size_t cap)
    {
        if (cap>_capacity)
        {
            char* tmp = new char[cap+1];
            strcpy(tmp, _str);
            delete[] _str;
            _str = tmp;
            _capacity = cap;
        }
    }
    void append(const char* str)
    {
        size_t len = strlen(str);
        if (len + _size > _capacity)
        {
            reserve(len+_size);
        }
        strcpy(_str + _size, str);
        _size += len;
    }
    void push_back(char str)
    {
        if (_capacity == _size)
        {
            reserve(_capacity == 0 ? 4 : _capacity * 2);
        }
        _str[_size] = str;
        _size++;
        _str[_size] = '\0';
    }
    void insert(size_t pos, char ch)
    {
        if (_size == _capacity)
        {
            reserve(_capacity == 0 ? 4 : _capacity * 2);
        }
        //size_t end = _size;当pos=0时，end需要走到小于0的位置才会停止，因此将其换成int类型
        //方法一,在比较的位置将pos强转成int,如果直接比较将会发生类型转换导致一直循环
        /*int end=_size;
        while (end >= (int)pos)
        {
            _str[end + 1] = _str[end];
            end--;
        }*/
        size_t end = _size;
        while (end > pos)
        {
            _str[end] = _str[end - 1];
            end--;
        }
        //方法二，令end>pos,这时就不会走到小于0的位置，也就不会一直循环
        _str[pos] = ch;
        _size++;
    }
    void insert(size_t pos,const char* str)
    {
        size_t len = strlen(str);
        if (_size+len > _capacity)
        {
            reserve(_capacity == 0 ? 4 : _capacity * 2);
        }
        size_t end = _size+len;
        
        while (end-len+1 > pos)
        {
            _str[end] = _str[end - len];
            end--;
        }
        strncpy(_str + pos, str, len);
        _size += len;
    }
    void resize(size_t n = 0, char ch = '\0')
    {
        if (n < _size)
        {
            _str[n] = '\0';
            _size = n;
        }
        else
        {
            reserve(n);
            for (size_t i = _size;i < n;i++)
            {
                _str[i] = ch;
            }
            _str[n] = '\0';
            _size = n;
        }
    }
    void erase(size_t pos=0, size_t len = npos)
    {
        if (len == npos && len >= _size - pos)
        {
            _str[pos] = '\0';
            _size = pos;
        }
        else
        {
            strcpy(_str + pos, _str + pos + len);
            _size -= len;
        }
    }
    void swap(string& s)
    {
        std::swap(s._str, _str);
        std::swap(s._size, _size);
        std::swap(s._capacity, _capacity);
    }
    void swap(string& s1, string& s2)
    {
        s1.swap(s2);
    }
    size_t find(char ch,size_t pos=0) const
    {
        for (size_t i = pos;i < _size;i++)
        {
            if (_str[i] == ch)
            {
                return i;
            }
        }
        return npos;
    }
    size_t find(const char* str, size_t pos = 0) const
    {
        char* p = strstr(_str, str);
        if (p)
        {
            return p - _str;
        }
        else
        {
            return npos;
        }
    }
    void clear()
    {
        _size = 0;
        _str[_size] = '\0';
    }
    ~string()
    {
        delete[] _str;
        _str = nullptr;
        _size = _capacity = 0;
    }

public:
    static const int npos;
private:
    char* _str;
    size_t _size;
    size_t _capacity;
};
const int string::npos = -1;
std::ostream& operator<<(std::ostream& output, const string& s)
{
    for (auto ch : s)//如果是成员函数，则第一个参数默认是this指针，会导致不能传入两个参数，因此使用全局
        //不使用友元的原因，使用范围for或者迭代器，可以不用访问私有成员
    {
        output<<s;
    }
    return output;
}
std::istream& operator>>(std::istream& in, string& s)
{
    s.clear();
    char ch;
    ch=in.get();
    char buff[128];
    size_t i = 0;
    while (ch != '\n' && ch != ' ')
    {
        buff[i++] += ch;//借助一个buffer，只有当达到了足够的容量才将其装入s，进行扩容，减少了扩容顺序
        if (i == 127)
        {
            buff[i] = '\0';
            s += buff;
            i = 0;
        }
        ch = in.get();
    }
    if (i > 0)
    {
        buff[i] = '\0';
        s += buff;
    }
    return in;  
}
bool operator==(const string& s1,const string& s2)//如果是成员函数，则第一个参数默认是this指针，会导致不能传入两个参数
{
    int ret = strcmp(s1.c_str(), s2.c_str());
    return ret == 0;
}
bool operator!=(const string& s1, const string& s2)
{
    return !(s1==s2);
}
bool operator>(const string& s1, const string& s2)
{
    int ret = strcmp(s1.c_str(), s2.c_str());
    return ret == 1;
}
}