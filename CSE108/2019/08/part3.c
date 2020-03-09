#include <stdio.h>
#include <math.h>

int arithmeticSequence(int);
int getInt(const char*);

int main(void)
{
    printf("Result : %d\n",arithmeticSequence(getInt("n : ")));
    return 0;
}

int arithmeticSequence(int n)
{
    if(n == 1)
        return 1;
    return 2 * arithmeticSequence(ceil(n/2)) + 1;
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}