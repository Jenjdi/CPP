#include "priority_queue.h"

using namespace My_Priority_queue;
struct A
{
    int _a;
};
//bool operator<(const A* a1, const A* a2)
//{
//
//}
// ��������ر���Ҫ���Զ������ͣ��Զ������͵�ָ��Ϊָ�룬Ҳ���������ͣ�������ֱ��ʹ��operator<���ᱨ�����������Ҫʹ�÷º���
//�º����������ƱȽ��߼�������������ν��бȽ�
int main()
{
    priority_queue<int> pq;
    pq.push(12);
    pq.push(123);
    pq.push(8);
    pq.push(7);
    while (!pq.empty())
    {
        std::cout << pq.top() << std::endl;
        pq.pop();
    }
    priority_queue<A*,std::vector<A*>>
    
}