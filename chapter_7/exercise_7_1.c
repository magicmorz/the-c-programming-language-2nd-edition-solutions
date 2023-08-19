#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
int main(int argc, char const *argv[])
{
    char myString[] = "Lorem Ipsum";
    char* myPtr = myString;
    bool upperToLower;
    if (argc > 1)
    {
        if (*argv[1] == '1')
        {
            upperToLower = true;
        }
        else if (*argv[1] == '0')
        {
            upperToLower = false;
        }
        else
        {
            upperToLower = true;
        }
    }
    else
    {
        upperToLower = true;
    }

    int (*neededFuntion)(int);
    neededFuntion = upperToLower ? &tolower : &toupper;

    while (*myPtr)
    {
        *myPtr = neededFuntion(*myPtr);
        putchar(*myPtr++);
        putchar('\n');
    }

    return 0;
}
