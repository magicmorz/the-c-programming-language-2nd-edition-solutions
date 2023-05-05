#include <stdio.h>
#include <limits.h>
#include <math.h>   
unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned invert(unsigned x, int p, int n);
int main()
{
    //printf("%d\n",setbits(0,6,3, 60));
    printf("%d\n",invert(60, 6, 3));
    return 0;
}

unsigned invert(unsigned x, int p, int n)
{
    // get the bits the are needed to be inverted
    // invert them and save in inverted_bits
    unsigned short mask = pow(2,n)-1;
    unsigned short inverted_bits = getbits(x, p, n) ^ mask; 

    // put inverted_bits in the right of the mask
    mask = 0xffff | inverted_bits;

    // put inverted_bits in the left of the mask 
    mask = mask<<(sizeof(mask)*8-(8-p-1));

    // put the inverted_bits at position of the original bits 
    mask = mask >> (sizeof(mask)*8-p-1);


    return x | mask;
    
}

/* getbits: get n bits from position p*/
unsigned getbits(unsigned x, int p, int n)
{
    return (x>>(p+1-n))&~(~0<<n);
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    return (y>>n<<n|getbits(y, p, n));
}
