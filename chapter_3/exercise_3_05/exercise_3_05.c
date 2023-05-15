#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100
void itob(int n, char s[], int b);
void reverse(char s[]);
int main()
{
    char s[MAX_SIZE];
    itob(289, s, 2);
    printf("%s", s);
    return 0;
}

void itob(int n, char s[], int b)
{
    int remainder;
    int i;
    for (i = 0; n > 0; i++, n /= b)
    {
        remainder = n % b;
        if ((b == 16) && (remainder > 9))
        {
            s[i] = '0' + remainder + 7;
        }
        else
        {
            s[i] = '0' + remainder;
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