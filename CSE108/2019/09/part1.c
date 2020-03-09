#include <stdio.h>

typedef struct
{
    int rent;
    int bill;
    int foods;
}Cost;

int getCostTotal(Cost*);

int main(void)
{
    Cost cost;
    int rent=0,bill=0,foods=0,people=0;

    printf("Enter the cost of rent, bill and foods : ");
    scanf("%d%d%d",&cost.rent,&cost.bill,&cost.foods);

    printf("Enter the number of people : ");
    scanf("%d",&people);

    printf("Total cost : %d\n",getCostTotal(&cost));
    printf("Cost per student : %.1lf\n",getCostTotal(&cost) / (double)people);

    return 0;
}

int getCostTotal(Cost* cost)
{
    return cost->rent + cost->bill + cost->foods;
}