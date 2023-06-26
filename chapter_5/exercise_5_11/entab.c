#include <stdio.h>
#define TAB_SIZE_IN_SPACES 8

void entab(int argc, char *argv[]);
int main(int argc, char *argv[])
{
    entab(argc, argv);
    return 0;
}

void entab(int argc, char *argv[])
{
    int count_blanks = 0;
    int tabs;
    int spaces;
    int c;
    if (argc <= 1)
    {
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
    else
    {
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
                        count_blanks = count_blanks + atoi(*(argv + 1));
                    }
                    c = getchar();
                }
                tabs = count_blanks / atoi(*(argv + 1));
                spaces = count_blanks % atoi(*(argv + 1));
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
}