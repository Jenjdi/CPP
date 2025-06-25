#include <iostream>
using namespace std;
namespace my_auto {
template <class T>
class auto_ptr {
private:
    T* _ptr;
    auto_ptr(T* ptr)
        : _ptr(ptr)
    {
    }
    auto_ptr(const auto_ptr<T>& ap)
        : _ptr(ap._ptr)
    {
        ap._ptr = nullptr;
    }
    ~auto_ptr()
    {
        if (_ptr)
        {
            delete _ptr;
        }
    }
    auto_ptr<T>& operator=(auto_ptr<T>& ap)
    {
        if (ap != this)
        {
            if (_ptr)
                delete _ptr;
            _ptr = ap._ptr;
            ap._ptr = nullptr;
        }
        return *this;
    }
    T* operator->()
    {
        return _ptr;
    }
    T& operator*()
    {
        return *_ptr;
    }
};
}
namespace my_unique {
template <class T>
class unique_ptr {
private:
    T* _ptr;

public:
    unique_ptr<T>& operator=(const unique_ptr<T>& ptr) = delete;
    unique_ptr(const unique_ptr<T>& ptr) = delete;
    unique_ptr(T* ptr)
        : _ptr(ptr)
    {
    }
    ~unique_ptr()
    {
        if (_ptr) {
            cout << "delete" << _ptr << endl;
            delete _ptr;
        }
    }
    T& operator*()
    {
        return *_ptr;
    }
    T* operator->()
    {
        return _ptr;
    }
};
}
namespace my_shared {
template <class T>
class shared_ptr {
private:
    T* _ptr;
    atomic<int>* _count; // 应该使用指针，如果直接使用int会导致每个shared_ptr对象内部都会有一个自己的引用计数

public:
    shared_ptr(T* ptr)
        : _ptr(ptr)
        , _count(new int(1))
    {
    }
    shared_ptr(const shared_ptr<T>& ptr)
        : _ptr(ptr._ptr)
        , _count(ptr._count)
    {
        (*_count)++;
    }
    shared_ptr<T>& operator=(const shared_ptr<T>& ptr)
    {
        if (_ptr != ptr._ptr) // 防止自己给自己赋值
        {
            this->release();
            _ptr = ptr->_ptr;
            _count = ptr->_count;
            (*_count)++;
        }
        return *this;
    }
    int use_count()
    {
        return *_count;
    }
    void release() // 需要设计锁保证引用计数是线程安全的，也可以对引用计数加上atomic
    {
        if (--(*_count) == 0) {
            delete _ptr;
            delete _count;
        }
    }
    T* get() const
    {
        return _ptr;
    }
    ~shared_ptr()
    {
        release();
    }
    T* operator->()
    {
        return _ptr;
    }
    T& operator*()
    {
        return &_ptr;
    }
};
}
namespace my_weak {
template <class T>
class weak_ptr {
private:
    T* _ptr;

public:
    weak_ptr(const shared_ptr<T>& sptr)
        : _ptr(sptr.get())
    {
    }
    weak_ptr()
        : _ptr(nullptr)
    {
    }
    weak_ptr<T>& operator=(const shared_ptr<T>& sp)
    {
        _ptr = sp.get();
        return *this;
    }
    T* operator->()
    {
        return _ptr;
    }
    T& operator*()
    {
        return *_ptr;
    }
};
}