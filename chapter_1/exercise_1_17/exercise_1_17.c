#include <stdio.h>
#define MAXLINE 1000 /*maximum input line size*/
#define MINLENGTH 80

int getline1(char line[], int limit);

main()
{
    int len, max = 0;
    char line[MAXLINE];
    char longest[MAXLINE];
    while ((len = getline1(line, MAXLINE)) > 0)
    {
        if (len > MINLENGTH)
        {
            printf("%s", line);
        }
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

