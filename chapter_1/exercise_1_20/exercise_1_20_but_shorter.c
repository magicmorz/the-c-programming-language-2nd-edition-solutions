#include <stdio.h>
#define TAB_SIZE_IN_SPACES 4
void detab();
main()
{
    detab();
}

void detab()
{
    int c;
    while ((c=getchar())!=EOF)
    {
        if (c == '\t')
        {
            for (int i = 0; i < TAB_SIZE_IN_SPACES; i++)
            {
                printf(" ");
            }
        }
        else
        {
            putchar(c);
        }
        
    }
}