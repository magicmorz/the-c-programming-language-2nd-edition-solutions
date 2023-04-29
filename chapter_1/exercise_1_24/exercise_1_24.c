#include <stdio.h>
#define PROGRAM_MAX_SIZE 1000
#define TRUE 1
#define FALSE 0
int get_c_program(char program[], int program_max_size);
int initialize_array(char program[], int size);
int remove_comments(char program[]);
int remove_line_comments(char program[]);
int remove_comment_blocks(char program[]);
int remove_from_index_to_next_newline(char program[], int index);
int count_qoutation_marks_in_line_before_index(char program[], int index);
int count_qoutation_marks_in_program_before_index(char program[], int index);
int remove_from_index_to_block_end(char program[], int index);
int remove_all_quoted_including_quotation_marks(char no_comment_program[]);
int check_no_quotation_marks(char clean_program[]);
int check_closing_for_each_open_parantheses(char clean_program[], int start_index, int nesting_level);
int check_closing_for_each_open_curly_brackets(char clean_program[], int start_index, int nesting_level);
int check_closing_for_each_open_bracket(char clean_program[], int start_index, int nesting_level);
int check_clean_program_validation(char clean_program[]);

int main()
{
    char program[PROGRAM_MAX_SIZE];
    initialize_array(program, PROGRAM_MAX_SIZE);
    printf("\nEnter C program\n");
    while ((get_c_program(program, PROGRAM_MAX_SIZE)) != EOF)
    {
        remove_comments(program);
        remove_all_quoted_including_quotation_marks(program);
        printf("\n%s", program);
        if (check_clean_program_validation(program) == TRUE)
        {
            printf("\nProgram is VALID\n");
        }
        else
        {
            printf("\nProgram is NOT VALID\n");
        }
        printf("\nEnter EOF to exit, any other key to continue\n");
        int c = getchar();
        if (c == EOF)
        {
            break;
        }

        initialize_array(program, PROGRAM_MAX_SIZE);
        printf("\nEnter C program\n");
    }

    return 0;
}

int check_clean_program_validation(char clean_program[])
{
    if (check_no_quotation_marks(clean_program))
    {
        if (check_closing_for_each_open_parantheses(clean_program, 0, 0) == 0)
        {
            if (check_closing_for_each_open_curly_brackets(clean_program, 0, 0) == 0)
            {
                if (check_closing_for_each_open_bracket(clean_program, 0, 0) == 0)
                {
                    return TRUE;
                }
            }
        }
    }
    else
    {
        return FALSE;
    }
}

int check_closing_for_each_open_bracket(char clean_program[], int start_index, int nesting_level)
{
    if (clean_program[start_index] == '\0')
    {
        return nesting_level;
    }
    if (clean_program[start_index] == '[')
    {
        return check_closing_for_each_open_bracket(clean_program, start_index + 1, nesting_level + 1);
    }
    if (clean_program[start_index] == ']')
    {
        if (nesting_level == 0)
        {
            return -1;
        }
        else
        {
            return check_closing_for_each_open_bracket(clean_program, start_index + 1, nesting_level - 1);
        }
    }
    return check_closing_for_each_open_bracket(clean_program, start_index + 1, nesting_level);
}

int check_closing_for_each_open_curly_brackets(char clean_program[], int start_index, int nesting_level)
{

    if (clean_program[start_index] == '\0')
    {
        return nesting_level;
    }
    if (clean_program[start_index] == '{')
    {
        return check_closing_for_each_open_curly_brackets(clean_program, start_index + 1, nesting_level + 1);
    }
    if (clean_program[start_index] == '}')
    {
        if (nesting_level == 0)
        {
            return -1;
        }
        else
        {
            return check_closing_for_each_open_curly_brackets(clean_program, start_index + 1, nesting_level - 1);
        }
    }
    return check_closing_for_each_open_curly_brackets(clean_program, start_index + 1, nesting_level);
}

int check_closing_for_each_open_parantheses(char clean_program[], int start_index, int nesting_level)
{

    if (clean_program[start_index] == '\0')
    {
        return nesting_level;
    }
    if (clean_program[start_index] == '(')
    {
        return check_closing_for_each_open_parantheses(clean_program, start_index + 1, nesting_level + 1);
    }
    if (clean_program[start_index] == ')')
    {
        if (nesting_level == 0)
        {
            return -1;
        }
        else
        {
            return check_closing_for_each_open_parantheses(clean_program, start_index + 1, nesting_level - 1);
        }
    }
    return check_closing_for_each_open_parantheses(clean_program, start_index + 1, nesting_level);
}

