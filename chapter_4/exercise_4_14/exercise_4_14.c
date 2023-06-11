#include <stdio.h>
#define swap(t, x, y) {\
    t = x;\
    x = y;\
    y = t;\
}
int main(int argc, char const *argv[])
{
    int a = 3, b = 4, t;
    swap(t, a, b);
    printf("a = %d, b = %d \n", a, b);
    return 0;
}
