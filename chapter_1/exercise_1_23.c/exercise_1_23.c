#include <stdio.h>
#define PROGRAM_MAX_SIZE 1000
int get_c_program(char program[], int program_max_size);
int initialize_array(char program[], int size);
int remove_comments(char program[]);
int remove_line_comments(char program[]);
int remove_comment_blocks(char program[]);
int remove_from_index_to_next_newline(char program[], int index);
int count_qoutation_marks_in_line_before_index(char program[], int index);
int count_qoutation_marks_in_program_before_index(char program[], int index);
int remove_from_index_to_block_end(char program[], int index);

int main()
{
    char program[PROGRAM_MAX_SIZE];
    initialize_array(program, PROGRAM_MAX_SIZE);
    get_c_program(program, PROGRAM_MAX_SIZE);
    remove_comments(program);
    printf("\n%s", program);
    return 0;
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
    program[position]=' ';
    position++;
    program[position]=' ';
    position++;
    while (((program[position] != '*')&&(program[position] != '/')) && (program[position] != EOF))
    {
        program[position] = ' ';
        position++;
    }
    program[position]=' ';
    position++;
    program[position]=' ';
    position++;
}


int remove_comments(char program[])
{
    remove_line_comments(program);
    remove_comment_blocks(program);

}


