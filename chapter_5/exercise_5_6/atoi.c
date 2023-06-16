#include <stdio.h>
int main(int argc, char const *argv[])
{
    char* s = "231";
    int n = atoi(s);
    printf("%d", n);
    return 0;
}

int atoi(char *s)
{
    int n;

    n = 0;
    while (*s >= '0' && *s <= '9')
    {
        n = 10 * n + (*s++ - '0');
    }
    return n;
}
