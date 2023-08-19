#include <stdarg.h>
#include <stdio.h>

void minprintf(char *fmt, ...);

int main()
{
	minprintf("int: %d, double: %f, string: %s\n", 1, 0.123, "Hello");

	return 0;
}


void minprintf(char *fmt, ...) {
    va_list ap;         // Declare a va_list type variable to hold the argument list
    char *p, *sval;     // Declare pointers to characters and strings
    int ival;           // Declare an integer variable
    double dval;        // Declare a double variable

    va_start(ap, fmt);  // Initialize the va_list variable with the last named parameter

    for (p = fmt; *p; p++) { // Loop through the format string
        if (*p != '%') {
            putchar(*p);     // If not '%', print the character and continue to the next iteration
            continue;
        }
        
        switch (*++p) {  // Move past '%', then examine the next character
        case 'd':         // Format specifier for integer
            ival = va_arg(ap, int);  // Get the integer argument from the list
            printf("%d", ival);     // Print the integer value
            break;
        case 'f':         // Format specifier for double
            dval = va_arg(ap, double);  // Get the double argument from the list
            printf("%f", dval);         // Print the double value
            break;
        case 's':         // Format specifier for string
            for (sval = va_arg(ap, char *); *sval; sval++) {
                putchar(*sval);  // Print each character of the string
            }
            break;
        case 'u':         // Format specifier for unsigned integer
            ival = va_arg(ap, unsigned int);  // Get the unsigned integer argument from the list
            printf("%u", ival);               // Print the unsigned integer value
            break;
        case 'o':         
            ival = va_arg(ap, unsigned int);  
            printf("%o", ival);               
            break;
        default:
            putchar(*p);     // Print the character following '%' if it doesn't match any format specifier
            break;
        }
    }

    va_end(ap);  // Clean up the va_list variable
}