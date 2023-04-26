#include <stdio.h>
#define BREAKING_POINT 10
#define MAX_LINE 1000

int get_line(char line[]);
void fold(char line[], int len, int breaking_point, int current_pos);
void initialize(char line[], int len);
main()
{
    char line[MAX_LINE];
    int len;
    int last_non_blank_char_pos = 0;
    while ((len = get_line(line)) > 0)
    {
        fold(line, len, BREAKING_POINT, 0);
    }
}

void fold(char line[], int len, int breaking_point, int current_pos)
{
    if (len < BREAKING_POINT-1)
    {
        while (line[current_pos]!='\0')
        {
            putchar(line[current_pos]);
            current_pos++;
        }
        putchar('\n');
        return;
    }
    else
    {
        int i;
        for (i = current_pos; (line[i] != '\0'); i++)
        {
            if (i == 0)
            {
                putchar(line[i]);
            }
            else if ((i % breaking_point != 0) && (i != 0))
            {
                putchar(line[i]);
            }
            else
            {
                break;
            }
        }
        putchar('\n');
        putchar(line[i]);
        fold(line, len - i , BREAKING_POINT, i + 1);
    }
}

int get_line(char line[])
{
    int len = 0;
    int c;
    initialize(line, MAX_LINE);
    while (((c = getchar()) != '\n') && (c != EOF))
    {
        line[len++] = c;
    }
    line[len] = '\0';
    return len;
}

void initialize(char line[], int len)
{
    for (int i = 0; i < len; i++)
    {
        line[i] = 0;
    }
    
}