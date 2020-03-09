#include <stdio.h>

#define PI 3.14

double area(int);
double perimeter(int);
int getInt(const char*);

int main(void)
{
    int radius = getInt("Please enter the radius of the circle : ");

    printf("The area of the circle : %.2lf\n",area(radius));
    printf("The perimeter of the circle : %.2lf\n",perimeter(radius));

    return 0;
}

double area(int r)
{
    return PI*r*r;
}

double perimeter(int r)
{
    return 2*PI*r;
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}