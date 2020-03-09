#include <stdio.h>

#define PI 3.14

double areaOfSphere(int);
int getInt(const char*);

int main(void)
{
    printf("Area : %.2lf\n",areaOfSphere(getInt("r : ")));
    return 0;
}

double areaOfSphere(int r)
{
    if(r <= 0)
        return 0;
    return 4*PI*r*r;
}

int getInt(const char* str)
{
    int var=0;

    printf("%s",str);
    scanf("%d",&var);

    return var;
}