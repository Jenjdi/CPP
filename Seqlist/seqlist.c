#include"Seqlist.h"
void SeqListInit(SeqList* ps)
{
	ps->a = NULL;
	ps->size = 0;
	ps->capacity = 0;
}
void SeqListDestroy(SeqList* ps)
{
	if (ps->a != NULL)
	{
		free(ps->a);
		ps->a = NULL;
		ps->size = ps->capacity = 0;
		
	}
}
void SeqListPrint(SeqList* ps)
{
	for (int i = 0; i < ps->size; i++)
	{
		printf("%d ", ps->a[i]);
	}
	printf("\n");
}
void checkout(SeqList* ps)
{
	if (ps->size == ps->capacity)
	{
		int newcapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;
		SLDateType* newnode = (SLDateType*)realloc(ps->a, newcapacity * sizeof(SLDateType));
		if (newnode == NULL)
		{
			perror("realloc failed");
			exit(1);
		}
		ps->a = newnode;
		ps->capacity = newcapacity;

	}
}
void SeqListPushBack(SeqList* ps, SLDateType x)
{
	checkout(ps);
	assert(ps);
	ps->a[ps->size++] = x;
}
void SeqListPushFront(SeqList* ps, SLDateType x)
{
	checkout(&ps);
	for (int i = ps->size; i > 0; i--)
	{
		ps->a[i] = ps->a[i - 1];
	}
	ps->a[0] = x;
	ps->size++;
}
void SeqListPopFront(SeqList* ps)
{
	for (int i = 0; i < ps->size; i++)
	{
		ps->a[i] = ps->a[i + 1];
	}
	ps->size--;
}
void SeqListPopBack(SeqList* ps)
{
	ps->a[ps->size-1] = 0;
	ps->size--;
}
int SeqListFind(SeqList* ps, SLDateType x)
{
	for (int i = 0; i < ps->size; i++)
	{
		if (ps->a[i] == x)
		{
			return i;
		}
	}
}
void SeqListInsert(SeqList* ps, int pos, SLDateType x)
{
	checkout(ps);
	for (int i = ps->size; i > pos; i++)
	{
		ps->a[i] = ps->a[i - 1];
	}
	ps->a[pos] = x;
	ps->size++;
}
void SeqListErase(SeqList* ps, int pos)
{
	checkout(ps);
	for (int i = pos; i < ps->size; i++)
	{
		ps->a[i] = ps->a[i + 1];
	}
	ps->size--;
}