#include <stdio.h>

typedef enum{MON,TUE,WED,THU,FRI,SAT,SUN}Day;
typedef enum{JAN,FEB,MAR,APR,MAY,JUNE,JULY,AUG,SEPT,OCT,NOV,DEC}Month;
typedef enum{Y2019,Y2020,Y2021}Year;

int calc_date(int,int*,Day*,Month*,Year*);
void print_date(int,Day,Month,Year);

int main(void)
{
    Day day = TUE;
    Month month = JAN;
    Year year = Y2019;
    int dm=1;
    
    calc_date(0,&dm,&day,&month,&year);
    print_date(dm,day,month,year);

    calc_date(360,&dm,&day,&month,&year);
    print_date(dm,day,month,year);

    return 0;
}

int calc_date(int n, int* dm, Day* d, Month *m, Year *y)
{
    *d += n % 7;

    for(*dm += n ; *dm > 30 ; *dm -= 30)
        if(++(*m) > DEC)
        {
            ++(*y);
            *m = 0;
        }
}

void print_date(int dm, Day day, Month month, Year year)
{
    printf("dm : %d, ",dm);

    switch(month)
    {
        case JAN:   printf("m : January, ");    break;
        case FEB:   printf("m : Febuary, ");    break;
        case MAR:   printf("m : March, ");      break;
        case APR:   printf("m : April, ");      break;
        case MAY:   printf("m : May, ");        break;
        case JUNE:  printf("m : June, ");       break;
        case JULY:  printf("m : July, ");       break;
        case AUG:   printf("m : August, ");     break;
        case SEPT:  printf("m : September, ");  break;
        case OCT:   printf("m : October, ");    break;
        case NOV:   printf("m : November, ");   break;
        case DEC:   printf("m : December, ");   break;
    }

    switch(year)
    {
        case Y2019:  printf("y : 2019, ");   break;
        case Y2020:  printf("y : 2020, ");   break;
        case Y2021:  printf("y : 2021, ");   break;
    }
    
    switch(day)
    {
        case MON:   printf("d : Monday\n");     break;
        case TUE:   printf("d : Tuesday\n");    break;
        case WED:   printf("d : Wednesday\n");  break;
        case THU:   printf("d : Thursday\n");   break;
        case FRI:   printf("d : Friday\n");     break;
        case SAT:   printf("d : Saturday\n");   break;
        case SUN:   printf("d : Sunday\n");     break;
    }
}