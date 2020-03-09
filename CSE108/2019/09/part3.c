#include <stdio.h>

struct Time
{
    int second;
    int minute;
    int hour;
};

void difference_time(struct Time,struct Time,struct Time*);
void printTime(struct Time*);
struct Time getTime(const char*);

int main(void)
{
    struct Time start = getTime("Start time (h,m,s) : ");
    struct Time end = getTime("Stop time (h,m,s) : ");
    struct Time difference;

    difference_time(start,end,&difference);

    printf("Time elapsed : ");printTime(&start);
    printf(" - ");printTime(&end);
    printf(" = ");printTime(&difference);printf("\n");

    return 0;
}

void difference_time(struct Time start, struct Time stop, struct Time* diff)
{
    diff->second = start.second - stop.second;
    diff->minute = start.minute - stop.minute;
    diff->hour = start.hour - stop.hour;

    if(diff->second < 0)
        diff->second += 60 , --diff->minute;

    if(diff->minute < 0)
        diff->minute += 60 , --diff->hour;
}

void printTime(struct Time* time)
{
    printf("%d:%d:%d",time->hour,time->minute,time->second);
}

struct Time getTime(const char* text)
{
    struct Time var;

    printf("%s",text);
    scanf("%d%d%d",&var.hour,&var.minute,&var.second);

    return var;
}