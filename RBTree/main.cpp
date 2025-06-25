#include "My_Map.h"
#include "My_Set.h"
int main()
{
    /*My_MAP::map<int, int> m;
    My_SET::set<int> s;
    m.insert({ 1, 2 });
    s.insert(1);
    s.insert(2);
    s.insert(3);
    My_SET::set<int>::iterator its = s.begin();
    while (its != s.end())
    {
        std::cout << *its << " ";
        ++its;
    }
    std::cout << std::endl;*/
    My_SET::set<int> s;
    
    s.insert(1);
    
    My_SET::set<int>::iterator it = s.begin();
    for (auto e : s)
    {
        std::cout << e << std::endl;
    }
}