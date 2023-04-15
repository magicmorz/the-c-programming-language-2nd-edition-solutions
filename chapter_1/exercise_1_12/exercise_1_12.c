// print the input one word per line
#include <stdio.h>
main()
{
    char input_char;
    while ((input_char = getchar()) != EOF)
    {
        if (input_char == '\n' || input_char == ' ')
        {
            printf("\n");
        }
        else
        {
            printf("%c", input_char);
        }
        
    }
    
}

