#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_SIZE 100
void get_string(char s[MAX_SIZE]);
void expand(char s1[], char s2[]);
int main()
{
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];
    get_string(s1);
    expand(s1, s2);
    printf("%s\n", s2);
    return 0;
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

void expand(char s1[], char s2[])
{
    int i,j;
    for (i = 0, j = 0; i < strlen(s1); i++)
    {
        if ((isdigit(s1[i]))&&(s1[i+1]=='-')&&(isdigit(s1[i+2])))
        {
           for (int character = s1[i]; character < s1[i+2]; character++, j++)
           {
                s2[j] = character;
           }
           i++;
           
        }

        else if ((isupper(s1[i]))&&(s1[i+1]=='-')&&(isupper(s1[i+2])))
        {
             for (int character = s1[i]; character < s1[i+2]; character++, j++)
           {
                s2[j] = character;
           }
           i++;
        }
        else if ((islower(s1[i]))&&(s1[i+1]=='-')&&(islower(s1[i+2])))
        {
             for (int character = s1[i]; character < s1[i+2]; character++, j++)
           {
                s2[j] = character;
           }
           i++;
        }
        else
        {
            s2[j]=s1[i];
            j++;
        }
        
        
    }
    s2[j]= '\0';

}