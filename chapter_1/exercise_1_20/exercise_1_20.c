#include <stdio.h>
#define MAXLENGTH 1000
#define TAB_SIZE_IN_SPACES 4
void detab(char line[]);
int get_line(char line[]);
main()
{
    char line[1000];
    int len;
    while ((len = get_line(line)) > 0)
    {
        detab(line);
        printf("%s\n", line);
    }
}

int get_line(char line[])
{
    int c;
    int i = 0;
    while (((c = getchar()) != EOF) && (c != '\n'))
    {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    return i;
}

void detab(char line[])
{
    for (int i = 0; line[i]!='\n'; i++)
    {
        if (line[i]=='\t')
        {
            line[i]= ' ';
            line[i+1]= ' ';
            line[i+2]= ' ';
            line[i+3]= ' ';
        }
        
    }
    
}