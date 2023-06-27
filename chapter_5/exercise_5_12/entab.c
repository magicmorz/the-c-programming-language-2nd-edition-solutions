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
    int startposition = 0;
    int duplicate_argc = argc;
    int start = 0;
    int num = TAB_SIZE_IN_SPACES;

    
        while ((duplicate_argc-- > 0)&&(c = *(argv[0])))
        {
            if (c == '-')
            {
                
                start = atoi(*argv);
                if (start<0)
                {
                    start *= -1;
                }
                
            }
            else if (c == '+')
            {
                num = atoi(*argv);
            }
            argv++;
        }
        int i = 0;
        while ((c = getchar()) != EOF)
        {
            i++;
            if ((i>=start)&&((c == ' ') || (c == '\t')))
            {
                while ((c == ' ') || (c == '\t'))
                {
                    if (c == ' ')
                    {
                        count_blanks++;
                    }
                    else if (c == '\t')
                    {
                        count_blanks = count_blanks + num;
                    }
                    c = getchar();
                }
                tabs = count_blanks / num;
                spaces = count_blanks % num;
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