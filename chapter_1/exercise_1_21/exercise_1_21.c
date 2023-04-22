#include <stdio.h>
#define TAB_SIZE_IN_SPACES 8    

void entab();   
main()
{
    entab();
}

void entab()
{
    int count_blanks = 0;
    int tabs;
    int spaces;
    int c;
    while ((c = getchar()) != EOF)
    {
        if ((c == ' ') || (c == '\t'))
        {
            while ((c == ' ') || (c == '\t'))
            {
                if (c == ' ')
                {
                    count_blanks++;
                }
                else if (c == '\t')
                {
                    count_blanks = count_blanks + TAB_SIZE_IN_SPACES;
                }
                c = getchar();
            }
            tabs = count_blanks / TAB_SIZE_IN_SPACES;
            spaces = count_blanks % TAB_SIZE_IN_SPACES;
            for (int i = 0; i < tabs; i++)
            {
                printf("\t");
            }
            for (int i = 0; i < spaces; i++)
            {
                printf(" ");
            }
            tabs = 0;
            spaces = 0;
            count_blanks = 0;
            
        }

        printf("%c", c);
    }
}