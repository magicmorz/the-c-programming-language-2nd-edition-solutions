#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist
{
    struct nlist *next;
    char *name;
    char *defn;
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];
unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
int *undef(char *name);

int main(int argc, char const *argv[])
{
    char *name = "Zinedine Zidane";
    char *defn = "bro";
    struct nlist *pt = install(name, defn);
    undef("Zinedine Zidane");
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
