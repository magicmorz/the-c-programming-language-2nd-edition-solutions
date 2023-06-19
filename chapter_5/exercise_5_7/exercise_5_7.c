#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXSTORE 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines, char *linestore);
void writelines(char *lineptr[], int nlines);
void swap(char *v[], int i, int j);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
main()
{
    char* linestore[MAXSTORE];
    int nlines; /* number of input lines read */
    if ((nlines = readlines(lineptr, MAXLINES, linestore)) >= 0)
    {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000 /* max length of any input line*/
size_t getline1(char line[], size_t max_line_len);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char *linestore)
{
    int len, nlines;
    char *p = linestore, line[MAXLEN];
    char *lines_stop = linestore + MAXSTORE;

    nlines = 0;
    while ((len = getline1(line, MAXLEN)) > 0)
    {
        if (nlines >= maxlines || p+len > lines_stop)
        {
            return -1;
        }
        else
        {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p+=len;
        }
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
    {
        printf("%s\n", *lineptr++);
    }
}

void qsort(char *v[], int left, int right)
{
    int i, last;

    if (left >= right)
    {
        return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
    {
        if (strcmp(v[i], v[left]) < 0)
        {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
size_t getline1(char line[], size_t max_line_len)
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
