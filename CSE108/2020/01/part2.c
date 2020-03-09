#include <stdio.h>

int main(void)
{
    int real_1=0,imag_1=0;
    int real_2=0,imag_2=0;

    printf("Please enter the first complex number (real part first) : ");
    scanf("%d%d",&real_1,&imag_1);

    printf("Please enter the second complex number (real part first) : ");
    scanf("%d%d",&real_2,&imag_2);

    printf("Sum of the numbers : %d%+di\n",real_1 + real_2 , imag_1 + imag_2);
    printf("Multiplicantion of the numbres : %d%+di\n",real_1 * real_2 - imag_1 * imag_2 , real_1 * imag_2 + real_2 * imag_1);

    return 0;
}