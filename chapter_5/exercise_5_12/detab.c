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

    while (--duplicate_argc > 0 && (*++argv)[0] == '-')
    {
        while (c = *++argv[0])
        {
            switch (c)
            {
            case /* constant-expression */:
                /* code */
                break;
            
            default:
                break;
            }
        }
        
    }

    if (argc > 1)
    {
        while ((c = getchar()) != EOF)
        {
            if (c == '\t')
            {
                for (int i = 0; i < atoi(*(argv + 1)); i++)
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
}