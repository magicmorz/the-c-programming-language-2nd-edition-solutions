#include <stdio.h>

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */
main()
{
    int input_char;
    int state;
    int number_of_lines, number_of_words, number_of_chars;
    number_of_lines = number_of_words=number_of_chars =  0;
    state = OUT;
    while ((input_char = getchar()) != EOF)
    {
        ++number_of_chars;
        if (input_char == ' ' || input_char == '\t')
        {
            state = OUT;
        }
        else if (input_char == '\n')
        {
            state = OUT;
            ++number_of_lines;
        }
        else if (state == OUT)
        {
            state = IN;
            ++number_of_words;
        }
    }
    printf("number of chars is %d \n number of words is %d \n number of lines is %d", number_of_chars, number_of_words, number_of_lines);
}