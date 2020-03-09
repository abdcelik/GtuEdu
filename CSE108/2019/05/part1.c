#include <stdio.h>

void get_min_max(int*,int*);
int getInt(const char*);

int main(void)
{
	int min=0,max=0;

	get_min_max(&min,&max);
	printf("Min : %d, Max : %d, Average : %d\n",min,max,(min+max)/2);

	return 0;
}

void get_min_max(int* min, int* max)
{
    int size = 3;
    int arr[size];

    for(int i=0 ; i < size ; ++i)
        arr[i] = getInt("Number : ");

	*min = *max = arr[0];
	
    for(int i = 1 ; i < size ; ++i)
    {
        if(arr[i] > *max)
            *max = arr[i];
        if(arr[i] < *min)
            *min = arr[i];
    }
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}