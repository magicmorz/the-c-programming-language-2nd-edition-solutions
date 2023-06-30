#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
double atof(const char* str);
void qsort(void *lineptr[], int left, int right,
			int (*comp)(void *, void *), int reverse);

int numcmp(char *s1, char *s2);

main(int argc, char *argv[])
{
	int nlines;
	int numeric = 0;
	int reverse = 0;

	if (argc > 1 && strcmp(argv[1], "-n") == 0)
		numeric = 1;
	else if (argc > 1 && strcmp(argv[1], "-r") == 0)
	{
		reverse = 1;
	}
	else if (argc > 1 && strcmp(argv[1], "-rn") == 0)
	{
		reverse = 1;
		numeric = 1;
	}
	else if (argc > 1 && strcmp(argv[1], "-rn") == 0)
	{
		reverse = 1;
		numeric = 1;
	}

	if (argc > 2 && strcmp(argv[2], "-r") == 0)
		reverse = 1;
	
		
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort((void **) lineptr, 0, nlines-1,
			(int (*)(void*, void*))(numeric ? numcmp : strcmp), reverse);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}

void qsort(void *v[], int left, int right,
			int (*comp)(void *, void *), int reverse)
{
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((reverse==0)?((*comp)(v[i], v[left]) < 0):((*comp)(v[i], v[left]) > 0))
			swap(v, ++last, i);
		/**if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);*/
	swap(v, left, last);
	qsort(v, left, last-1, comp, reverse);
	qsort(v, last+1, right, comp, reverse);
}

void swap(void *v[], int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

#define MAXLEN 10000

int readlines(char *lineptr[], int maxlines)
{
	int mygetline(char *, int);
	char *alloc(int);

	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;
	while ((len = mygetline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}

	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

int mygetline(char *s, int lim)
{
	int c;
	char *t = s;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*t++ = c;

	if (c == '\n')
		*t++ = c;

	*t = '\0';
	return t - s;
}

#define ALLOCSIZE 1000000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	} else
		return 0;
}

void afree(char *p)
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}
double atof(const char* str) {
    double result = 0.0;
    double sign = 1.0;
    int exponent = 0;
    int i = 0;

    // Skip leading whitespace
    while (isspace(str[i]))
        i++;

    // Handle optional sign
    if (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign = -1.0;
        i++;
    }

    // Process digits before the decimal point
    while (isdigit(str[i])) {
        result = result * 10.0 + (str[i] - '0');
        i++;
    }

    // Process the decimal point and digits after it
    if (str[i] == '.')
    {
        i++;
        double factor = 0.1;
        while (isdigit(str[i])) {
            result = result + (str[i] - '0') * factor;
            factor *= 0.1;
            i++;
        }
    }

    // Process the optional exponent part
    if (str[i] == 'e' || str[i] == 'E') {
        i++;
        int expSign = (str[i] == '-') ? -1 : 1;
        if (str[i] == '-' || str[i] == '+')
            i++;
        while (isdigit(str[i])) {
            exponent = exponent * 10 + (str[i] - '0');
            i++;
        }
        exponent *= expSign;
    }

    // Apply the sign and exponent to the result
    result *= sign;
    while (exponent > 0) {
        result *= 10.0;
        exponent--;
    }
    while (exponent < 0) {
        result *= 0.1;
        exponent++;
    }

    return result;
}