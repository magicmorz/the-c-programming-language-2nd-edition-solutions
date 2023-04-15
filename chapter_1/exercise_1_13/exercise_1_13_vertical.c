#include <stdio.h>

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */
main()
{
    int input_char, state, current_word_length, max_element = 0;
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

    for (int i = 1; i <= 10; ++i)
    {
        if (length_histogram[i] > length_histogram[max_element])
        {
            max_element = i;
        }
    }

    for (int i = length_histogram[max_element]; i >= 0; --i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (length_histogram[j]>=i)
            {
                printf("* ");
            }
            else
            {
                printf("  ");
            }
            
        }
        printf("\n");
    }

    for (int i = 0; i < 10 ; i++)
    {
        printf("%d ", i);
    }
    
}