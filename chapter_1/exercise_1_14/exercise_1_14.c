#include <stdio.h>
main()
{
    int input_char;
    int histogram[128];
    for (int i = 0; i < 128; ++i)
    {
        histogram[i] = 0;
    }

    while ((input_char = getchar()) != EOF)
    {
        ++histogram[input_char];
    }
    for (int i = 0; i < 128; ++i)
    {
        printf("%d ", i);
        for (int j = 0; j <= histogram[i]; ++j)
        {
            printf("*");
        }
        printf("\n");
    }
}