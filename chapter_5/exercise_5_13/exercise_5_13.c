#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 100

int main() {
    int i =0;
    char s[MAXLEN];
    // Allocate memory for the array of pointers
    char** strings = (char**)malloc(sizeof(char*));
    char** new_strings = (char**)realloc(strings, sizeof(char*));
    while (get_line(s)!=-1)
    {
      i++;
      new_strings = (char**)realloc(new_strings, i* sizeof(char*));
      strcpy(new_strings[i], &s);
      
    }
    




    // Allocate memory for each string and assign it to the array
    strings[0] = (char*)malloc(6 * sizeof(char));
    strings[1] = (char*)malloc(6 * sizeof(char));
    strings[2] = (char*)malloc(7 * sizeof(char));

    // Check if the memory allocation for strings was successful
    if (strings[0] == NULL || strings[1] == NULL || strings[2] == NULL) {
        printf("Memory allocation failed.\n");

        // Free previously allocated memory
        free(strings[0]);
        free(strings[1]);
        free(strings[2]);
        free(strings);

        return 1;
    }

    // Initialize the strings
    strcpy(strings[0], "Hello");
    strcpy(strings[1], "World");
    strcpy(strings[2], "OpenAI");

    // Access and print the strings
    for (int i = 0; i < 3; i++) {
        printf("%s\n", strings[i]);
    }

    // Free allocated memory
    free(strings[0]);
    free(strings[1]);
    free(strings[2]);
    free(strings);

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
}