#include <stdio.h>

typedef enum{false,true}bool;

bool makeup_exam(int,int,int);
int getInt(const char*);

int main(void)
{
    int midterm=0,final=0,absenteeism=0;

    midterm = getInt("Midterm : ");
    final = getInt("Final : ");
    absenteeism = getInt("Absenteeism : ");

    if(makeup_exam(midterm,final,absenteeism) == true)
        printf("Allowed!\n");
    else
        printf("Not Allowed!\n");
    
    return 0;
}

bool makeup_exam(int midterm, int final, int absenteeism)
{
    return !(midterm*0.4 + final*0.6 > 59.5 || absenteeism > 80);
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}