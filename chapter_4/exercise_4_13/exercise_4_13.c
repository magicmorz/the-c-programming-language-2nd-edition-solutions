#include <stdio.h>
#include <string.h>
#define MAXSIZE 100
int main()
{
    int num = 5894;
    char s[MAXSIZE] = "abcdefg";

   
    reverse(s);
    printf("%s\n", s);
    return 0;
}


int reverse (char s[])
{
    static int i;
    static int j;
    int c;
    if (s[i]!='\0')
    {
        c = s[i++];
        reverse(s);
        s[j++]= c;
    }
    
}