#include <stdio.h>
main()
{
    char c;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            continue;
        }
        if (c == ' ')
        {
            while ((c = getchar()) == ' ')
            {
                continue;
            }
        }
        else
        {
            printf("%c\n", c);
        }
    }
}
