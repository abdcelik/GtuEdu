#include <stdio.h>

int fact(int);
int combination(int,int);
int permutation(int,int);
int getInt(const char*);

int main(void)
{
    int num1 = getInt("Enter a number (M): ");
    int num2 = getInt("Enter a number (N): ");

    printf("C(%d,%d) : %d\n",num1,num2,combination(num1,num2));
    printf("P(%d,%d) : %d\n",num1,num2,permutation(num1,num2));

    return 0;
}

int fact(int num)
{
    if(num)
        return num*fact(num-1);
    return 1;
}

int combination(int m, int n)
{
    return fact(m)/(fact(n)*fact(m-n));
}

int permutation(int m, int n)
{
    return fact(m)/fact(m-n);
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}