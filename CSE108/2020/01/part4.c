#include <stdio.h>

#define DAY 21
#define MONTH 2
#define YEAR 2020

double calculateDifference(int,int,int);

int main(void)
{
    int day=0,month=0,year=0;

    printf("Please enter a date in format dd/mm/yy : ");
    scanf("%d%d%d",&day,&month,&year);

    printf("Entered date is %.2lf seconds far away from now.\n",calculateDifference(day,month,year));

    return 0;
}

double calculateDifference(int d, int m, int y)
{
    return 24*60*60*(double)(d-DAY + (m-MONTH)*30 + (y-YEAR)*12*30);
}