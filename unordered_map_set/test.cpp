#include "hashTable.h"
#include "unordered_map.h"
#include"unordered_set.h"
#include <iostream>
int main()
{
    std::string arr[] = { "ƻ��", "����", "ƻ��", "����", "ƻ��", "ƻ��", "����",
        "ƻ��", "�㽶", "ƻ��", "�㽶", "ƻ��", "��ݮ", "ƻ��", "��ݮ" };
    My_Map::unordered_map<std::string, int> countMap;
    for (auto& e : arr) {
        countMap[e]++;
    }

    My_Map::unordered_map<std::string, int>::iterator it = countMap.begin();
    while (it != countMap.end()) {
        // it->first += 'x'; // key�����޸�
        it->second += 1; // value�����޸�
        std::cout << it->first << ":" << it->second << std::endl;
        ++it;
    }
    std::cout << std::endl;

    for (auto& kv : countMap) {
        std::cout << kv.first << ":" << kv.second << std::endl;
    }
    std::cout << std::endl;

}