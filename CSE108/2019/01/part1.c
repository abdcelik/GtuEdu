#include <stdio.h>

int getInt(const char*);
int add(int,int);

int main(void)
{
	printf("Sum : %d\n",add(getInt("Second number : "),getInt("First number : ")));
	return 0;
}

int getInt(const char* text)
{
	int var=0;

	printf("%s",text);
	scanf("%d",&var);

	return var;
}

int add(int num1, int num2)
{
	return num1+num2;
}