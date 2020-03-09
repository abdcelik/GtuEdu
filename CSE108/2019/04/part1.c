#include <stdio.h>

typedef enum{false,true}bool;

void find_prime_numbers(int);
bool isPrime(int);
int getInt(const char*);

int main(void)
{
	find_prime_numbers(getInt("Please enter a number to find prime numbers that are smaller than the number : "));
	return 0;
}

void find_prime_numbers(int number)
{
	int count=0;

	for(int i=2 ; i < number ; ++i)
		if(isPrime(i) == true)
		{
			printf("%d ",i);
			++count;
		}

	printf("\nThere are %d prime numbers which are smaller than %d\n",count,number);
}

bool isPrime(int number)
{
	bool flag = true;

	for(int i=2 ; i < number && flag ; ++i)
		if(number % i == 0)
			flag = false;

	return flag;
}

int getInt(const char* text)
{
	int var=0;

	printf("%s",text);
	scanf("%d",&var);

	return var;
}