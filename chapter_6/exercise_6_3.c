#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "myfile.txt"
#define MAX_WORD_LENGTH 30

int getword(char *word, int lim, FILE *fptr);
typedef struct
{
    char *word;
    int *lines;
    int count;
} word_info;

int check_word_already_in_list(word_info *list, char *word);

int main(int argc, char const *argv[])
{

    char *line = NULL;
    size_t line_length = 0;
    int line_number = 0;
    int size = 1;
    word_info *word_list = NULL;
    word_list = (word_info *)malloc(sizeof(word_info) * size);

    // Open a file in read mode
    FILE *fptr;
    fptr = fopen(FILENAME, "r");
    if (fptr == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    int read;
    while ((read = getline(&line, &line_length, fptr)) != -1) // get line from file
    {

        // loop over each word in the line
        // if not already created, create a word_info object for the word
        // save line number

        char current_word[MAX_WORD_LENGTH];
        int pos;
        
        while (getword(current_word, MAX_WORD_LENGTH, fptr)) // loop over each word in the line
        {
            // if this word already has a word_info object
            if ((pos = check_word_already_in_list(word_list, current_word)) != -1)
            {
                // increament numner of appreances
                (word_list + pos)->count++;
                // make space for a new line number
                (word_list + pos)->lines = (word_info *)realloc(word_list + pos, (word_list + pos)->count);
                // save line number
                (word_list + pos)->lines[(word_list + pos)->count] = line_number; // save line number
            }
            else // if not already created, create a word_info object for the word
            {
                size++;
                word_list = (word_info *)realloc(word_list + size, size * sizeof(word_info));
                // save word
                strcpy(word_list[size].word, current_word);
                // increament numner of appreances
                word_list->count = 1;
                // make space for a new line number
                (word_list + size)->lines = (word_info *)realloc(word_list + size, (word_list + size)->count);
                // save line number
                (word_list + size)->lines[(word_list + size)->count] = line_number;
            }
        }

        line_number++;
    }

    return 0;
}

int check_word_already_in_list(word_info *list, char *word)
{
    word_info *list_ptr = list;
    int size = sizeof(list_ptr) / sizeof(*list_ptr);
    int i = 0;
    while (list_ptr)
    {
        if (strcmp(list_ptr++->word, word) == 0)
        {
            return i;
        }
        i++;
    }
    return -1;
}

int getword(char *word, int lim, FILE *fptr)
{
    int c, d;
    char *w = word;

    while (isspace(c = getc(fptr)))
        ;
    if (c != EOF)
        *w++ = c;
    if (isalpha(c) || c == '_' || c == '#')
    {
        for (; --lim > 0; w++)
            if (!isalnum(*w = getc(fptr)) && *w != '_')
            {
                ungetc(*w, fptr);
                break;
            }
    }
    else if (c == '\'' || c == '"')
    {
        for (; --lim > 0; w++)
            if ((*w = getc(fptr)) == '\\')
            {
                *++w = getc(fptr);
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
        if ((d = getc(fptr)) == '*')
        {
            c = comment();
        }
        else
        {
            ungetc(d, fptr);
        }
    }
    else if (c == EOF)
    {
        return EOF;
    }

    *w = '\0';
    return word[0];
}

int comment(FILE *fptr)
{
    int c;
    while ((c = getc(fptr)) != EOF)
    {
        if (c == '*')
        {
            if ((c = getc(fptr)) == '/')
            {
                break;
            }
            else
            {
                ungetc(c, fptr);
            }
        }
    }
    return c;
}
