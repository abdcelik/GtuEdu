#include <stdio.h>

void letter_grade(int,int);
int getInt(const char*);

int main(void)
{
    int midterm = getInt("Midterm : ") , final = getInt("Final : ");

    letter_grade(midterm,final);
    return 0;
}

void letter_grade(int midterm, int final)
{
    double average = midterm*0.4 + final*0.6;

    if(average < 60)        printf("Letter Grade : F\n");
    else if(average < 70)   printf("Letter Grade : D\n");
    else if(average < 80)   printf("Letter Grade : C\n");
    else if(average < 90)   printf("Letter Grade : B\n");
    else                    printf("Letter Grade : A\n");
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}