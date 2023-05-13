#include <stdio.h>
#define MAX_SIZE 100
void get_string(char s[MAX_SIZE]);
void escape(char s[], char t[]);
int main()
{
    char s[MAX_SIZE];
    char t[MAX_SIZE];
    get_string(s);
    escape(s, t);
    printf("%s\n", t);
    de_escape(s, t);
    printf("%s\n", t);
    return 0;
}

void escape(char s[], char t[])
{
    int i = 0;
    int j = 0;
    while (s[i] != '\0')
    {
        switch (s[i])
        {
        case '\n':
            t[j] = '\\';
            j++;
            t[j] = 'n';
            j++;
            i++;
            break;

        case '\t':
            t[j] = '\\';
            j++;
            t[j] = 't';
            j++;
            i++;
            break;

        default:
            t[j] = s[i];
            j++;
            i++;
            break;
        }
    }
    t[j] = '\0';
}

void de_escape(char s[], char t[])
{
    int i = 0;
    int j = 0;
    while (s[i] != '\0')
    {
        switch (s[i])
        {
        case '\\':
            switch (s[i + 1])
            {
            case 'n':
                t[j] = '\n';
                j++;
                i+=2;
                break;
            case 't':
                t[j] = '\t';
                j++;
                i+=2;
                break;
            default:
                break;
            }
            break;
        default:
            t[j] = s[i];
            j++;
            i++;
            break;
        }
    }
    t[j] = '\0';
}

void get_string(char s[MAX_SIZE])
{
    int c;
    int i = 0;
    for (i = 0; ((c = getchar()) != EOF) && i < MAX_SIZE; i++)
    {
        s[i] = c;
    }

    s[i] = '\0';
}