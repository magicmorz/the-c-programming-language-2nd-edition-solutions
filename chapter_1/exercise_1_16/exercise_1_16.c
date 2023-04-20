#include <stdio.h>
#define MAXLINE 1000 /*maximum input line size*/

int getline1(char line[], int limit);
void copy(char destination[], char source[]);

main()
{
    int len, max = 0;
    char line[MAXLINE];
    char longest[MAXLINE];
    while ((len = getline1(line, MAXLINE)) > 0)
    {
        if (len > max)
        {
            copy(longest, line);
            max = len;
        }
        printf("the length of this line is %d\n", len);
    }
    if (max>0)
    {
        printf("%s", longest);
    }
    
    return 0;
}

int getline1(char s[], int limit)
{
    int c;
    int i;
    for (i = 0; (i < limit - 1) && ((c = getchar()) != '\n') && c != EOF; i++)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void copy(char destination[], char source[])
{
    int i = 0;

    while ((destination[i] = source[i]) != '\0')
    {
        i++;
    }
}
