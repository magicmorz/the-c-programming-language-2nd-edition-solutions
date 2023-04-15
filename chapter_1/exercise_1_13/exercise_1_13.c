#include <stdio.h>

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */
main()
{
    int input_char, state, current_word_length;
    int length_histogram[10];

    current_word_length = 0;
    state = OUT;

    for (int i = 0; i < 10; ++i)
    {
        length_histogram[i] = 0;
    }

    while ((input_char = getchar()) != EOF)
    {
        if (input_char == ' ' || input_char == '\t')
        {
            state = OUT;
            ++length_histogram[current_word_length];
            current_word_length = 0;
        }
        else if (input_char == '\n')
        {
            state = OUT;
            ++length_histogram[current_word_length];
            current_word_length = 0;
        }
        else if (state == OUT)
        {
            state = IN;
        }
        if (state == IN)
        {
            ++current_word_length;
        }
    }

    for (int i = 0; i < 10; ++i)
    {
        printf("%d ", i);
        for (int j = 0; j <= length_histogram[i]; ++j)
        {
            printf("*");
        }
        printf("\n");
        
    }
}