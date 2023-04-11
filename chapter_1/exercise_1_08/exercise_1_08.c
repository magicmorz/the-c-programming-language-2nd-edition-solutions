#include <stdio.h>
main()
{
    int count = 0, c;
    while ((c = getchar()) != EOF)
    {
        if ((c == '\t') || (c == '\n') || (c == '\0'))
        {
            ++count;
        }
    }

    printf("%d\n", count);
}
 