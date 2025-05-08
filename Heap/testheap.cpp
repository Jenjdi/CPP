#include "heap.h"
int main()
{
    My_Heap::Heap<int> hp;
    hp.HeapInit();
    hp.HeapPush(12);
    hp.HeapPush(13);
    hp.HeapPush(14);
    hp.HeapPush(15);
    hp.HeapPush(16);
    for (int i = 0; i < hp.size(); i++) {

        hp.HeapPop();
        std::cout << hp.HeapTop() << " ";
    }
}