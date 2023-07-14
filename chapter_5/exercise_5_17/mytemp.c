#include <stdio.h>
#define MAX_NUMBER_OF_FIELDS 100
#define MAX_NUMBER_OF_FIELD_OPTIONS 4

int parse_argumets(int argc, char const *argv[]);

enum field_options {INDEX, ORDER , FOLD, DIRECTORY};
int fields_options [MAX_NUMBER_OF_FIELDS][MAX_NUMBER_OF_FIELD_OPTIONS];

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

int parse_argumets(int argc, char const *argv[])
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (*(argv+i)=='-')
            {
                for (int j = 0; *(argv+i)[j]!= '\0'; j++)
                {
                    /* code */
                }
                
            }
            else
            {
                return -1; // Invalid argument
            }
            
        }
        
    }
    
}