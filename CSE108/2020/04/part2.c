#include <stdio.h>

typedef enum{false,true}bool;

void generate_primes(int,int,int*,int*);
bool isPrime(int);
bool isSemiPrime(int);
int getInt(const char*);

int main(void)
{
    int lowerBound = getInt("Lower Bound : ");
    int upperBound = getInt("Upper Bound : ");
    int numP=0,numSemP=0;

    generate_primes(lowerBound,upperBound,&numP,&numSemP);

    printf("Num primes : %d\n",numP);
    printf("Num semi-primes : %d\n",numSemP);

    return 0;
}

void generate_primes(int n1, int n2, int* nump, int* numsemp)
{
    for(int i=n1 ; i <= n2 ; ++i)
    {
        if(isPrime(i))
        {
            printf("%d is prime\n",i);
            ++(*nump);
        }
        else if(isSemiPrime(i))
        {
            printf("%d is semi-prime\n",i);
            ++(*numsemp);
        }
    }
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

bool isSemiPrime(int num)
{
    if(num <= 2)
        return false;

    int totalPrime=0;

    for(int i=2 ; i < num ; ++i)
        if(num % i == 0)
        {
            if(isPrime(i) && totalPrime < 2)
                ++totalPrime;
            else
                return false;
        }

    if(totalPrime == 2)
        return true;
    else
        return false;
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}