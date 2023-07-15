#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <limits.h>

#define MAX_NUMBER_OF_FIELDS 100
#define MAX_NR_OF_LINES 5000
#define MAX_NUMBER_OF_FIELD_OPTIONS 4
#define INT_MAX_NR_OF_DIGITS (size_t)(floor(log10(labs(INT_MAX))) + 1)
#define MAX_LINE_LEN 1000

int parse_argumets(int argc, char const *argv[]);
void quick_sort(void *v[], size_t start, size_t end, int (*comp)(void *, void *));
int numcmp(const char *s1, const char *s2);
int estrcmp(const char *s1, const char *s2);
size_t read_lines(char *line_ptr[], const size_t max_nr_of_lines);
int fieldscmp(const char *s1, const char *s2);
size_t get_line(char line[], size_t max_line_len);
char *substr(const char *s, size_t start, size_t end);
void swap(void *v[], size_t i, size_t j);
size_t str_nth_blank_pos(const char *s, size_t n);

int (*comp)(const char *, const char *) = estrcmp;

enum field_options
{
    INDEX,
    ORDER,
    FOLD,
    DIRECTORY
};
int fields_options[MAX_NUMBER_OF_FIELDS][MAX_NUMBER_OF_FIELD_OPTIONS];
int (*fields_compare[MAX_NUMBER_OF_FIELDS])(const char *, const char *);
int order = 1;
int fold = 0;
void write_lines(char *line_ptr[], const size_t nr_of_lines);
int directory = 0;
int num_of_fields = 0;

int main(int argc, char const *argv[])
{
   // Parse command-line arguments
    if (!parse_argumets(argc, argv))
    {
        puts("Error: invalid arguments.");
        return EXIT_FAILURE;
    }

    size_t nr_of_lines;
    char *line_ptr[MAX_NR_OF_LINES];

    // Read lines from input
    if ((nr_of_lines = read_lines(line_ptr, MAX_NR_OF_LINES)) != -1)
    {
        // Perform quicksort on the lines
        quick_sort((void **)line_ptr, 0, nr_of_lines - 1, (int (*)(void *, void *))comp);

        // Write sorted lines to output
        write_lines(line_ptr, nr_of_lines);
    }
    else
    {
        puts("Error: input too large.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int parse_argumets(int argc, char const *argv[])
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (argv[i][0] == '-')
            {
                for (size_t j = 1; argv[i][j] != '\0'; j++)
                {
                    if (isdigit(argv[i][j]))
                    {
                        char field_index_as_string[INT_MAX_NR_OF_DIGITS];
                        int k = 0;
                        while (isdigit(argv[i][j]))
                        {
                            field_index_as_string[k] = argv[i][j];
                            j++;
                        }
                        fields_options[i - 1][INDEX] = atoi(field_index_as_string);
                        num_of_fields++;
                    }
                    else
                    {
                        switch (argv[i][j])
                        {
                        case 'n':
                            fields_compare[i - 1] = numcmp;
                            break;
                        case 'r':
                            fields_options[i - 1][ORDER] = -1;
                            break;
                        case 'f':
                            fields_options[i - 1][FOLD] = 1;
                            break;
                        case 'd':
                            fields_options[i - 1][DIRECTORY] = 1; // Directory comparison
                            break;

                        default:
                            return 0;
                            break;
                        }
                    }
                }
            }
            else
            {
                return 0; // Invalid argument
            }
        }

        // Set the comparison function based on the parsed options
        if (num_of_fields && num_of_fields == argc - 1)
        {
            // compare using fields
            comp = fieldscmp;
        }
        else if (argc > 2)
        {
            return 0; // Invalid argument count
        }

        return 1; // Successful parsing
    }
}
// Writes lines to stdout
void write_lines(char *line_ptr[], const size_t nr_of_lines)
{
    for (size_t i = 0; i < nr_of_lines; ++i)
    {
        puts(line_ptr[i]);
        free(line_ptr[i]);
    }
}
// Quicksort algorithm for sorting an array
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


