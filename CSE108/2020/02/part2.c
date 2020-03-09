#include <stdio.h>

int area(int,int);
int perimeter(int,int);
int getInt(const char*);

int main(void)
{
    int len = getInt("Please enter the length of the rectangle : ");
    int width = getInt("Please enter the width of the rectangle : ");

    printf("Area of the rectangle : %d\n",area(len,width));
    printf("Perimeter of the rectangle : %d\n",perimeter(len,width));

    return 0;
}

int area(int l, int w)
{
    return l*w;
}

int perimeter(int l, int w)
{
    return 2*(l+w);
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}