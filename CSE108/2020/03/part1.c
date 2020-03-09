#include <stdio.h>

int getInt(const char*);

int main(void)
{
    int num1 = getInt("Enter first number : ");
    int num2 = getInt("Enter second number : ");

    for(int i=0 ; i < num2 ; ++i)
        printf("%d * %d = %d\n",num1,i+1,num1*(i+1));

    return 0;
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}