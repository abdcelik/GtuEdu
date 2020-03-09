#include <stdio.h>

int maxValue(const int*,int);

int main(void)
{
    int size = 5;
    int arr[] = {1,2,5,3,4};

    printf("%d\n",maxValue(arr,size));
    return 0;
}

int maxValue(const int* arr, int size)
{
    if(size == 1)
        return arr[size-1];
    return maxValue(arr,size-1) > arr[size-1] ? maxValue(arr,size-1) : arr[size-1];
}