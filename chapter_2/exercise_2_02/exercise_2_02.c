#include <stdio.h>
#define MAX_LINE_LEN 15
enum boolean
{
    FALSE,
    TRUE
};
int get_line(char line[]);
int main()
{
    char line[MAX_LINE_LEN];
    int len;

    while ((len = get_line(line)) > 0)
    {
        printf("%s\n", line);
    }

    return 0;
}

int get_line(char s[])
{
    int i;
    int c;
    int condition = TRUE;
    for (i = 0; condition == TRUE; ++i)
    {
        // &&  &&
        if (i < MAX_LINE_LEN - 1)
        {
            if ((c = getchar()) != '\n')
            {
                if (c != EOF)
                {
                    s[i] = c;
                }
                else
                {
                    condition = FALSE;
                    break;
                }
            }
            else
            {
                condition = FALSE;
                break;
            }
        }
        else
        {
            condition = FALSE;
            break;
        }
    }

    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}
