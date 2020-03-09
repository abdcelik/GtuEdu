#include <stdio.h>

int addition(int,int);
int substraction(int,int);
int multiplication(int,int);
double division(int,int);
int power_of_two(int);
int get_integer_from_user(void);
char get_operation_type_from_user(void);

int main(void)
{
    int num1=0,num2=0;

    switch(get_operation_type_from_user())
    {
        case '+':
            printf("Res : %d\n",addition(get_integer_from_user(),get_integer_from_user()));
            break;
        case '-':
            num1 = get_integer_from_user();
            num2 = get_integer_from_user();

            printf("Res : %d\n",substraction(num1,num2));
            break;
        case '*':
            printf("Res : %d\n",multiplication(get_integer_from_user(),get_integer_from_user()));
            break;
            case '/':
            num1 = get_integer_from_user();
            num2 = get_integer_from_user();

            printf("Res : %.2lf\n",division(num1,num2));
            break;
        case '^':
            printf("Res : %d\n",power_of_two(get_integer_from_user()));
            break;
        default:
            printf("Undefined operation!");
            break;
    }
    
    return 0;
}

int addition(int value1, int value2)
{
    return value1+value2;
}

int substraction(int value1, int value2)
{
    return value1-value2;
}

int multiplication(int value1, int value2)
{
    return value1*value2;
}

double division(int dividend, int divisor)
{
    return (double)dividend/divisor;
}

int power_of_two(int exponential)
{
    int res=1;

    for(int i=0 ; i < exponential ; ++i,res *= 2);

    return res;
}

int get_integer_from_user(void)
{
    int var=0;

    printf("Number : ");
    scanf("%d",&var);

    return var;
}

char get_operation_type_from_user(void)
{
    char operation=0;

    printf("Operation : ");
    scanf("%c",&operation);

    return operation;
}