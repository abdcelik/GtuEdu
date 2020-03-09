#include <stdio.h>
#include <math.h>

void calc_roots(int,int,int,double*,double*);
int getInt(const char*);

int main(void)
{
    int a = getInt("a : ") , b = getInt("b : ") , c = getInt("c : ");
    double root1=0,root2=0;

    calc_roots(a,b,c,&root1,&root2);
    printf("root 1 : %.2lf\troot 2 : %.2lf\n",root1,root2);

    return 0;
}

void calc_roots(int a, int b, int c, double* root1, double* root2)
{
    double delta = sqrt(b*b - 4*a*c);

    *root1 = (-b + delta) / (2*a);
    *root2 = (-b - delta) / (2*a);
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}