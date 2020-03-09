#include <stdio.h>

int is_perfect(int);
int getInt(const char*);

int main(void)
{
    int num = getInt("Enter the number : ");

    if(is_perfect(num))
        printf("%d is a perfect number\n",num);
    else
        printf("%d is not a perfect number\n",num);

    return 0;
}

int is_perfect(int num)
{
    int sum=0;

    for(int i=1 ; i < num ; ++i)
        if(num % i == 0)
            sum += i;

    return num == sum;
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}