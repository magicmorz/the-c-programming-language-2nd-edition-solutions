#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 100
void reverse(char s[]);
void itoa(int n, char s[], int minimun_field_width);

int main(int argc, char const *argv[])
{
    char s1[MAX_SIZE];
    itoa(17, s1, 10);
    printf("%s\n", s1);
    return 0;
}

void itoa(int n, char s[], int minimun_field_width)
{
    int i, sign;

    sign = n;
    i = 0;

    do
    {
        s[i++] = abs(n % 10) + '0';
    } while (n /= 10);

    if (sign < 0)
    {
        s[i++] = '-';
    }

    

    if (strlen(s) < minimun_field_width)
    {
        int j = 0;
        while (j < minimun_field_width - strlen(s))
        {
            s[i++] = ' ';
        }
        
    }

    s[i] = '\0';

    reverse(s);
}

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}
