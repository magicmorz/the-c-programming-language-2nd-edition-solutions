#include <stdio.h>
void month_day(int year, int yearday, int *pmonth, int *pday);
int day_of_year(int year, int month, int day);
main()
{
    int m;
    int d;
    month_day(1988, 60, &m, &d);
    printf("%d %d\n", m, d);
    printf("%d", day_of_year(1988, 2, 29));
    return 0;
}

static char daytab[2][13] =
    {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int check_day_of_year_valid(int year, int yearday)
{
    int leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    if (leap)
    {
        if (yearday > 366 || yearday <= 0)
        {
            return 0;
        }
    }
    else
    {
        if (yearday > 365 || yearday <= 0)
        {
            return 0;
        }
    }

    return 1;
}

int check_day_of_month_valid(int year, int month, int day)
{
    int leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if ((day <= daytab[leap][month]) && (day > 0) && month >0 && month <= 12)
    {
        return 1;
    }
    return 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (!check_day_of_month_valid(year, month, day))
    {
        return -1;
    }
    for (i = 0; i < month; i++)
    {
        day += daytab[leap][i];
    }
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    if (!check_day_of_year_valid(year, yearday))
    {
        *pmonth = -1;
        *pday = -1;
    }
    else
    {
        for (i = 1; yearday > daytab[leap][i]; i++)
        {
            yearday -= daytab[leap][i];
        }
        *pmonth = i;
        *pday = yearday;
    }
}
