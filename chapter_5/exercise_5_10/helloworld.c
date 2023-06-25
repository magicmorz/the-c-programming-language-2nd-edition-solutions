#include <stdio.h>
int main(int argc, char const *argv[])
{
    while (--argc > 0)
    {
        printf("%s\n",*++argv);
    }
    
    
    return 0;
}
/*
int main(int argc, char const *argv[]) {
    for (int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    return 0;
}
*/