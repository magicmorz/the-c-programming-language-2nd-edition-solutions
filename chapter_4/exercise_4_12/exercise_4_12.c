#include <stdio.h>
#define MAXSIZE 100
int main()
{
    int num = 5894; 
    char s[MAXSIZE];
    itoa(s,num, 0);
    printf("%s\n",s);
    return 0;
}


int itoa(char s[], int n, int i)
{
    if (n<0)
    {
        s[0] = '-';
        n = -n;
        i++;
    }
    if (n/10)
    {
        i = itoa(s,n/10, i);
    }
    s[i] = n%10+'0';
    s[i+1]= '\0';
    return ++i;
    
    
}
