#include <stdio.h>
#define MAXLINE 1000 /*maximum input line size*/
#define INSIDE 1
#define OUTSIDE 0

int getline1(char line[], int limit);
void strip(char line []);

main()
{
    int len, max = 0;
    char line[MAXLINE];
    char longest[MAXLINE];
    while ((len = getline1(line, MAXLINE)) > 0)
    {
        strip(line);
        printf("%s\n", line);
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

void strip (char s[])
{
    int start_position;
    int end_position;
    int i;
    
    for (i = 0; (s[i]!= '\0')&&((s[i]==' ')||(s[i]=='\t')); i++)
        ;
    
    start_position = i;

    for (i = start_position; (s[i]!= '\0')/**&&(s[i]!=' ')&&(s[i]!='\n')*/; i++)
        ;
    
    end_position = i;

    //printf("start_position is %d  end position is %d\n", start_position, end_position);
    
    for (i = 0; i <= end_position-start_position; i++)
    {
        s[i] = s[start_position+i];
    }

    for(;i<MAXLINE;i++)
    {
        s[i] = '\0';
    }
    
}
