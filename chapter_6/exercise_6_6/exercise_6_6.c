#include <stdio.h>
#define HASHSIZE 101
#define MAX_WORD_LENGTH 30
static struct nlist *hashtab[HASHSIZE];
unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
int *undef(char *name);
struct nlist
{
    struct nlist *next;
    char *name;
    char *defn;
};

int main(int argc, char const *argv[])
{
    char current_word[MAX_WORD_LENGTH];
    char c;
    char prev = NULL;

    char *name = (char*)malloc(sizeof(char));
    char *defn = (char*)malloc(sizeof(char));
    while ((c = getc(stdin))!=EOF)
    {
        if ((c == '#') && ((prev == NULL) || (prev == '\n')))
        {
            getword(current_word, MAX_WORD_LENGTH);
            if (strcmp(current_word, "define") == 0)
            {
                getword(name, MAX_WORD_LENGTH);
                getword(defn, MAX_WORD_LENGTH);
                install(name,defn);
            }
        }

        prev = c;
    }

    return 0;
}

int *undef(char *name)
{
    struct nlist *node;
    struct nlist *prev_node = NULL;
    int index = hash(name);

    for (node = hashtab[index]; node != NULL; prev_node = node, node = node->next)
    {
        if (strcmp(node->name, name) == 0)
        {
            free(node->name);
            free(node->defn);
            if (prev_node == NULL)
            {
                hashtab[index] = node->next;
            }
            else
            {
                prev_node->next = node->next;
            }
            free(node);
            return 1;
        }
    }
    return 0;
}

unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; ++s)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    {
        if (strcmp(s, np->name) == 0)
            return np;
    }
    return NULL;
}

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL)
    {
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else
        free((void *)np->defn);

    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
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
        if ((d = getc(stdin)) == '*')
        {
            c = block_comment();
        }

        else
        {
            ungetc(d, stdin);
        }
        if ((d = getc(stdin)) == '/')
        {
            c = line_comment();
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

int block_comment(void)
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

int line_comment(void)
{
    int c;
    while ((c = getc(stdin)) != EOF)
    {
        if (c == '\n')
        {
            break;
        }
    }
    return c;
}
