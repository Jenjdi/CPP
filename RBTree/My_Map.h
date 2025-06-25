#pragma once
#include "RBtree.h"
namespace My_MAP {
template <class K, class V>
class map {
private:
    struct KoM {
        const K& operator()(const std::pair<K, V>& kv)
        {
            return kv.first;
        }
    };
    RBtree<K, std::pair<K, V>, KoM> _tree;

public:
    typedef typename RBtree<K, std::pair<K, V>, KoM>::iterator iterator;//û��ʵ���������ͼ���typename��ʾ���߱�������ʵ������ʱ����ȥ��
    typedef typename RBtree<K, std::pair<K, V>, KoM>::const_iterator const_iterator;
    bool insert(const std::pair<K, V>& kv)
    {
        return _tree.Insert(kv).second;
    }
    V& operator[](const K& key)
    {
        std::pair<iterator, bool> ret = _tree.Insert(std::make_pair(key, V()));
        return ret.first->second;
    }
    iterator begin()
    {
        return _tree.begin();
    }
    iterator end()
    {
        return _tree.end();
    }
};
}
