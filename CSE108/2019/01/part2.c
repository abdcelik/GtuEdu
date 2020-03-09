#include <stdio.h>

int find_max_of_five(int,int,int,int,int);

int main(void)
{
	printf("Max num : %d\n",find_max_of_five(8,-5,0,3,9,-1));
	return 0;
}

int find_max_of_five(int a1, int a2, int a3, int a4, int a5)
{
	int arr[] = {a2,a3,a4,a5};
	int max = a1;

	for(int i=0 ; i < 4 ; ++i)
		if(arr[i] > max)
			max = arr[i];

	return max;
}