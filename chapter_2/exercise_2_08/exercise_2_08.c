#include <stdio.h>
#include <math.h>
unsigned righttrot(unsigned short x, int n);
int main ()
{
    printf("%d\n",righttrot(60, 3));
    return 0;
}

unsigned righttrot(unsigned short x, int n)
{
    unsigned short temp = 0;
    unsigned short mask =0;
    unsigned short submask = 0;
    short right_most_bit;
    while (n>0)
    {
        temp = temp >> 1;
        right_most_bit = x % 2;
        submask = right_most_bit*(pow(2,sizeof(mask)*8-1));
        mask = mask | submask;
        temp = temp | mask;
        x = x >> 1;
        n--;
        // reset mask to 0
        mask = mask ^ mask;
    }
    return x | temp;
    
}