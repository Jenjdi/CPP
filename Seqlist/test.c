#include"Seqlist.h"
int main()
{
	SeqList sl;
	SeqListInit(&sl);

	SeqListPushBack(&sl, 8);
	SeqListPrint(&sl);

	SeqListPushBack(&sl, 10);
	SeqListPrint(&sl);

	SeqListPushFront(&sl, 20);
	SeqListPrint(&sl);

	SeqListPopFront(&sl);
	SeqListPrint(&sl);

	SeqListPopBack(&sl);
	SeqListPrint(&sl);

	int a=SeqListFind(&sl, 8);
	printf(a,"\n");

	SeqListInsert(&sl, 2, 15);
	SeqListPrint(&sl);

	SeqListErase(&sl, 1);
	SeqListPrint(&sl);

	SeqListDestroy(&sl);
}