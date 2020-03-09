#include <stdio.h>

#define PI 3.14

double mySine(double);
double convertToRadian(double);
double power(double,int);
int factorial(int);
double getDouble(const char*);

int main(void)
{
    double angle=0;

    angle = getDouble("Enter angle in degrees : ");
    printf("Sine of %.3lf degrees : %.3lf\n",angle,mySine(convertToRadian(angle)));
    
    return 0;
}

double mySine(double x)
{
    double res = 0.0;

    for(int i=0 ; i < 4 ; ++i)
        res += power(-1,i) * power(x,2*i+1) / factorial(2*i+1);

    return res;
}

double convertToRadian(double angle)
{
    return angle * PI / 180;
}

double power(double base, int exponent)
{
    double res = 1;

    for(int i=0 ; i < exponent ; ++i , res *= base);

    return res;
}

int factorial(int num)
{
    if(num != 0)
        return num * factorial(num-1);
    return 1;
}

double getDouble(const char* text)
{
    double var=0;

    printf("%s",text);
    scanf("%lf",&var);

    return var;
}