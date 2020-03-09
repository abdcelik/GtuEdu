#include <stdio.h>

typedef enum{false,true}bool;

bool isOdd(int);
int getInt(const char*);

int main(void)
{
    int num = getInt("Please enter an integer : ");

    if(isOdd(num))
        printf("%d is and odd number\n",num);
    else
        printf("%d is an even number\n",num);
        
    return 0;
}

bool isOdd(int n)
{
    return n % 2 == 1;
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}