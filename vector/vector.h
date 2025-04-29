#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <algorithm>
#include <cassert>
#include <iostream>
namespace my_vector {

template <class T>
class vector {
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    vector() { }
    vector(const vector<T>& v)
    {
        reserve(v.capacity()); // �������ݴ���
        for (auto& e : v) {
            push_back(e);
        }
    }
    template <class InputIterator>
    vector(InputIterator first, InputIterator last) // ��ģ��ĳ�Ա���������Ǻ���ģ��
    {
        while (first != last) {
            push_back(*first);
            first++;
        }
    }
    vector(std::initializer_list<T> il)//���Բ��ü����ã���constԭ�������initializer_list����Ҫ�ľ���ǳ����
        //ʵ������il��ָ��ֱ�ָ��������ĵ�һ��Ԫ�غͳ�����������һ��Ԫ�أ����ÿ�����ֱ�Ӿ͹����ˣ���˼���const�����ö���������û��Ӱ��
        //{1��2��3��4��5��6��78��75}
    {
        reserve(il.size());
        for (auto& e : il)
        {
            push_back(e);
        }
    }
    ~vector()
    {
        delete[] _start;
        _start = _finish = _end_of_storage = nullptr;
    }
    const_iterator begin() const
    {
        return _start;
    }
    const_iterator end() const
    {
        return _finish;
    }
    iterator begin()
    {
        return _start;
    }
    iterator end()
    {
        return _finish;
    }
    size_t size() const
    {
        return _finish - _start;
    }
    size_t capacity() const
    {
        return _end_of_storage - _start;
    }
    void reserve(size_t n)
    {
        if (n > capacity()) {
            size_t old_size = size();
            T* tmp = new T[n];
            // memcpy(tmp, _start, old_size * sizeof(T));//�����ǰ����ֽڿ����ģ����ʹ��string,_start��tmp�е�_strָ�����ͬһ���ַ������ᵼ��ǳ����������
            // ��Ȼvector�����ǳ����������û�н��vector����Ķ������ǳ����
            // ���������
            for (size_t i = 0; i < size(); i++) {
                tmp[i] = _start[i]; // �����memcpy��ͬ����ͨ�����ö�Ӧ�Ķ���ĸ�ֵ����ֵ�Ƕ�Ӧ���������������Ϳ��Է�ֹǳ����������
            }
            delete[] _start;
            _start = tmp;
            _finish = old_size + tmp;
            _end_of_storage = tmp + n;
        }
    }
    void push_back(const T& val) // �п�����string��vector�ȣ����⿽���������ʹ�ô�����
    {
        /*if (_finish == _end_of_storage)
        {
            reserve(capacity() == 0 ? 4 : 2 * capacity());
        }

        *_finish = val;
        ++_finish;*/
        insert(end(), val);
    }
    void insert(iterator pos, T val)
    {
        assert(pos >= _start);
        assert(pos <= _finish);
        if (_finish == _end_of_storage) {
            size_t len = pos - _start; // ʹ��len��ԭ�򣺵õ�����ǰ�����λ�ã��Ա������pos�ҵ�λ��
            reserve(capacity() == 0 ? 4 : 2 * capacity());
            pos = _start + len; // ������������ݣ���Ҫ��pos���и��£�����ͻᵼ�µ�����ʧЧ
        }
        iterator it = _finish - 1;
        while (it >= pos) {
            *(it + 1) = *it;
            --it;
        }
        *pos = val;
        ++_finish;
    }

    vector<T>& operator=(vector<T> v) // �����Ǵ�ֵ�����Ǵ����ã���˲��Ὣvԭ����ֵ�޸ģ�����ֻ��v�Ŀ���
    {
        swap(v);
        return *this;
    }
    T& operator[](size_t pos)
    {
        assert(pos < size());
        return _start[pos];
    }
    iterator erase(iterator pos)
    {
        iterator it = pos + 1;
        while (pos < _finish) {
            (*it - 1) = (*it);
            it++;
        }
        _finish--;
        return pos;
    }
    void resize(size_t n, const T& val = T()) // �����Զ������͵��ù��캯���������������ͽ�����г�ʼ������int()��ʼ��Ϊ0��char()��ʼ��Ϊ'\0'
    {
        if (n > capacity()) {
            reserve(n);
            while (_finish < _start + n) {
                *_finish = val;
                ++_finish;
            }
        } else {
            _finish = _start + n;
        }
    }
    void swap(vector<T>& v)
    {
        std::swap(_start, v._start);
        std::swap(_finish, v._finish);
        std::swap(_end_of_storage, v._end_of_storage);
    }
    void pop_back()
    {
        erase(--end());
    }
    bool empty()
    {
        return _start == _finish;
    }

private:
    iterator _start = nullptr;
    iterator _finish = nullptr;
    iterator _end_of_storage = nullptr;
};
template <class T>
void swap(vector<T>& t1, vector<T>& t2)
{
    t1.swap(t2);
}
}
