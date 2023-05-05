#include <stdio.h>
#include <limits.h>
unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);
int main()
{
    printf("%d\n",setbits(0,6,3, 60));
    return 0;
}

/* getbits: get n bits from position p*/
unsigned getbits(unsigned x, int p, int n)
{
    return (x>>(p+1-n))&~(~0<<n);
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{/*
    x = getbits(y, p, n);
    y = y >> n;
    y = y << n;
    y = y |x;
    return y;*/
    return (y>>n<<n|getbits(y, p, n));
}
