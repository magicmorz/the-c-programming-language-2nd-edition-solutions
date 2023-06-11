#include <stdio.h>
#define swap(t, x, y) \
    {                 \
        t temp;       \
        temp = x;     \
        x = y;        \
        y = temp;     \
    };
int main(int argc, char const *argv[])
{
    int a = 3, b = 4;
    swap(int, a, b);
    printf("a = %d, b = %d \n", a, b);
    return 0;
}
