#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct key
{
    char *word;
    int count;
} keytab[] = {
    {"auto", 0}, {"break", 0}, {"case", 0}, {"char", 0}, {"const", 0}, {"continue", 0}, {"default", 0}, {"double", 0}, {"else", 0}, {"enum", 0}, {"extern", 0}, {"float", 0}, {"for", 0}, {"goto", 0}, {"if", 0}, {"int", 0}, {"long", 0}, {"register", 0}, {"return", 0}, {"short", 0}, {"signed", 0}, {"sizeof", 0}, {"static", 0}, {"struct", 0}, {"switch", 0}, {"typedef", 0}, {"union", 0}, {"unsigned", 0}, {"void", 0}, {"volatile", 0}, {"while", 0}};

char *variable_types[] = {"int", "long", "short", "double", "char"};

#define NKEYS (sizeof keytab / sizeof keytab[0])

int getword(char *, int);
int binsearch(char *, struct key *, int);
char *variable_names[MAXWORD];
main()
{
    int n;
    char word[MAXWORD];
    int i = 0;
    while (getword(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]))
        {
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
            {
                if (strcmp(word, variable_types[0])==0)
                {
                    if (getword(word, MAXWORD) != EOF)
                    {
                        if (isalpha(word[0]))
                        {
                            // Allocate memory for each word before copying
                            variable_names[i] = (char *)malloc(strlen(word) + 1);
                            if (variable_names[i] != NULL)
                            {
                                strcpy(variable_names[i], word);
                                i++;
                            }
                            else
                            {
                                // Handle memory allocation failure, e.g., print an error message
                                printf("Memory allocation failed for word: %s\n", word);
                            }
                        }
                    }
                }
            }
        }
    }

    for (i = 0; i < MAXWORD; i++)
        printf("%s\n", variable_names[i]);

    return 0;
}

int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
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

int comment(void)
{
    int c;
    while ((c = getc(stdin)) != EOF)
    {
        if (c == '*')
        {
            if ((c = getc(stdin)) == '/')
            {
                break;
            }
            else
            {
                ungetc(c, stdin);
            }
        }
    }
    return c;
}
