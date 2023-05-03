#include <stdio.h>
#define STRING_MAX_SIZE 100

void squeeze(char s1[], char s2[]);

int main()
{

    char s1[STRING_MAX_SIZE];
    char s2[STRING_MAX_SIZE];
    printf("enter string s1\n");
    get_string(s1);
    printf("enter string s2\n");
    get_string(s2);
    squeeze(s1, s2);
    printf("%s\n", s1);
    return 0;
}

void squeeze(char s1[], char s2[])
{
    int i, j;
    int found = 0;
    for (i = j = 0; s1[i] != '\0'; i++)
    {
        for (int k = 0; (s2[k] != '\0') && !found; k++)
        {
            if (s1[i] == s2[k])
            {
                found = 1;
            }
        }

        if (!found)
        {
            s1[j++] = s1[i];
        }
        found = 0;
    }
    s1[j] = '\0';
}

int get_string(char s[])
{
    int c;
    int i = 0;
    while ((c = getchar()) != EOF)
    {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}