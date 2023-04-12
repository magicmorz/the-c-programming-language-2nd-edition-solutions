#include <stdio.h>
main()
{
    char input_char;
    while ((input_char = getchar()) != EOF)
    {
        if (input_char == '\t')
        {
            printf("\\t");
        }
        else if (input_char == '\b')
        {
            printf("\\b");
        }
        else
        {
            printf("%c", input_char);
        }
    }
}
