#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "myfile.txt"
#define MAX_WORD_LENGTH 30

int getword(char *word, int lim, char **line_temp);
int comment(char **line_temp);
int compare(const void *a, const void *b);
typedef struct
{
    char *word;
    int *lines;
    int count;
    int number;
} word_info;

int check_word_already_in_list(word_info *list, char *word);
int size = 0;
int main(int argc, char const *argv[])
{

    char *line = NULL;
    size_t line_length = 0;
    int line_number = 0;
    word_info *word_list = NULL;
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

        while (getword(current_word, MAX_WORD_LENGTH, &line)) // loop over each word in the line
        {
            // if this word already has a word_info object
            if ((pos = check_word_already_in_list(word_list, current_word)) != -1)
            {
                // increament number of appreances
                (word_list + pos)->count++;
                // save line number
                (word_list + pos)->lines[(word_list + pos)->count - 1] = line_number; // save line number
            }
            else // if not already created, create a word_info object for the word
            {
                size++;
                word_list = (word_info *)realloc(word_list, size * sizeof(word_info));
                word_list[size - 1].number = size - 1;
                // save word
                word_list[size - 1].word = (char *)malloc(strlen(current_word) * sizeof(char));
                strcpy(word_list[size - 1].word, current_word);
                // increament numner of appreances
                (word_list + size - 1)->count = 1;

                word_list[size - 1].lines = (int *)malloc(sizeof(int));
                // Assign line number to the last element of the lines array
                word_list[size - 1].lines[word_list[size - 1].count - 1] = line_number;
            }
        }
        line_number++;
    }

    qsort(word_list, size, sizeof(word_list[0]), compare);

    for (int i = 0; i < size; i++)
    {
        printf("\"%s\" appeared %d times\n", word_list[i].word,word_list[i].count);
    }

    fclose(fptr);
    return 0;
}

// Comparison function for qsort
int compare(const void *a, const void *b) {
    const word_info *structA = (const word_info *)a;
    const word_info *structB = (const word_info *)b;
    
    if (structA->count < structB->count) return -1;
    if (structA->count > structB->count) return 1;
    return 0;
}

int check_word_already_in_list(word_info *list, char *word)
{
    word_info *list_ptr = list;
    if (list == NULL)
        return -1;
    int i = 0;
    while (i < size)
    {
        if (strcmp(list_ptr->word, word) == 0)
        {
            return list_ptr->number;
        }
        i++;
        list_ptr++;
    }
    return -1;
}

int getword(char *word, int lim, char **line_temp)
{
    int c, d;
    char *w = word;

    while (isspace(c = *(*line_temp)++))
        ;

    if (c != EOF)
        *w++ = c;

    if (isalpha(c) || c == '_' || c == '#')
    {
        for (; --lim > 0; w++)
        {
            if (!isalnum(*w = *(*line_temp)++) && *w != '_')
            {
                (*line_temp)--;
                break;
            }
        }
    }
    else if (c == '\'' || c == '"')
    {
        for (; --lim > 0; w++)
        {
            if ((*w = *(*line_temp)++) == '\\')
            {
                *++w = *(*line_temp)++;
            }
            else if (*w == c)
            {
                break;
            }
        }
    }
    else if (c == '/')
    {
        if ((d = *(*line_temp)++) == '*')
        {
            c = comment(line_temp);
        }
        else
        {
            (*line_temp)--;
        }
    }
    else if (c == EOF)
    {
        return EOF;
    }

    *w = '\0';
    return word[0];
}

int comment(char **line_temp)
{
    int c;
    while ((c = *(*line_temp)++) != EOF)
    {
        if (c == '*')
        {
            if ((c = *(*line_temp)++) == '/')
            {
                break;
            }
            else
            {
                (*line_temp)--;
            }
        }
    }
    return c;
}