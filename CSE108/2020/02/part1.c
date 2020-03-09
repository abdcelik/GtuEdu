#include <stdio.h>

int largestNumber(int[]);

int main(void)
{
    int arr[3];

    printf("Please enter three integer numbers : ");
    scanf("%d%d%d",&arr[0],&arr[1],&arr[2]);

    printf("The largest number : %d\n",largestNumber(arr));

    return 0;
}

int largestNumber(int arr[])
{
    int max = arr[0];
    
    for(int i=1 ; i < 3 ; ++i)
        if(arr[i] > max)
            max = arr[i];

    return max;
}