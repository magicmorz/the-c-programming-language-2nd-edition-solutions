#include <stdio.h>
#include <ctype.h>
#define MAXLINE 100
int main()
{
    double sum, atof(char[]);
    char line[MAXLINE];
    int getline1(char line[], int max);

    sum = 0;
    while (getline1(line, MAXLINE) > 0)
    {
        printf("\t%g\n", sum += atof(line));
    }

    return 0;
}

double atof(char s[])
{
    double value_after_point = 0, power, value_until_point, len_after_point = 0;
    int i, sign;

    for (i = 0; i < isspace(s[i]); i++)
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
    {
        i++;
    }
    for (value_until_point = 0.0; isdigit(s[i]); i++)
    {
        value_until_point = 10.0 * value_until_point + (s[i] - '0');
    }
    if (strchr(s, 'e') || strchr(s, 'E'))
    {
        if ((s[i] == '.'))
        {
            i++;
            for (; isdigit(s[i]); i++)
            {
                value_after_point = 10.0 * value_after_point + (s[i] - '0');
                len_after_point ++;
            }
            if ((s[i] == 'e') || (s[i] == 'E'))
            {
                i++;
                sign = (s[i] == '-') ? -1 : 1;
                if (sign == -1)
                    i++;
                for (power = 0; isdigit(s[i]); i++)
                {
                    power = 10.0 * power + (s[i] - '0');
                }
                return (sign == -1) ? value_until_point / pow(10, power) +value_after_point / pow(10, power+ len_after_point) : value_until_point * pow(10, power) + value_after_point;
            } 
        }
        else if ((s[i] == 'e') || (s[i] == 'E'))
        {
            i++;
            sign = (s[i] == '-') ? -1 : 1;
            if (sign == -1)
                i++;
            for (power = 0; isdigit(s[i]); i++)
            {
                power = 10.0 * power + (s[i] - '0');
            }
            printf("%f\n", power);
            return (sign == -1) ? value_until_point / pow(10, power) + value_after_point / pow(10, power+len_after_point) : value_until_point * pow(10, power) + value_after_point;
        }
    }
    else if (s[i] == '.')
    {
        i++;

        for (power = 1.0; isdigit(s[i]); i++)
        {
            value_after_point = 10.0 * value_after_point + (s[i] - '0');
            power *= 10.0;
        }
        return sign * value_until_point/ power + value_after_point  / pow(10, power);
    }
    else
    {
        return sign * value_until_point;
    }
}

/*getline: get line into s, return length*/
int getline1(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    {
        s[i++] = c;
    }
    if (c == '\n')
    {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}