#include <stdio.h>

int main(void)
{
    int var1=0,var2=0;

    printf("Please enter two integer numbers : ");
    scanf("%d%d",&var1,&var2);

    printf("%d + %d = %d\n",var1,var2,var1 + var2);
    printf("%d - %d = %d\n",var1,var2,var1 - var2);
    printf("%d * %d = %d\n",var1,var2,var1 * var2);
    printf("%d / %d = %d\n",var1,var2,var1 / var2);
    printf("%d %% %d = %d\n",var1,var2,var1 % var2);

    return 0;
}