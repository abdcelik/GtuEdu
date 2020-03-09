#include <stdio.h>

#define CITYNUM 4

void read_forecast(float[][7]);
void city_avr(float[][7],float[][3]);
void calc_ave(float[][7],float[][3],int,int);
void select_city_and_day(float[][3]);
float getFloat(const char*);

int main(void)
{
    float wf[CITYNUM][7];
    float ave[CITYNUM][3];

    read_forecast(wf);
    city_avr(wf,ave);
    select_city_and_day(ave);

    return 0;
}

void read_forecast(float wf[][7])
{
    for(int i=0 ; i < CITYNUM ; ++i)
    {
        printf("%d.city\n",i+1);

        for(int j=0 ; j < 7 ; ++j)
            wf[i][j] = getFloat("Degree : ");
    }
}

void city_avr(float wf[][7], float ave[][3])
{
    for(int i=0 ; i < CITYNUM ; ++i)
        for(int j=0 ; j < 3 ; ++j)
            calc_ave(wf,ave,i,j);
}

void calc_ave(float wf[][7], float ave[][3], int city, int fivefold)
{
    for(int i=0 ; i < 5 ; ++i)
        ave[city][fivefold] += wf[city][fivefold+i];
    ave[city][fivefold] /= 5;
}

void select_city_and_day(float ave[][3])
{
    for(int i=0 ; i < CITYNUM ; ++i)
        for(int j=0 ; j < 3 ; ++j)
            if(ave[i][j] >= 20.)
                printf("City %d, Days %d\n",i+1,j+1);
}

float getFloat(const char* text)
{
    float var=0.;

    printf("%s",text);
    scanf("%f",&var);

    return var;
}