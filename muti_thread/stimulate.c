#include<stdio.h>
#include<assert.h>
char* my_strcat(char* dest, const char* src)
{
    char* ret = dest;
    assert(dest != NULL);
    assert(src != NULL);
    while (*dest) {
        dest++;
    }
    while ((*dest++ = *src++)) {
        ;
    }
    return ret;
}
void* my_memcpy(void* dst, const void* src, size_t count)
{
    void* ret = dst;
    assert(src);
    assert(dst);
    while (count--)
    {
        (char*)dst = (char*)src;
        (char*)dst = (char*)dst + 1;
        (char*)src = (char*)src + 1;
    }
    return ret;
}
int main()
{
    char a[20] = "abcdef";
    char b[10] = "123456";
    char* c=my_memcpy(&a, &b,6);
    printf("%s", c);
}