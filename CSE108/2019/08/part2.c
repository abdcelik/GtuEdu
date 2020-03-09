#include <stdio.h>

int recursive_pow(int,int);
int getInt(const char*);

int main(void)
{
    int base = getInt("Base : ") , exponent = getInt("Exponent : ");

    printf("Base : %d, Exponent : %d, Result : %d\n",base,exponent,recursive_pow(base,exponent));
    recursive_pow(2,3);

    return 0;
}

int recursive_pow(int base, int exponent)
{
    if(exponent != 0)
        return base * recursive_pow(base,exponent-1);
    return 1;
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}