#include <stdio.h>
void strcat1(char *s, char *t);
int main(int argc, char const *argv[])
{
    char s1[] = "magic";
    char *s2 = "morz";
    strcat1(s1, s2);
    printf("%s\n", s1);
    return 0;
}

void strcat1(char *s, char *t)
{
    while (*s)
    {
        s++;
    }
    while (*s++ = *t++)
        ;
}

