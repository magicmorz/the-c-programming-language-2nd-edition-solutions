#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define MAXOP 100
#define NUMBER '0'
#define TEXT 'a'
#define MAXVAL 100
#define BUFSIZE 100

int getop(char[]);
void push(double);
double pop(void);
int place_pointer = 0;

int sp = 0;
double val[MAXVAL];
double last_printed_value;

void swap_top_two()
{
    double op1 = pop();
    double op2 = pop();
    push(op1);
    push(op2);
}

double top(void)
{
    if (sp)
    {
        return val[sp - 1];
    }

    else
    {
        printf("stack is empty\n");
    }
}

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void get_line(char s[])
{
    int c, i = 0;
    while ((c = getchar()) != '\n')
    {
        s[i++] = c;
    }
    s[i] = '\n';
    s[i + 1] = '\0';
}

int buf[BUFSIZE];
char bufp = 0;

int main()
{
    int type;
    double op2;
    char s[MAXOP];

    char input_line[MAXVAL];
    get_line(input_line);
    while (strchr(input_line, EOF) == NULL)
    {
        get_line(input_line);

        int j;
        for (int i = 0; input_line[i] != '\0'; i++)
        {
            while ((input_line[i] == ' ' || (input_line[i] == '\t')))
            {
                i++;
            }
            s[j] = input_line[i];
            s[++j] = '\0';

            if (!isdigit(input_line[i]) && input_line[i] != '.' && input_line[i] != '-' && !isalpha(input_line[i]))
            {
                switch (input_line[i])
                {
                case '+':
                    push(pop() + pop());
                    j = 0;
                    continue;
                case '*':
                    push(pop() * pop());
                    j = 0;
                    continue;
                case '/':
                    if (op2 != 0.0)
                    {
                        op2 = pop();
                        push(pop() / op2);
                        j = 0;
                    }
                    else
                        printf("error: zero divisor\n");
                    continue;

                case '%':
                    op2 = pop();
                    if (op2 != 0.0)
                    {
                        push((int)pop() % (int)op2);
                        j = 0;
                    }
                    else
                        printf("error: zero divisor\n");
                    continue;
                case '^':
                    op2 = pop();
                    push(pow(pop(), op2));
                    j = 0;
                    continue;

                case '~':
                    push(sin(pop()));
                    j = 0;
                    continue;
                case '\n':
                    last_printed_value = top();
                    printf("\t%.8g\n", pop());
                    j = 0;
                    continue;
                }
            }

            if (input_line[i] == '-') // if minus
            {
                s[j++] = input_line[i];
                if (!isdigit(input_line[i + 1]))
                {

                    op2 = pop();
                    push(pop() - op2);
                    j = 0;
                }
                else
                    s[++j] = input_line[i];
            }

            if (isalpha(input_line[i])) // if variable
            {
                while (isalpha(input_line[i + 1]))
                {
                    i++;
                    s[j++] = input_line[i];
                }
                s[j] = '\0';
                if (strcmp(s, "top") == 0)
                {
                    printf("%f\n", top());
                    j = 0;
                    continue;
                }
                if (strcmp(s, "swap") == 0)
                {
                    swap_top_two();
                    j = 0;
                    continue;
                }
                if (strcmp(s, "e") == 0)
                {
                    push(exp(pop()));
                    j = 0;
                    continue;
                }
                if (strcmp(s, "last") == 0)
                {
                    push(last_printed_value);
                    j = 0;
                    continue;
                }
                if (strcmp(s, "clear") == 0)
                {
                    for (int i = 0; i < MAXVAL; val[i] = ' ', i++)
                        ;
                    j = 0;
                    continue;
                }
            }
            if (isdigit(input_line[i]))
            {
                while (isdigit(input_line[i + 1]))
                {
                    i++;
                    s[j++] = input_line[i];
                }
            }
            if (input_line[i] == '.')
            {
                while (isdigit(input_line[i + 1]))
                {
                    i++;

                    s[j++] = input_line[i];
                }
            }
            s[j] = '\0';
            printf("%s\n", s);
            push(atof(s));
            j = 0;
        }
    }

    return 0;
}
