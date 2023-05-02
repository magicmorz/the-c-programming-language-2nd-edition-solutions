#include <stdio.h>
#include <ctype.h>
#define STRING_MAX_SIZE 20
int htoi(char s[]);
int get_string(char s[]);
int main()
{
    char s[STRING_MAX_SIZE];
    get_string(s);
    printf("%d\n",htoi(s));
    return 0;
}

int htoi(char s[])
{
    int xnum = 0;
    for (int i = 0; isxdigit(s[i]); i++)
    {
        if (((s[i]=='0')&&(s[i+1]=='x'))||((s[i]=='0')&&(s[i+1]=='X')))
        {
            i++;
            continue;
        }
        
        if(isdigit(s[i]))
        {
            xnum = 16 * xnum + (s[i]-'0');
        }
        else if(islower(s[i]))
        {
            xnum = 16 * xnum + (s[i]-'a'+10);

        }
        else if (isupper(s[i]))
        {
            xnum = 16 * xnum + (s[i]-'A'+10);
        }

    }
    return xnum;
    
}

int get_string(char s[])
{
    int c;
    int i =0;
    while ((c = getchar())!=EOF)
    {
        s[i]= c;
        i++;
    }
    s[i]='\0';
    return i;
}