#pragma once
#include <string>
#include <vector>
template <class K>
struct HashFunc {
    size_t operator()(const K& key)
    {
        return (size_t)key;
    }
};
// ʹ��ģ���ػ�
// ��������stringʱ��������
template <>
struct HashFunc<std::string> {
    size_t operator()(const std::string& key)
    {
        size_t hash = 0;
        for (auto e : key) {
            hash *= 131;
            hash += e;
        }
        return hash;
    }
};
// namespace OpenAddress {
// enum Status {
//     Exist,
//     Delete,
//     Empty
// };
// template <class T>
// struct HashNode {
//     T _data;
//     Status _status = Empty;
// };
//
// template <class K, class T, class KofT, class Hash>
// class HashTable;
//
// template <class K, class T, class KofT, class Hash>
// struct __HTIterator {
//     typedef HashNode<T> Node;
//
//     typedef __HTIterator<K, T, KofT, Hash> Self;
//
//     Node* _node;
//     HashTable<K, T, KofT, Hash>* _pHT;
//     KofT kot;
//     Hash hs;
//
//     __HTIterator(Node* node, HashTable<K, T, KofT, Hash>* pHT)
//         : _node(node)
//         , _pHT(pHT)
//     {
//     }
//     Self& operator++()
//     {
//         size_t hashi = hs(kot(_node->_data)) % _pHT->_table.size();
//         for (; hashi < _pHT->_table.size(); hashi++) {
//             if (_pHT->_table[hashi]) {
//                 break;
//             }
//         }
//         if (hashi == _pHT->_table.size()) {
//             _node = nullptr;
//         } else {
//             _node = _pHT->_table[hashi];
//         }
//         return *this;
//     }
//     bool operator!=(const Self& s)
//     {
//         return _node != s._node;
//     }
//     bool operator==(const Self& s)
//     {
//         return _node == s._node;
//     }
//     T& operator*()
//     {
//         return _node->_data;
//     }
//     T* operator->()
//     {
//         return &_node->_data;
//     }
//
// };
//
// template <class K, class T, class KofT, class Hash>
// class HashTable {
//     typedef __HTIterator<K, T, KofT, Hash> iterator;
//
// private:
//     std::vector<HashNode<T>> _table;
//     size_t _n = 0; // ��ǰ��ϣ���е�������
//     KofT kot;
//     Hash hs;
//
// public:
//     friend struct __HTIterator<K, T, KofT, Hash>;
//     HashTable()
//     {
//         _table.resize(10);
//     }
//     iterator begin()
//     {
//         for (size_t i = 0; i < _table.size(); i++) {
//             if (_table[i])
//                 return iterator(_table[i], this);
//         }
//         return end();
//     }
//     iterator end()
//     {
//         return iterator(nullptr, this);
//     }
//     bool Insert(const T& data)
//     {
//         if (Find(kot(data))) {
//             return false; // ������ظ�ֵ���룬ֱ�ӷ��أ��ܾ�����
//         }
//         if (_n * 10 / _table.size() > 7) {
//             HashTable<K, T, KofT, Hash> newHT;
//             newHT._table.resize(_table.size() * 2);
//             for (size_t i = 0; i < _table.size(); i++) {
//                 if (_table[i]._status == Exist) {
//                     return newHT.Insert(_table[i]._data);
//                 }
//             }
//             _table.swap(newHT._table);
//         }
//         size_t hashi = hs(kot(data)) % _table.size();
//         while (_table[hashi]._status == Exist) {
//             hashi++;
//             hashi %= _table.size();
//         }
//         _table[hashi]._data = data;
//         _table[hashi]._status = Exist;
//         _n++;
//         return true;
//     }
//     HashNode<T>* Find(const K& key)
//     {
//         size_t hashi = hs(key) % _table.size();
//         while (_table[hashi]._status != Empty) {
//             if (hs(kot(_table[hashi]._data)) == hs(key) && _table[hashi]._status == Exist) {
//                 return &_table[hashi];
//             }
//             ++hashi;
//             hashi %= _table.size();
//         }
//         return nullptr;
//     }
//     bool Erase(const K& key)
//     {
//         HashNode<T>* pos = Find(key);
//         if (pos == nullptr) {
//             return false;
//         }
//         pos->_status = Delete;
//         --_n;
//         return true;
//     }
// };
// }
namespace Bucket {

template <class T>
struct HashNode {
    T _data;
    HashNode<T>* _next;
    HashNode(const T& data)
        : _data(data)
        , _next(nullptr)
    {
    }
};

template <class K, class T, class KeyOfT, class Hash>
class HashTable {
public:
    template <class Ptr, class Ref>
    struct __HTIterator {
        typedef HashNode<T> Node;
        typedef __HTIterator Self;

