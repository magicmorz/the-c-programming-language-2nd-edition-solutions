#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

int sp = 0;
double val[MAXVAL];

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
        return val [sp-1];
       //printf("%f\n", val[sp-1]);
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

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    i = 0;

    if (c == '-')
    {
        s[i] = c;
        if (!isdigit(c = getch()))
        {
            ungetch(c);
            return '-';
        }
        else
            s[++i] = c;
    }
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
    printf("%s\n", s);
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            if (op2 != 0.0)
            {
                op2 = pop();
                push(pop() / op2);
            }
            else
                printf("error: zero divisor\n");
            break;

        case '%':
            op2 = pop();
            if (op2 != 0.0)
            {
                push((int)pop() % (int)op2);
            }
            else
                printf("error: zero divisor\n");
            break;

        case 't':
            printf("%f\n",top());
            break;

         case 's':
            swap_top_two();
            break;

        case 'c':
            for (int i = 0; i < MAXVAL; val[i] = ' ', i++)
                ;
            break;

        case '\n':
            printf("\t%.8g\n", pop());
            break;
        }
    }
    return 0;
}