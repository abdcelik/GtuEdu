#include <stdio.h>

typedef enum{false,true}bool;

int calcPrimeNumber(int);
int calcCoPrimeNumber(int);
int updateNumber(int);
bool isPrime(int);
bool isCoPrime(int,int);
int getInt(const char*);

int main(void)
{
    int num = getInt("Number : ");

    printf("%-10s%-10s%-15s%-20s\n","Step","Value","No of Primes","No of co-primes");

    for(int i=0 ; num != 1 ; ++i)
    {
        printf("%-10d%-10d%-15d%-20d\n",i+1,num,calcPrimeNumber(num),calcCoPrimeNumber(num));
        num = updateNumber(num);
    }

    return 0;
}

int calcPrimeNumber(int num)
{
    int count=0;

    for(int i=2 ; i < num ; ++i)
        if(isPrime(i))
            ++count;
    return count;
}

int calcCoPrimeNumber(int num)
{
    int count=0;

    for(int i=2 ; i < num ; ++i)
        if(isCoPrime(i,num))
            ++count;
    return count;
}

int updateNumber(int num)
{
    return num % 2 == 0 ? num/2 : 3*num + 1;
}

bool isPrime(int num)
{
    if(num < 2)
        return false;
    
    for(int i=2 ; i < num ; ++i)
        if(num % i == 0)
            return false;
    return true;
}

bool isCoPrime(int n1, int n2)
{
    if(n1 < 0 || n2 < 0)
        return false;
    
    int smallInt = n1 > n2 ? n1 : n2;

    for(int i=2 ; i <= smallInt ; ++i)
        if(n1 % i == 0 && n2 % i == 0)
            return false;
    return true;
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}