        const HashTable* _pHT;
        Node* _node;
        KeyOfT kot;
        Hash hs;

        __HTIterator(Node* node, const HashTable* ht)
            : _node(node)
            , _pHT(ht)
        {
        }
        Self& operator++()
        {
            if (_node->_next) // ��ǰ���û�����꣬���������
            {
                _node = _node->_next;
            } else {
                size_t hashi = hs(kot(_node->_data)) % _pHT->_table.size();
                hashi++;
                for (; hashi < _pHT->_table.size(); hashi++) {
                    if (_pHT->_table[hashi]) {
                        break;
                    }
                }
                if (hashi == _pHT->_table.size()) {
                    _node = nullptr;
                } else {
                    _node = _pHT->_table[hashi];
                }
            }
            return *this;
        }
        bool operator!=(const Self& s)
        {
            return _node != s._node;
        }
        bool operator==(const Self& s)
        {
            return _node == s._node;
        }
        Ref operator*()
        {
            return _node->_data;
        }
        Ptr operator->()
        {
            return &_node->_data;
        }
    };

    typedef HashNode<T> Node;
    typedef __HTIterator<T*, T&> iterator;
    typedef __HTIterator<const T*, const T&> const_iterator;

private:
    std::vector<Node*> _table;
    size_t _n;
    KeyOfT kot;
    Hash hs;

public:
    HashTable()
        : _n(0)
    {
        _table.resize(10, nullptr);
    }
    ~HashTable()
    {
        for (size_t i = 0; i < _table.size(); i++) {
            Node* cur = _table[i];
            while (cur) {
                Node* next = cur->_next;
                delete cur;
                cur = next;
            }
            _table[i] = nullptr;
        }
    }
    
    iterator begin()
    {
        for (size_t i = 0; i < _table.size(); i++) {
            Node* cur = _table[i];
            if (cur) {
                // this -> HashTable*
                return iterator(cur, this);
            }
        }

        return end();
    }

    iterator end()
    {
        return iterator(nullptr, this);
    }

    const_iterator begin() const
    {
        for (size_t i = 0; i < _table.size(); i++) {
            Node* cur = _table[i];
            if (cur) {
                // this -> const HashTable*
                return const_iterator(cur, this);
            }
        }

        return end();
    }

    const_iterator end() const
    {
        return const_iterator(nullptr, this);
    }
    std::pair<iterator, bool> Insert(const T& data)
    {
        iterator it = Find(kot(data));
        if (it != end()) {
            return std::make_pair(it, false);
        }
        if (_n==_table.size()) // �洢�������ﵽ�����������ޣ���������
        {
            std::vector<Node*> newTable(_table.size() * 2, nullptr);
            for (size_t i = 0; i < _table.size(); i++) {
                Node* cur = _table[i];
                while (cur) {
                    Node* next = cur->_next;
                    size_t hashi = hs(kot(cur->_data)) % newTable.size();
                    cur->_next = newTable[hashi];
                    newTable[hashi] = cur;
                    cur = next;
                }
                _table[i] = nullptr;
            }
            _table.swap(newTable);
        }
        size_t hashi = hs(kot(data)) % _table.size();
        Node* newnode = new Node(data);
        newnode->_next = _table[hashi];
        _table[hashi] = newnode;
        ++_n;
        return (std::make_pair(iterator(newnode, this), true));
    }
    iterator Find(const K& key)
    {
        size_t hashi = hs(key) % _table.size();
        Node* cur = _table[hashi];
        while (cur) {
            if (hs(kot(cur->_data)) == hs(key)) {
                return iterator(cur, this);
            }
            cur = cur->_next;
        }
        return end();
    }
    bool Erase(const K& key)
    {
        if (Find(key)) {
            size_t hashi = hs(key) % _table.size();
            Node* cur = _table[hashi];
            Node* prev = nullptr;
            while (cur) {
                if (hs((kot(cur->_data))) == hs(key)) {
                    if (prev == nullptr) {
                        _table[hashi] = cur->_next;
                    } else {
                        prev->_next = cur->_next;
                    }
                    delete cur;
                    return true;
                } else {
                    prev = cur;
                    cur = cur->_next;
                }
            }
            return false;
        }
    }
};

}