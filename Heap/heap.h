#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
namespace My_Heap {
template <typename HeapDataType>
class Heap {
private:
    typedef struct heap {
        HeapDataType* _arr;
        int _size;
        int _capacity;
    } HP;
    void swap(int* a, int* b)
    {
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }
    void AdjustUp(HeapDataType* arr, int child)
    {
        int parent = (child - 1) / 2;
        while (child > 0) {
            if (arr[parent] > arr[child]) {
                swap(&arr[parent], &arr[child]);
                child = parent;
                parent = (child - 1) / 2;
            } else {
                break;
            }
        }
    }
    void AdjustDown(HeapDataType* arr, int parent)
    {
        int child=parent*2+1;
        while (child < size()) {
            if(child+1<size()&&arr[child+1]<arr[child])
            {
                child++;
            }
            if (arr[child] < arr[parent]) {
                swap(&arr[parent], &arr[child]);
                parent = child;
            } else {
                break;
            }
        }
    }
    HP* _php;

public:
    int size()
    {
        return _php->_size;
    }
    int capacity()
    {
        return _php->_capacity;
    }
    HeapDataType HeapTop()
    {
        return _php->_arr[0];
    }
    void HeapInit()
    {
        _php->_arr = NULL;
        _php->_size = _php->_capacity = 0;
    }
    void HeapDestroy()
    {
        free(_php->_arr);
        _php->_arr = NULL;
        _php->_size = _php->_capacity = 0;
    }
    void HeapPush(HeapDataType data)
    {
        if (_php->_size == _php->_capacity) {
            size_t newcap = _php->_capacity == 0 ? 4 : 2 * (_php->_size);
            HeapDataType* tmp = (HeapDataType*)realloc(_php->_arr, newcap * sizeof(HeapDataType));
            if (tmp == NULL) {
                perror("malloc failed");
                exit(-1);
            }
            _php->_capacity = newcap;
            _php->_arr = tmp;
        }
        _php->_arr[_php->_size] = data;
        _php->_size++;
        AdjustUp(_php->_arr, _php->_size - 1);
    }
    void HeapPop()
    {
        swap(&(_php->_arr[_php->_size]), (&_php->_arr[0]));
        _php->_size--;
        AdjustDown(_php->_arr, 0);
    }
};
}
