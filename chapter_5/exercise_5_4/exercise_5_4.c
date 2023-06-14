#include <stdio.h>
int strend(char *s, char *t);
int main(int argc, char const *argv[])
{
    char s1[] = "mr blue sky";
    char *s2 = "sky";

    printf("%d\n", strend(s1, s2));
    return 0;
}

int strend(char *s, char *t)
{
    while (*s++)
    {
        if (*s == *t)
        {
            while (*s++ == *t++)
            {
                if ((*s == '\0') && (*t == '\0'))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}
