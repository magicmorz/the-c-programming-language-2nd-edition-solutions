#include <stdio.h>
#include <ctype.h>
#define MAXLINE 100
#define OCTLEN 6

int inc(int pos, int n);

int main(int argc, char const *argv[])
{
    int c, pos;

    pos = 0;
    while ((c = getchar()) != EOF)
    {
        if (iscntrl(c) || c == ' ')
        {
            if (pos + OCTLEN > MAXLINE)
            {
                putchar('\n');
                pos = 0;
            }
            
            printf("\\%03o", c);

            if (c == '\n')
            {
                putchar('\n');
                pos = 0;
            }
            else
            {
                putchar(c);
                pos = inc(pos, 1);
            }
        }
        else
        {
            if (pos + 1 > MAXLINE)
            {
                putchar('\n');
                pos = 0;
            }
            
            putchar(c);
            pos = inc(pos, 1);
        }
    }

    return 0;
}

int inc(int pos, int n)
{
    if (pos + n <= MAXLINE)
    {
        return pos + n;
    }
    else
    {
        putchar('\n');
        return n;
    }
}
