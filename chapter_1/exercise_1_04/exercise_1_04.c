#include <stdio.h>

main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    celsius = lower;

    printf("Celsius\t\t Fahrenheit\n");
    while (celsius <= upper)
    {

        fahr = 32.0 + (celsius * (9.0 / 5.0));
        printf("%5.0f %17.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}
