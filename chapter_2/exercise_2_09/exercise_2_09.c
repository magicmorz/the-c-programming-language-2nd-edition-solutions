# include <stdio.h>
int bitcount(unsigned x);
int main()
{
    printf("%d\n", bitcount(5));
    return 0;
}

int bitcount(unsigned x)
{
    int b;
    // x &= (x-1) deletes the rightmost 1 bit in x (in two's complement number system because 
    // (X-1) is the same as x but the rightmost 1 is 0
    // the result of x & (x-1) is the same as x but with a deleted rightmost 1 bit
    for (b = 0; x!=0; x &= (x-1))
    {
        b++;        
    }
    return b;
    
}