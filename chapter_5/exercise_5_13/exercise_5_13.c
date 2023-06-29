#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int get_line(char s[]);

int main(int argc, char const *argv[])
{
    int n = 3;
    if (argc > 1)
    {
        n = atoi(argv[1]) * -1;
    }

    char **pointer_array;
    pointer_array = (char **)malloc(sizeof(char *));

    int i = 0;
    int len = 1;
    char s[40];

    while (get_line(s) != -1)
    {
        pointer_array = (char **)realloc(pointer_array, (++len) * sizeof(char *));
        pointer_array[i] = (char *)malloc(strlen(s) + 1);
        strcpy(pointer_array[i], s);
        i++;
    }
    if (len-1 < n)
    {
        printf("too short\n");
    }
    else
    {
        for (int i = len - n - 1; i < len - 1; i++)
        {
            printf("%s", *(pointer_array + i));
        }
    }

    return 0;
}

int get_line(char s[])
{
    int c, i = 0;
    int end;
    while ((c = getchar()) != '\n')
    {
        if (c == EOF)
        {
            return -1;
        }
        s[i++] = c;
    }
    s[i] = '\n';
    s[i + 1] = '\0';
    return i + 1;
}