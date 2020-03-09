#include <stdio.h>

#define clear() printf("\033[H\033[J")	// clear the screen

void menu();
int greatest_common_divisor(int,int,int);
int isPrime(int);
void piecewise_linear_function(int);
int equal_or_not_equal(int,int);
char find_first_capital_letter(char*);
void mergeSort(int[],int[],int);
void m_sort(int[],int[],int,int);
void merge(int[],int[],int,int,int);

int main()
{
	menu();
	return 0;
}
void menu()
{
	int choice,exit=1;
	int num1,num2,res,digit=0,i;
	int arr[64],temparr[64],size;
	char str[64],chr;
	clear();
	while(exit)
	{
		printf("1 - Greatest Common Divisor\n");
		printf("2 - Merge Sort\n");
		printf("3 - Piecewise Linear Function\n");
		printf("4 - Does it fit the formula ?\n");
		printf("5 - Find First Capital\n");
		printf("0 - Exit\n");
		printf("Choice : ");
		scanf(" %d",&choice);
		clear();
		switch(choice)
		{
			case 1:
				printf("1. Number : ");
				scanf("%d",&num1);
				printf("2. Number : ");
				scanf("%d",&num2);
				res=greatest_common_divisor(num1,num2,2);
				printf("** GCD(%d,%d) = %d **",num1,num2,res);
				break;
			case 2:
				printf("Enter the length of the list : ");
				scanf("%d",&size);
				printf("Enter the elements of the list : \n");
				for(i=0;i<size;i++)
				{
					printf("%d. elements : ",i+1);
					scanf("%d",&arr[i]);
				}
				mergeSort(arr,temparr,size);
				printf("Sorted array is : \n");
				for(i=0;i<size;i++)
					printf("%d  ",arr[i]);
				break;
			case 3:
				printf("Number : ");
				scanf("%d",&num1);
				piecewise_linear_function(num1);
				break;
			case 4:
				printf("Number : ");
				scanf("%d",&num1);
				num2=num1;
				while(num2>0)
					num2/=10,digit++;
				res=equal_or_not_equal(num1,digit); // The function returns the formula's result.
				if(res==num1)						// If the result fits number, print "Equal".
					printf("Equal");
				else
					printf("Not equal");
				digit=0;
				break;
			case 5:
				printf("String (without space): ");
				scanf(" %[^\n]s",str);
				chr=find_first_capital_letter(str);
				printf("** The first capital is %c **",chr);
				break;
			case 0:
				exit=0;
				break;
		}
		printf("\n\n");
	}
}
int greatest_common_divisor(int num1,int num2,int primeFactor)
{
	if(primeFactor<=num1)
		if(isPrime(primeFactor)&&num1%primeFactor==0&&num2%primeFactor==0)
			return primeFactor*greatest_common_divisor(num1/primeFactor,num2/primeFactor,primeFactor);
		else
			return greatest_common_divisor(num1,num2,primeFactor+1);
	else
		return 1;
}
int isPrime(int num)
{
	int i,flag=1;
	for(i=2;i<num&&flag;i++)
		if(num%i==0)
			flag=0;
	return flag;
}
void mergeSort(int numbers[],int temp[],int array_size)
{
	m_sort(numbers,temp,0,array_size-1);
}
void m_sort(int numbers[],int temp[],int left,int right)
{
	int mid;
	if(right>left)		// divide
	{
		mid=(right+left)/2;
		m_sort(numbers,temp,left,mid);
		m_sort(numbers,temp,mid+1,right);
		merge(numbers,temp,left,mid+1,right);
	}
}
void merge(int numbers[],int temp[],int left,int mid,int right)
{
	int i,left_end,num_elements,tmp_pos;
	left_end=mid-1;
	tmp_pos=left;
	num_elements=right-left+1;

	while((left<=left_end)&&(mid<=right))	//conquer
	{
		if(numbers[left]<=numbers[mid])
		{
			temp[tmp_pos]=numbers[left];
			tmp_pos=tmp_pos+1;
			left=left+1;
		}
		else
		{
			temp[tmp_pos]=numbers[mid];
			tmp_pos=tmp_pos+1;
			mid=mid+1;
		}
	}

	while(left<=left_end)				//conquer
	{
		temp[tmp_pos]=numbers[left];
		left=left+1;
		tmp_pos=tmp_pos+1;
	}

	while(mid<=right)					//conquer
	{
		temp[tmp_pos]=numbers[mid];
		mid=mid+1;
		tmp_pos=tmp_pos+1;
	}

	for(i=0;i<=num_elements;i++)
	{
		numbers[right]=temp[right];
		right=right-1;
	}
}
void piecewise_linear_function(int num)
{
	printf("%d  ",num);
	if(num>1)
		if(num%2==0)
			return piecewise_linear_function(num/2);
		else
			return piecewise_linear_function(3*num+1);
}
int equal_or_not_equal(int num,int digit)
{
	int i,j=1;
	if(num>0)
	{
		for(i=0;i<digit;i++)
			j*=(num%10);
		return j+equal_or_not_equal(num/10,digit);
	}
	else
		return 0;
}
char find_first_capital_letter(char *str)
{
	if(*str&&*str>='a'&&*str<='z')
		return find_first_capital_letter(str+1);
	else
		return *str;
}