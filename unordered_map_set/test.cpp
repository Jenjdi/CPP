#include "hashTable.h"
#include "unordered_map.h"
#include"unordered_set.h"
#include <iostream>
int main()
{
    std::string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
        "苹果", "香蕉", "苹果", "香蕉", "苹果", "草莓", "苹果", "草莓" };
    My_Map::unordered_map<std::string, int> countMap;
    for (auto& e : arr) {
        countMap[e]++;
    }

    My_Map::unordered_map<std::string, int>::iterator it = countMap.begin();
    while (it != countMap.end()) {
        // it->first += 'x'; // key不能修改
        it->second += 1; // value可以修改
        std::cout << it->first << ":" << it->second << std::endl;
        ++it;
    }
    std::cout << std::endl;

    for (auto& kv : countMap) {
        std::cout << kv.first << ":" << kv.second << std::endl;
    }
    std::cout << std::endl;

}