#include <stdio.h>
int main()
{
    char s[40];
    while (s[0]!=EOF)
    {
        getline1(&s);
        printf("%s\n",s);
    }
    
    return 0;
}

void getline1(char *s)
{
    while (((*s = getchar())!= '\n')&&(*s++!=EOF))
    ;
    *s = '\0';
    
}