#include <stdio.h>

int check_prime(int);
int getInt(const char*);

int main(void)
{
    int choice=0,num=0,count=0;

    printf("1. Is it prime or not\n");
    printf("2. Nth prime number\n");
    choice = getInt("Choice : ");

    switch(choice)
    {
        case 1:
            if(check_prime((num = getInt("Enter a positive integer : "))))
                printf("%d is a prime number\n",num);
            else
                printf("%d is not a prime number\n",num);
            break;
        case 2:
            num = getInt("Enter an integer for N : ");

            for(int i=0 ; count < num ; ++i)
                if(check_prime(i))
                    printf("%d. prime number : %d\n",++count,i);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }


    return 0;
}

int check_prime(int n)
{
    if(n < 2)
        return 0;

    for(int i=2 ; i < n ; ++i)
        if(n % i == 0)
            return 0;
    return 1;
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}