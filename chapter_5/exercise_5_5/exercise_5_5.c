#include <stdio.h>
void strncpy(char *d, char *s, int n);
void strncat(char *d, char *s, int n);
int strncmp(char *s, char *t, int n);

int main(int argc, char const *argv[])
{
    char s1[40] = "         ";
    char *s2 = "mr blue sky";
    strncpy(s1, s2, 2);
    printf("strncpy is %s\n", s1);

    char base[] = "bruno";
    char addition[] = "mars";
    strncat(addition, base, 2);
    printf("strncat is %s\n", base);

    char cmp1[] = "abc";
    char cmp2[] = "abd";
    printf("strncmp is %d\n", strncmp(cmp1, cmp2, 2));
    return 0;
}

void strncpy(char *d, char *s, int n)
{
    int i;
    for (i = 0; (i < n) && (*s != '\0'); i++)
    {
        *d++ = *s++;
    }
    if (i < n)
    {
        for (; i < n; i++)
        {
            *d++ = '\0';
        }
    }
}

void strncat(char *t, char *s, int n)
{
    while (*s)
    {
        s++;
    }
    while (n)
    {
        *s++ = *t++;
        n--;
    }
    *s = '\0';
}

int strncmp(char *s, char *t, int n)
{
    for (int i = 1; (*s == *t)&&(i<n); s++, t++, i++)
    {
        if (*s == '\0')
        {
            return 0;
        }
    }
    return *s - *t;
}