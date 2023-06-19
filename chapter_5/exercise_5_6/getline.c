#include <stdio.h>
int getline1(char *s, int n);
int main()
{
    char s[40];
    int n;
    while (getline1(s, n) > 0)
    {
        printf("%s\n", s);
    }

    return 0;
}

int getline1(char *s, int n)
{
    n = 0;
    while (((*s = getchar()) != '\n') && (*s++ != EOF))
    {
        n++;
    }
    *s = '\0';
    return n;
}