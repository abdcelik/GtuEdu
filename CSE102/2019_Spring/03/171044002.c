#include <stdio.h>

#define HWNUM 10
#define LABNUM 10
#define EXAMNUM 2

void menu();
void calculator();
int add(int,int);
int sub(int,int);
int multiplication(int,int);
int divison(int,int);
int power(int,int);
int modulo(int,int);
int doit(int(),int,int);
void weightedCalculate();
int take_grades(int[]);
int take_exam_grades(int[]);
double calculate_homework(int[]);
double calculate_lab(int[]);
double calculate_all(int,int[],int);
void draw_diamond();
int my_stringcmp(char*,char*);

int main()
{
	menu();
	return 0;
}
void menu()
{
	int choice,exit=1;
	while(exit)
	{
		printf("\n**** MENU ****\n");
		printf("(1) - Calculator\n");
		printf("(2) - Weighted Average\n");
		printf("(3) - Draw Diamond\n");
		printf("(4) - Exit\n");
		printf("Choice : ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				calculator();
				break;
			case 2:
				weightedCalculate();
				break;
			case 3:
				draw_diamond();
				break;
			case 4:
				exit=0;
				break;
			default:
				printf("Invalid choice...\n");
				break;
		}
	}
}
void calculator()
{
	char str[255],operation[2];
	int num1,num2,index,i,r,result=0,exit=1;
	char op[6][3]={{"+"},{"-"},{"*"},{"/"},{"**"},{"%"}};

	printf("\n**** CALCULATOR ****\n");
	printf("Rules (1) You put a space each expression\n");
	printf("Rules (2) If you want to exit the calculator, enter '.'\n");
	printf("(+) Addition\n");
	printf("(-) Substraction\n");
	printf("(*) Multiplication\n");
	printf("(/) Divison\n");
	printf("(**) Power\n");
	printf("(%%) Modulo\n\n");
	while(exit)
	{
		scanf(" %[^\n]s",str);		// This expression takes up to the enter character.
		r=sscanf(str,"%s %d %d",operation,&num1,&num2);
		
		if(my_stringcmp(operation,".")==0)
			exit=0;

		for(i=0;i<6;i++)			// The for loop is determined by which operation.
			if(my_stringcmp(operation,op[i])==0)
				index=i;

		switch(index)
		{
			case 0:
				if(r==2)
					result=doit(add,result,num1);
				else
					result=doit(add,num1,num2);
				break;
			case 1:
				if(r==2)
					result=doit(sub,result,num1);
				else
					result=doit(sub,num1,num2);
				break;
			case 2:
				if(r==2)
					result=doit(multiplication,num1,result);
				else
					result=doit(multiplication,num1,num2);
				break;
			case 3:
				if(r==2)
					result=doit(divison,result,num1);
				else
					result=doit(divison,num1,num2);
				break;
			case 4:
				if(r==2)
					result=doit(power,result,num1);
				else
					result=doit(power,num1,num2);
				break;
			case 5:
				if(r==2)
					result=doit(modulo,result,num1);
				else
					result=doit(modulo,num1,num2);
				break;
			default:
				printf("Invalid operation...\n");
				break;
		}
		if(result!='.')			// Except for special cases
			printf("%d\n",result);
		else					// If there are special cases, the previous result reset.
			result=0;
	}
}
int add(int number1,int number2)
{
	return number1+number2;
}
int sub(int number1,int number2)
{
	return number1-number2;
}
int multiplication(int number1,int number2)
{
	return number1*number2;
}
int divison(int number1,int number2)
{
	if(number2!=0)
		return number1/number2;
	else
	{
		printf("Division by zero is undefined\n");
		return '.';
	}
}
int power(int number1,int number2)
{
	int i,p=1;
	if(number2<0)
		return 0;
	else if(number2!=0)
	{
		for(i=0;i<number2;i++)
			p*=number1;
		return p;
	}
	else if(number1==0&&number2==0)
	{
		printf("0 force of 0 is undefined\n");
		return '.';
	}
	else
		return 1;
}
int modulo(int number1,int number2)
{
	if(number2==0)
	{
		printf("Malformed expression...\n");
		return '.';
	}
	else
		return number1%number2;
}
int doit(int foo(),int first_number,int second_number)
{
	int res;
	res=foo(first_number,second_number);
	return res;
}
void weightedCalculate()
{
	int homeworkGrades[HWNUM];
	int labGrades[LABNUM];
	int examGrades[EXAMNUM];
	double aveHW,aveLAB,aveALL;
	printf("*** HOMEWORK GRADES ***\n");
	take_grades(homeworkGrades);
	printf("*** LAB GRADES ***\n");
	take_grades(labGrades);
	printf("*** MIDTERM AND FINAL ***\n");
	take_exam_grades(examGrades);
	aveHW=calculate_homework(homeworkGrades);
	aveLAB=calculate_lab(labGrades);
	aveALL=calculate_all(aveHW,examGrades,aveLAB);
	printf("\nWeighted Average : %.3lf\n",aveALL);
}
int take_grades(int arr[])
{
	int i;
	for(i=0;i<HWNUM;i++)
	{
		printf("  %d. Grade : ",i+1);
		scanf("%d",&arr[i]);
	}
}
int take_exam_grades(int arr[])
{
	printf("  Midterm : ");
	scanf("%d",&arr[0]);
	printf("  Fİnal : ");
	scanf("%d",&arr[1]);
}
double calculate_homework(int arr[])
{
	double average=0;
	int i;
	for(i=0;i<10;i++)
		average+=arr[i];
	return average/10;
}
double calculate_lab(int arr[])
{
	double average=0;
	int i;
	for(i=0;i<10;i++)
		average+=arr[i];
	return average/10;
}
double calculate_all(int ave_hw,int grades[],int ave_lab)
{
	printf("Ave hw : %d\n",ave_hw);
	printf("Ave lab : %d\n",ave_lab);
	double average;
	average=(ave_hw*0.1)+(ave_lab*0.2)+(grades[0]*0.3)+(grades[1]*0.4);
	return average;
}
void draw_diamond()
{
	int height,i,j;
	printf("Height : ");
	scanf("%d",&height);
	for(i=0;i<height;i++)
	{
		for(j=height-1;j>i;j--)
			printf(" ");
		for(j=0;j<2*(i+1);j++)
			if(j==0)
				printf("/");
			else if(j==2*i+1)
				printf("\\");
			else
				printf("*");
		printf("\n");
	}
	for(i=0;i<height;i++)
	{
		for(j=0;j<i;j++)
			printf(" ");
		for(j=2*height;j>2*i;j--)
			if(j==2*height)
				printf("\\");
			else if(j==2*i+1)
				printf("/");
			else
				printf("*");
		printf("\n");
	}
}
int my_stringcmp(char *str1,char *str2)
{
	while(*str1&&*str2&&*str1==*str2)
		++str1,++str2;
	return *str1-*str2;
}