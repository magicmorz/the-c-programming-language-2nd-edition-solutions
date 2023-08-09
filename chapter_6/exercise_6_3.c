#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "myfile.txt"

int getword(char *, int);

typedef struct
{
    char *word;
    int *lines;
} word_info;

int main(int argc, char const *argv[])
{
    FILE *fptr;
    char *line = NULL;
    size_t line_length = 0;
    int line_number = 0;

    word_info* word_list = NULL:
    
    // Open a file in read mode
    fptr = fopen(FILENAME, "r");

    if (fptr == NULL) {
        perror("Error opening file");
        return 1;
    }

    int read;
    while ((read = getline(&line, &line_length, fptr))!= -1)
    {
        line_number++;
        // get line from file
        // loop over each word in the line
            // if word is not noise 
                // if not already created, create a word_info object for the word
                // save line number
    }
    
    return 0;
}

int getword(char *word, int lim)
{
    int c, d;
    char *w = word;

    while (isspace(c = getc(stdin)))
        ;
    if (c != EOF)
        *w++ = c;
    if (isalpha(c) || c == '_' || c == '#')
    {
        for (; --lim > 0; w++)
            if (!isalnum(*w = getc(stdin)) && *w != '_')
            {
                ungetc(*w, stdin);
                break;
            }
    }
    else if (c == '\'' || c == '"')
    {
        for (; --lim > 0; w++)
            if ((*w = getc(stdin)) == '\\')
            {
                *++w = getc(stdin);
            }
            else if (*w == c)
            {
                w++;
                break;
            }
            else if (*w == EOF)
            {
                break;
            }
    }
    else if (c == '/')
    {
        if ((d = getch()) == '*')
        {
            c = comment();
        }
        else
        {
            ungetc(d, stdin);
        }
    }
    else if (c == EOF)
    {
        return EOF;
    }

    *w = '\0';
    return word[0];
}