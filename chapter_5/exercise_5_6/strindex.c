#include <stdio.h>

char* pattern = "ould";
int main()
{
    char s[40];
    int n;
    while (*s != EOF)
    {
        getline1(s);
        n = strindex(s, pattern);
        if (n >= 0)
        {
            printf("%d\n", n);
            printf("%s\n", s);
        }
    }

    return 0;
}

void getline1(char *s)
{
    while (((*s = getchar()) != '\n') && (*s++ != EOF))
        ;
    *s = '\0';
}

int strindex(char* s, char* t)
{
    int i, j, k;
    
    
    for (i = 0; *(s+i) != '\0'; i++)
    {
        for (j = i, k = 0; *(t+k) != '\0' && *(s+j) == *(t+k); j++, k++)
            ;
        if (k > 0 && *(t+k) == '\0')
        {
            return i;
        }
    }
    return -1;
}