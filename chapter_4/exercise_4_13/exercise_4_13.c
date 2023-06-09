#include <stdio.h>
#include <string.h>
#define MAXSIZE 100
int main()
{
    int num = 5894;
    char s[MAXSIZE] = "abcdefg";

    char d[MAXSIZE] = "       ";

    reverse(s, d, strlen(s)-1, 0);
    printf("%s\n", d);
    return 0;
}

int reverse(char s[], char d[], int i, int j)
{
    if (j == strlen(d))
    {
        return 0;
    }
    if (s[i + 1] == '\0')
    {
        d[j] = s[i];
        s[i] = '\0';
        i--;
        j++;
    }

    reverse(s, d, i, j);
}