int check_no_quotation_marks(char clean_program[])
{
    int i = 0;
    while (clean_program[i] != '\0')
    {
        if ((clean_program[i] == '\'') || (clean_program[i] == '\"'))
        {
            return FALSE;
        }
        i++;
    }
    return TRUE;
}

int remove_all_quoted_including_quotation_marks(char no_comment_program[])
{
    int i = 0;
    int quotation_start;
    int inside_quotation = FALSE;
    while (no_comment_program[i] != '\0')
    {
        if (no_comment_program[i] == '\'')
        {
            inside_quotation = TRUE;
            quotation_start = i;
            i++;
            while (inside_quotation)
            {
                if ((no_comment_program[i] != '\'') && (no_comment_program[i] != '\0'))
                {
                    no_comment_program[i] = ' ';
                    i++;
                }
                else if (no_comment_program[i] == '\'')
                {
                    inside_quotation = FALSE;
                    no_comment_program[i] = ' ';
                    no_comment_program[quotation_start] = ' ';
                    i++;
                }
                else
                {
                    inside_quotation = FALSE;
                    no_comment_program[i] = ' ';
                    i++;
                }
            }
        }
        else if (no_comment_program[i] == '\"')
        {
            inside_quotation = TRUE;
            quotation_start = i;
            i++;
            while (inside_quotation)
            {
                if ((no_comment_program[i] != '\"') && (no_comment_program[i] != '\0'))
                {
                    no_comment_program[i] = ' ';
                    i++;
                }
                else if (no_comment_program[i] == '\"')
                {
                    inside_quotation = FALSE;
                    no_comment_program[i] = ' ';
                    no_comment_program[quotation_start] = ' ';
                    i++;
                }
                else
                {
                    inside_quotation = FALSE;
                    no_comment_program[i] = ' ';
                    i++;
                }
            }
        }
        else
        {
            i++;
        }
    }
}

int get_c_program(char program[], int program_max_size)
{
    int i = 0;
    while ((program[i] = getchar()) != EOF)
    {
        i++;
    }
}

int count_qoutation_marks_in_line_before_index(char program[], int index)
{
    int count_qoutation_marks = 0;
    int position = index - 1;
    int new_line_position;
    while ((program[position] != '\n') && (position >= 0))
    {
        if (program[position] == '"')
        {
            count_qoutation_marks++;
        }
        position--;
    }
    return count_qoutation_marks;
}

int remove_line_comments(char program[])
{
    for (int i = 0; program[i] != '\0'; i++)
    {
        if ((program[i] == '/') && (program[i + 1] == '/'))
        {
            // if there is a even number of " chars before in the same line, the "//" is a start of a comment
            if (count_qoutation_marks_in_line_before_index(program, i) % 2 == 0)
            {
                // remove all the chars from the index to next '\n'
                remove_from_index_to_next_newline(program, i);
            }
        }
    }
}
int remove_from_index_to_next_newline(char program[], int index)
{
    while ((program[index] != '\n') && (program[index]) != EOF)
    {
        program[index] = ' ';
        index++;
    }
}

int initialize_array(char program[], int size)
{
    for (int i = 0; i < size; i++)
    {
        program[i] = '\0';
    }
}
int remove_comment_blocks(char program[])
{
    for (int i = 0; program[i] != '\0'; i++)
    {
        if ((program[i] == '/') && (program[i + 1] == '*'))
        {
            // if there is a even number of " chars before, the "/*" is a start of a comment block
            if (count_qoutation_marks_in_program_before_index(program, i) % 2 == 0)
            {
                // remove all the chars from the index to next '*/'
                remove_from_index_to_block_end(program, i);
            }
        }
    }
}

int count_qoutation_marks_in_program_before_index(char program[], int index)
{
    int count_qoutation_marks = 0;
    int position = index - 1;
    int new_line_position;
    while (position >= 0)
    {
        if (program[position] == '"')
        {
            count_qoutation_marks++;
        }
        position--;
    }
    return count_qoutation_marks;
}

int remove_from_index_to_block_end(char program[], int index)
{
    int position = index;
    program[position] = ' ';
    position++;
    program[position] = ' ';
    position++;
    while (((program[position] != '*') && (program[position] != '/')) && (program[position] != EOF))
    {
        program[position] = ' ';
        position++;
    }
    program[position] = ' ';
    position++;
    program[position] = ' ';
    position++;
}

int remove_comments(char program[])
{
    remove_line_comments(program);
    remove_comment_blocks(program);
}