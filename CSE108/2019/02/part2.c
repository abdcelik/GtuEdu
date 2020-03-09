#include <stdio.h>
#include <math.h>

double calc_quadratic_eq_roots(int,int,int,int);
int getInt(const char*);

int main(void)
{
    int a = getInt("a : ") , b = getInt("b : ") , c = getInt("c : ");

    printf("x : %.2lf\n",calc_quadratic_eq_roots(a,b,c,getInt("choice : ")));
    return 0;
}

double calc_quadratic_eq_roots(int a, int b, int c, int choice)
{
    double delta = sqrt(b*b - 4*a*c);

    if(choice == 1)
        delta *= -1;

    return (-b + delta) / (2*a);
}

int getInt(const char* str)
{
    int var=0;

    printf("%s",str);
    scanf("%d",&var);

    return var;
}