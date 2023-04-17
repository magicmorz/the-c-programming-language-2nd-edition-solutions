#include <stdio.h>

float fahrenheit_to_celcius(float fahrenheit);

main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;

    printf("Fahrenheit\t Celsius\n");
    while (fahr <= upper)
    {
        celsius = fahrenheit_to_celcius(fahr);
        printf("%5.0f %17.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}

float fahrenheit_to_celcius (float fahrenheit)
{
    return (5.0 / 9.0) * (fahrenheit - 32.0);
}
