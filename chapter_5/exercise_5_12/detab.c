#include <stdio.h>
#define TAB_SIZE_IN_SPACES 4
void detab(int argc, char const *argv[]);
int main(int argc, char const *argv[])
{
    detab(argc, argv);
}

void detab(int argc, char const *argv[])
{
    int startposition = 0;
    int duplicate_argc = argc;
    int c;
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
    

    if (start > 0)
    {
        int i = 0;
        while ((c = getchar()) != EOF)
        {
            i++;
            if (c == '\t' && i >= start)
            {
                for (int i = 0; i < num; i++)
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
    else
    {
        while ((c = getchar()) != EOF)
        {
            if (c == '\t')
            {
                for (int i = 0; i < num; i++)
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
}