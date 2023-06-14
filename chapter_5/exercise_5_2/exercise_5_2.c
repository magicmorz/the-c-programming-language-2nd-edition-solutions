#include <ctype.h>
#include <stdio.h>
#include <math.h>
#define BUFSIZE 100

int getch(void);
void ungetch(int);

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

/* getfloat: get next float from input into *pn */
int getfloat(float *pn)
{
    int c, sign, temp;

    while (isspace(c = getch())) /* skip white space */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        *pn = -1;
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
    {
        temp = c;
        c = getch();
        if (!isdigit(c))
        {
            *pn = -1;
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
    {
        *pn = 10 * *pn + (c - '0');
    }
    if (c == '.')
    {
        c = getch();
       for (int i = -1 ; isdigit(c); c = getch(), i--)
        {
            *pn =  *pn + ((float)(c - '0')*(pow(10, i)));
        }
    }

    *pn *= sign;
    if (c != EOF)
    {
        ungetch(c);
    }
    return c;
}

int main()
{
    int type;
    float p;

    while ((type = getfloat(&p)) != EOF)
    {
        printf("result is %f\n", p);
    }
    return 0;
}