// Reads lines of input and stores them in line_ptr array
size_t read_lines(char *line_ptr[], const size_t max_nr_of_lines)
{
    size_t line_length;
    size_t nr_of_lines = 0;

    char *current_line = (char *)malloc(MAX_LINE_LEN);
    char *current_line_copy = NULL;

    while ((line_length = get_line(current_line, MAX_LINE_LEN)))
    {
        if (nr_of_lines >= max_nr_of_lines || (current_line_copy = (char *)malloc(line_length)) == NULL)
        {
            return -1;
        }
        else
        {
            current_line[line_length - 1] = '\0';
            strcpy(current_line_copy, current_line);
            line_ptr[nr_of_lines++] = current_line_copy;
        }
    }

    free(current_line);

    return nr_of_lines;
}

// Swaps two elements in an array
void swap(void *v[], size_t i, size_t j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// Reads a line of input from stdin
size_t get_line(char line[], size_t max_line_len)
{
    int c;
    size_t i;

    for (i = 0; i < max_line_len - 1 && (c = getc(stdin)) != EOF && c != '\n'; ++i)
    {
        line[i] = c;
    }

    if (c == '\n')
    {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';

    return i;
}

// Numeric comparison function
int numcmp(const char *s1, const char *s2)
{
    double nr1 = atof(s1);
    double nr2 = atof(s2);

    if (nr1 < nr2)
    {
        return order * -1;
    }
    else if (nr1 > nr2)
    {
        return order * 1;
    }

    return 0;
}

// Case-insensitive string comparison function
int estrcmp(const char *s1, const char *s2)
{
    while (*s1 != '\0' && *s2 != '\0')
    {
        if (directory)
        {
            while (*s1 != '\0' && !isalnum(*s1) && !isspace(*s1))
            {
                ++s1;
            }
            while (*s2 != '\0' && !isalnum(*s2) && !isspace(*s2))
            {
                ++s2;
            }
        }

        int result = fold ? tolower(*s1) - tolower(*s2) : *s1 - *s2;
        if (result == 0)
        {
            ++s1;
            ++s2;
        }
        else
        {
            return order * result;
        }
    }

    return 0;
}

// Field-based comparison function
int fieldscmp(const char *s1, const char *s2)
{
    int i = 0;
    while (i < num_of_fields)
    {
        // Get the start position of the field in s1
        size_t start_s1 = str_nth_blank_pos(s1, fields_options[i][INDEX] - 1);
        // Get the end position of the field in s1
        size_t end_s1 = str_nth_blank_pos(s1, fields_options[i][INDEX]);
        // Extract the field from s1 using start and end positions
        char *field_s1 = substr(s1, start_s1, end_s1);

        // Get the start position of the field in s2
        size_t start_s2 = str_nth_blank_pos(s2, fields_options[i][INDEX] - 1);
        // Get the end position of the field in s2
        size_t end_s2 = str_nth_blank_pos(s2, fields_options[i][INDEX]);
        // Extract the field from s2 using start and end positions
        char *field_s2 = substr(s2, start_s2, end_s2);

        // Set the comparison function for the field
        comp = fields_compare[i];
        // Set the sorting order for the field
        order = fields_options[i][ORDER];
        // Set the case-insensitivity flag for the field
        fold = fields_options[i][FOLD];
        // Set the directory comparison flag for the field
        directory = fields_options[i][DIRECTORY];

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
// Finds the position of the nth blank space in a string
size_t str_nth_blank_pos(const char *s, size_t n)
{
    size_t pos = 0;
    while (n && *s != '\0')
    {
        if (*s == ' ' || *s == '\t')
        {
            do
            {
                ++pos;
                ++s;
            } while (*s == ' ' || *s == '\t');

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

// Extracts a substring from a string
char *substr(const char *s, size_t start, size_t end)
{
    if (start > end)
    {
        return NULL;
    }

    const size_t len = end - start;
    char *dest = (char *)malloc(len + 1);

    for (size_t i = start; i < end && s[i] != '\0'; ++i)
    {
        *dest = s[i];
        ++dest;
    }
    *dest = '\0';

    return dest - len;
}