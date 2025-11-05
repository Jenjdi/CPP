#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef int STDataType;
typedef struct stack
{
    STDataType* a;
    int top;
    int capacity;
}stack;
void StackInit(stack* ps)
{
    ps->a = (STDataType*)malloc(sizeof(STDataType) * 4);
    if (ps->a == NULL)
    {
        printf("malloc fail\n");
        exit(-1);
    }
    ps->top = 0;
    ps->capacity = 4;
}
void StackDestroy(stack* ps)
{
    free(ps->a);
    ps->a = NULL;
    ps->top = ps->capacity = 0;
}
void StackPop(stack* ps)
{
    assert(ps);
    assert(ps->top > 0);
    ps->top--;
}
void StackPush(stack* ps,STDataType data)
{
    assert(ps);
    if(ps->capacity==ps->top)
    {
        STDataType* tmp = (STDataType*)realloc(ps->a,ps->capacity*2*sizeof(STDataType));
        if(tmp==NULL)
        {
            printf("realloc fail\n");
            exit(-1);
        }
        ps->a = tmp;
        ps->capacity *= 2;
    }
    ps->a[ps->top] = data;
    ps->top++;
}
int main()
{
    stack s;
    StackInit(&s);
    StackPush(&s,15);
    StackPush(&s,178);
    StackPush(&s,1478);
    StackPush(&s,4512);
    StackPush(&s,789);
    StackPush(&s,125);
    StackPush(&s,45615);
    StackPop(&s);
    for(int i=0;i<s.top;i++)
    {
        printf("%d ",s.a[i]);
    }
}

