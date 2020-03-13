#include <stdio.h>

#define FILENAME "integers.txt"
#define MAXROW 10
#define MAXCOLUMN 20

typedef enum{false,true}bool;

bool readFromFileAndCalculate(const char*);
int getInt(const char*);

int main(void)
{
    if(!readFromFileAndCalculate(FILENAME))
        printf("Error! File could not be read or inputs are invalid!\n");
    return 0;
}

bool readFromFileAndCalculate(const char* fileName)
{
    FILE *fp = fopen(fileName,"r+");

    if(!fp)
        return false;

    int row = getInt("Row : ");
    int column = getInt("Column : ");
    int val=0,sum=0;

    if(row < 0 || row > MAXROW || column < 0 || column > MAXCOLUMN)
    {
        fclose(fp);
        return false;
    }

    for(int i=0 ; i < row ; ++i)
    {
        for(int j=0 ; j < column ; ++j)
        {
            fscanf(fp,"%d",&val);
            sum += val;
        }

        for(char chr=0 ; chr != '\n' ; fscanf(fp,"%c",&chr));
    }

    printf("Average : %.2lf\n",(double)sum / (row*column));

    fclose(fp);
    return true;
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}