#include <stdio.h>
/* print Fahrenheit-Celsius table
    for fahr = 0, 20, ..., 300; floating point version */

main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("Fahrenheit\t Celsius\n");
    for (fahr = upper; fahr >= lower; fahr = fahr - step)
    {
        printf("%5.0f %17.1f\n", fahr, (5.0 / 9.0) * (fahr - 32.0));
    }
}
