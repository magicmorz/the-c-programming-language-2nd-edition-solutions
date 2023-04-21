#include <stdio.h>
#define MAXLENGTH 1000
int get_line(char line[], int len);
void reverse(char line[], int len);
main()
{
    char line [MAXLENGTH];
    int len;
    while ((len = get_line(line, MAXLENGTH))>0)
    {
        reverse(line, len);
        printf("%s\n", line);
    }
    
}

int get_line(char s[], int limit)
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

void reverse(char s[], int len)
{
    int temp;
    for (int i = 0; i < (len/2); i++)
    {
        if (s[i]=='\n')
        {
            s[i] = ' ';
        }
        if (s[len-1-i]=='\n')
        {
            s[len-1-i] = ' ';
        }
        
        temp = s[i];
        s[i] = s[len-2-i];
        s[len-2-i] = temp;
    }
    
}