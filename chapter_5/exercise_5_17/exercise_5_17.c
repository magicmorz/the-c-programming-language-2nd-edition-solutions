#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>

#define MAX_NR_OF_LINES 5000
#define MAX_LINE_LEN 1000
#define MAX_NR_OF_FIELDS 100
#define MAX_NR_OF_FIELD_OPTIONS 4
#define INT_MAX_NR_OF_DIGITS (size_t)(floor(log10(labs(INT_MAX))) + 1)

// Field option constants
enum field_option
{
    INDEX,
    ORDER,
    FOLD,
    DIRECTORY
};

// Function prototypes
int parse_arg_list(int argc, char *argv[]);
size_t str_nth_blank_pos(const char *s, size_t n);
char *substr(const char *s, size_t start, size_t end);
size_t read_lines(char *line_ptr[], const size_t max_num_of_lines);
void write_lines(char *line_ptr[], const size_t num_of_lines);
int numcmp(const char *s1, const char *s2);
int estrcmp(const char *s1, const char *s2);
int fieldscmp(const char *s1, const char *s2);
void swap(void *v[], size_t i, size_t j);
void quick_sort(void *v[], size_t start, size_t end, int (*comp)(void *, void *));

// Global variables
int order = 1;     // 1 ascending, -1 descending
int fold = 0;      // 0 case-sensitive, 1 case-insensitive
int directory = 0; // 0 normal, 1 directory
int (*comp)(const char *, const char *) = estrcmp;

int num_of_fields = 0;
int (*fields_comp[MAX_NR_OF_FIELDS])(const char *, const char *);
int fields_options[MAX_NR_OF_FIELDS][MAX_NR_OF_FIELD_OPTIONS];

// Parses command-line arguments and sets the appropriate options
int parse_arg_list(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            for (size_t j = 1; argv[i][j]; ++j)
            {
                if (isdigit(argv[i][j]) && !fields_options[i - 1][INDEX])
                {
                    fields_options[i - 1][INDEX] = atoi(&argv[i][j]);
                    ++num_of_fields;
                    break;
                }

                switch (argv[i][j])
                {
                case 'n':
                    fields_comp[i - 1] = numcmp;
                    break;
                case 'f':
                    fields_options[i - 1][FOLD] = 1;
                    break;
                case 'd':
                    fields_options[i - 1][DIRECTORY] = 1;
                    break;
                case 'r':
                    fields_options[i - 1][ORDER] = -1;
                    break;
                default:
                    return 0; // Invalid option
                }
            }

            if ((num_of_fields || argc > 2) && !fields_options[i - 1][INDEX])
                return 0; // Missing field index
        }
        else
        {
            return 0; // Invalid argument format
        }
    }

    if (num_of_fields && num_of_fields != argc - 1)
        return 0; // Invalid argument count

    comp = (num_of_fields) ? fieldscmp : estrcmp;
    return 1; // Successful parsing
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



// Reads lines of input and stores them in line_ptr array
size_t read_lines(char *line_ptr[], const size_t max_num_of_lines)
{
    size_t num_of_lines = 0;
    char line[MAX_LINE_LEN];

    // Read lines until the maximum number of lines is reached or input ends
    while (num_of_lines < max_num_of_lines && fgets(line, sizeof(line), stdin))
    {
        // Remove the newline character at the end of the line, if present
        size_t line_length = strlen(line);
        if (line_length > 0 && line[line_length - 1] == '\n')
        {
            line[line_length - 1] = '\0';
            --line_length;
        }

        // Allocate memory for the line copy
        char *current_line_copy = malloc(line_length + 1);
        if (current_line_copy == NULL)
        {
            // Memory allocation failed
            return -1;
        }

        // Copy the line to the allocated memory
        strcpy(current_line_copy, line);

        // Store the line copy in the line_ptr array
        line_ptr[num_of_lines++] = current_line_copy;
    }

    return num_of_lines;
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

// Numeric comparison function
int numcmp(const char *s1, const char *s2)
{
    // Convert the input strings to double values
    double nr1 = atof(s1);
    double nr2 = atof(s2);

    // Compare the numeric values
    // Return -1 if nr1 is less than nr2, 1 if nr1 is greater than nr2, and 0 if they are equal
    return order * ((nr1 > nr2) - (nr1 < nr2));
}

// Case-insensitive string comparison function
int estrcmp(const char *s1, const char *s2)
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

        // Perform the comparison, taking into account case-folding option
        int result = fold ? tolower((unsigned char)*s1) - tolower((unsigned char)*s2) : *s1 - *s2;

        if (result != 0)
            return order * result;

        // Move to the next characters in both strings
        ++s1;
        ++s2;
    }

    // Reached the end of one or both strings, consider them equal
    return 0;
}
// Field-based comparison function
int fieldscmp(const char *s1, const char *s2)
{
    int i = 0;

    // Iterate through each field to compare
    while (i < num_of_fields)
    {
        // Get the start and end positions of the current field in s1
        size_t start_s1 = str_nth_blank_pos(s1, fields_options[i][INDEX] - 1);
        size_t end_s1 = str_nth_blank_pos(s1, fields_options[i][INDEX]);

        // Extract the current field from s1
        char *field_s1 = substr(s1, start_s1, end_s1);

        // Get the start and end positions of the current field in s2
        size_t start_s2 = str_nth_blank_pos(s2, fields_options[i][INDEX] - 1);
        size_t end_s2 = str_nth_blank_pos(s2, fields_options[i][INDEX]);

        // Extract the current field from s2
        char *field_s2 = substr(s2, start_s2, end_s2);

        // Set the comparison function, sorting order, case-insensitivity, and directory comparison flag for the current field
        comp = fields_comp[i];
        order = fields_options[i][ORDER];
        fold = fields_options[i][FOLD];
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

// Swaps two elements in an array
void swap(void *v[], size_t i, size_t j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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

int main(int argc, char *argv[])
{
    // Parse command-line arguments
    if (!parse_arg_list(argc, argv))
    {
        puts("Error: invalid arguments.");
        return EXIT_FAILURE;
    }

    size_t num_of_lines;
    char *line_ptr[MAX_NR_OF_LINES];

    // Read lines from input
    if ((num_of_lines = read_lines(line_ptr, MAX_NR_OF_LINES)) != -1)
    {
        // Perform quicksort on the lines
        quick_sort((void **)line_ptr, 0, num_of_lines - 1, (int (*)(void *, void *))comp);

        // Write sorted lines to output
        write_lines(line_ptr, num_of_lines);
    }
    else
    {
        puts("Error: input too large.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
