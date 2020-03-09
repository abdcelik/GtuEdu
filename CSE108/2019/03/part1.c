#include <stdio.h>

int inverseNumber(int);
int digitNumber(int);
int power(int,int);

int main(void)
{
    int num = 12345;

    printf("%d -- inverse : %d\n",num,inverseNumber(num));
    return 0;
}

int inverseNumber(int num)
{
    int digit=0;

    if(num == 0)
        return 0;
    else
        digit = digitNumber(num);

    return (num%10)*power(10,digit-1) + inverseNumber(num/10);
}

int digitNumber(int num)
{
    int digit = 0;
    
    for(; num ; num /= 10 , ++digit);

    return digit;
}

int power(int base, int exponential)
{
    int res = 1;

    for(int i=0 ; i < exponential ; ++i , res *= base);

    return res;
}