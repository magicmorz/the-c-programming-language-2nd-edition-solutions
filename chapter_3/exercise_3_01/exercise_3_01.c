#include <stdio.h>
int binary_sort(int sorted_array[], int len, int target);
int main()
{
    int myNumbers[] = {25, 50, 75, 100};
    printf("%d\n", binary_sort(myNumbers, 4, 75));
}

int binary_sort(int sorted_array[], int len, int target)
{
    int start = 0;
    int end = len - 1;
    int middle = (start + end) / 2;
    while ((start != end) && (target != sorted_array[middle]))
    {
        middle = (start + end) / 2;

        if (target > sorted_array[middle])
        {
            start = middle + 1;
        }
        else
        {
            end = middle - 1;
        }
    }
    return (target == sorted_array[middle]) ? middle : -1;
}