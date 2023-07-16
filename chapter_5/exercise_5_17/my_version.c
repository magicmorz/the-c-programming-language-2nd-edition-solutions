#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_NUM_OF_DIGITS (size_t)(floor(log10(labs(INT_MAX))) + 1)
#define MAX_NUM_OF_FIELDS 100
#define MAX_NUM_OF_OPTIONS 4
#define MAX_NUM_OF_LINES 100
#define MAX_LINE_LEN 50

enum options
{
    INDEX,
    ORDER,
    FOLD,
    DIRECTORY
};

// function declarations
int parse_arguments(int argc, char const *argv[]);
int numcmp(const char *, const char *);
int fieldscmp(const char *, const char *);
int insensitive_strcmp(const char *, const char *);
int read_lines(char* line_ptr[], const size_t max_num_of_lines);
void quick_sort(void *v[], size_t start, size_t end, int (*comp)(void *, void *));
void swap(void *v[], size_t i, size_t j);
// globals
int options_per_field[MAX_NUM_OF_FIELDS][MAX_NUM_OF_OPTIONS];
int (*cmp_func_per_field[MAX_NUM_OF_FIELDS])(const char  *, const char *);

int order = 1;
int fold = 0;
int directory = 1;
int num_of_fields = 0;
int (*comp)(const char *, const char *) = insensitive_strcmp;
int parse_arguments(int argc, char const *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            for (size_t j = 1; argv[i][j] != '\0'; j++)
            {
                if (isdigit(argv[i][j]) && !options_per_field[i][INDEX])
                {
                    char field_index_as_str[MAX_NUM_OF_DIGITS];
                    int k = 0;
                    while (isdigit(argv[i][j]))
                    {
                        field_index_as_str[k] = argv[i][j];
                        j++;
                    }
                    j--; // now it is not a digit
                    num_of_fields++;
                    options_per_field[i-1][INDEX] = atoi(field_index_as_str);
                }
                else
                {
                    switch (argv[i][j])
                    {
                    case 'n':
                        cmp_func_per_field[i - 1] = numcmp;
                        break;
                    case 'r':
                        options_per_field[i-1][ORDER] = -1;
                        break;
                    case 'f':
                        options_per_field[i-1][FOLD] = 1;
                        break;
                    case 'd':
                        options_per_field[i-1][DIRECTORY] = 1;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        else
        {
            return 0; // Invalid argument format
        }
        if ((num_of_fields || argc > 2) && !options_per_field[i-1][INDEX])
        {
            return 0;
        }
        comp = (num_of_fields) ? fieldscmp : insensitive_strcmp;
    }

    return 1;
}
// Swaps two elements in an array
void swap(void *v[], size_t i, size_t j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
int read_lines(char* line_ptr[], const size_t max_num_of_lines)
{
    size_t num_of_lines = 0;
    char line[MAX_LINE_LEN];

    while (num_of_lines < max_num_of_lines && fgets(line, sizeof(line), stdin))
    {
        size_t line_len = strlen(line);
        if (line_len>0 && line[line_len-1] == '\n')
        {
            line[line_len-1] = '\0';
            line_len--;
        }
        char* current_line_copy = malloc(line_len +1);
         if (current_line_copy == NULL)
        {
            // Memory allocation failed
            return -1;
        }
        strcpy(current_line_copy, line);
        line_ptr[num_of_lines++] = current_line_copy;
    }

    return num_of_lines;
    
}
void quick_sort(void *v[], size_t start, size_t end, int (*comp)(void *, void *))

{
    if ((long)start >= (long)end)
    {
        return;
    }

    swap(v, start, (start + end) / 2);

    size_t last = start;
    for (size_t i = start + 1; i <= end; ++i)
    {
        if ((*comp)(v[i], v[start]) < 0)
        {
            swap(v, ++last, i);
        }
    }

    swap(v, start, last);
    quick_sort(v, start, last - 1, comp);
    quick_sort(v, last + 1, end, comp);
}

int numcmp(const char *s1, const char *s2)
{
    double n1 = atof(s1);
    double n2 = atof(s2);
    return order *((n1>n2)-(n1<n2));
}
// Extracts a substring from a string
char *substr(const char *s, size_t start, size_t end)
{
    if (start > end || s == NULL)
    {
        return NULL; // Invalid input or NULL string, return NULL
    }

    const size_t len = end - start;
    char *dest = malloc(len + 1); // Allocate memory for the destination string

    if (dest == NULL)
    {
        return NULL; // Memory allocation failed, return NULL
    }

    strncpy(dest, s + start, len); // Copy the substring from source to destination
    dest[len] = '\0'; // Add null-terminating character at the end of the destination string

    return dest; // Return the extracted substring
}
// Finds the position of the nth blank space in a string
size_t str_nth_blank_pos(const char *s, size_t n)
{
    size_t pos = 0;

    while (n && *s != '\0')
    {
        if (isspace(*s))
        {
            ++pos;

            // Skip consecutive whitespace characters
            while (isspace(*s))
            {
                ++s;
            }

            --n;
        }
        else
        {
            ++pos;
            ++s;
        }
    }

    return pos;
}

// Field-based comparison function
int fieldscmp(const char *s1, const char *s2)
{
    int i = 0;

    // Iterate through each field to compare
    while (i < num_of_fields)
    {
        // Get the start and end positions of the current field in s1
        size_t start_s1 = str_nth_blank_pos(s1, options_per_field[i][INDEX] - 1);
        size_t end_s1 = str_nth_blank_pos(s1, options_per_field[i][INDEX]);

        // Extract the current field from s1
        char *field_s1 = substr(s1, start_s1, end_s1);

        // Get the start and end positions of the current field in s2
        size_t start_s2 = str_nth_blank_pos(s2, options_per_field[i][INDEX] - 1);
        size_t end_s2 = str_nth_blank_pos(s2, options_per_field[i][INDEX]);

        // Extract the current field from s2
        char *field_s2 = substr(s2, start_s2, end_s2);

        // Set the comparison function, sorting order, case-insensitivity, and directory comparison flag for the current field
        comp = cmp_func_per_field[i];
        order = options_per_field[i][ORDER];
        fold = options_per_field[i][FOLD];
        directory = options_per_field[i][DIRECTORY];

        // Compare the extracted fields using the specified options
        int comp_result = comp(field_s1, field_s2);

        // Free the memory allocated for field_s1
        free(field_s1);
        // Free the memory allocated for field_s2
        free(field_s2);

        if (comp_result == 0)
        {
            ++i; // Move to the next field if the current fields are equal
        }
        else
        {
            return comp_result; // Return the comparison result if the fields are not equal
        }
    }

    return 0; // All fields are equal, return 0
}


int insensitive_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2)
    {
        if (directory)
        {
            // Skip non-alphanumeric and non-whitespace characters in directory comparison
            while (*s1 && !isalnum(*s1) && !isspace(*s1))
                ++s1;
            while (*s2 && !isalnum(*s2) && !isspace(*s2))
                ++s2;
            
        }
        int result = fold? tolower((int)s1) - tolower((int)s2) : *s1-*s2;

        if (result != 0)
        {
            return order * result;
        }

        ++s1;
        ++s2;
        
    }
    return 0;
}
// Writes lines to stdout
void write_lines(char *line_ptr[], const size_t num_of_lines)
{
    for (size_t i = 0; i < num_of_lines; ++i)
    {
        puts(line_ptr[i]);
        free(line_ptr[i]);
    }
}

int main(int argc, char const *argv[])
{
    if (!parse_arguments(argc, argv))
    {
        printf("Arguments Error!\n");
    }

    size_t num_of_lines;
    char * line_ptr[MAX_NUM_OF_LINES];
    if ((num_of_lines=read_lines(line_ptr, MAX_NUM_OF_LINES))!=-1)
    {    
        quick_sort((void**)line_ptr, 0, num_of_lines-1,(int (*)(void *, void *))comp);
        write_lines(line_ptr, num_of_lines);
    }
    
    
    return 0;
}
