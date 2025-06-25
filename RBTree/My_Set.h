#pragma once
#include "RBtree.h"
namespace My_SET {
template <class K>
class set {
    
private:
    struct KoS {
        const K& operator()(const K& key)
        {
            return key;
        }
    };
    RBtree<K, K, KoS> _tree;

public:
    typedef typename RBtree<K, K, KoS>::iterator iterator;
    typedef typename RBtree<K, K, KoS>::const_iterator const_iterator;
    bool insert(const K& data)
    {
        return _tree.Insert(data).second;
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