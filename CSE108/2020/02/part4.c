#include <stdio.h>

int add(int,int);
int substract(int,int);
int multiply(int,int);
int divide(int,int);
int mod(int,int);
int getInt(const char*);
char getChar(const char*);

int main(void)
{
    int num1=0,num2=0;
    char operation = getChar("Please enter an operation sign : ");

    num1 = getInt("First integer number : ");
    num2 = getInt("Second integer number : ");

    switch(operation)
    {
        case '+':
            printf("%d + %d = %d\n",num1,num2,add(num1,num2));
            break;
        case '-':
            printf("%d - %d = %d\n",num1,num2,substract(num1,num2));
            break;
        case '*':
            printf("%d * %d = %d\n",num1,num2,multiply(num1,num2));
            break;
        case '/':
            printf("%d / %d = %d\n",num1,num2,divide(num1,num2));
            break;
        case '%':
            printf("%d %% %d = %d\n",num1,num2,mod(num1,num2));
            break;
        default:
            printf("Error! This operation is not supported.\n");
            break;
    }

    return 0;
}

int add(int n1, int n2)
{
    return n1+n2;
}

int substract(int n1, int n2)
{
    return n1-n2;
}

int multiply(int n1, int n2)
{
    return n1*n2;
}

int divide(int n1, int n2)
{
    return n1/n2;
}

int mod(int n1, int n2)
{
    return n1%n2;
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}

char getChar(const char* text)
{
    char var=0;

    printf("%s",text);
    scanf("%c",&var);

    return var;
}