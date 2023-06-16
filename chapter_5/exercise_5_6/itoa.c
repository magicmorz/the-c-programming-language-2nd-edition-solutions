#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 100
void reverse(char *s);
void itoa(int n, char *s);

char s1[MAX_SIZE];

int main(int argc, char const *argv[])
{
    itoa(-2147483648, s1);
    printf("%s\n", s1);
    return 0;
}

void itoa(int n, char *s)
{
    int sign, len = 0;

    sign = n;

    do
    {
        *s++ = abs(n % 10) + '0';
        len++;
    } while (n /= 10);

    if (sign < 0)
    {
        *s++ = '-';
        len++;
    }

    *s = '\0';

    reverse(s - len);
}

void reverse(char *s)
{
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}
