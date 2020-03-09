#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define RED 0
#define YELLOW 1
#define BLUE 2
#define BLACK 3
#define WHITE 4

#define PI 3
#define SQUARE 1
#define RECTENGULAR 2
#define CIRCULAR 3
#define clear() system("clear")

double CreateBody(int);
int SetColor(int);
double LoadMoves(int,double);
int SetAttackPower(int,int);
void ShowPokemon(int,double,int,double,int);
double getDouble();

int main()
{
	int shape,color,attack_power;
	double size_of_body,move_lenght;
	shape=CIRCULAR;
	size_of_body=CreateBody(shape);
	color=168;
	color=SetColor(color);
	move_lenght=LoadMoves(shape,size_of_body);
	attack_power=SetAttackPower(0,150);
	ShowPokemon(shape,size_of_body,color,move_lenght,attack_power);
	return 0;
}
double getDouble()
{
	double value;
	scanf("%lf",&value);
	while(value<=0)
	{
		printf("Please enter greater than 0 :");
		scanf("%lf",&value);
	}
	return value;
}
double CreateBody(int shape)
{
	double value1,value2;
	if(shape==1)
	{
		printf("Square Pokémon is being created...\n");
		printf("Please enter a positive edge : ");
		value1=getDouble();
		return value1*value1;
	}
	else if(shape==2)
	{
		printf("Rectegular Pokémon is being created...\n");
		printf("Please enter a positive edge : ");
		value1=getDouble();
		printf("Please enter a positive edge : ");
		value2=getDouble();
		return value1*value2;
	}
	else
	{
		printf("Circular Pokémon is being created...\n");
		printf("Please enter a positive radius : ");
		value1=getDouble();
		return PI*value1*value1;
	}
}
int SetColor(int color)
{
	if(color>=0&&color<=1000)
		return color%5;		//0-red 1-yellow 2-blue 3-black 4-white
	else
		return 1;
}
double LoadMoves(int shape,double body_size)
{
	double value1,value2;
	if(shape==1)
	{
		value1=sqrt(body_size);
		return 4*value1;
	}
	else if(shape==2)
	{
		value1=5;
		value2=body_size/value1;
		return (value1+value2)*2;
	}
	else
	{
		value1=body_size/PI;
		value1=sqrt(value1);
		return 2*PI*value1;
	}
}
int SetAttackPower(int lower_bound,int upper_bound)
{
	int AP;
	srand(time(NULL));
	AP=rand()%(upper_bound+1);	//	[lower_bound,upper bound]
	return AP;
}
void ShowPokemon(int shape,double body_size,int color,double move_lenght,int attack_power)
{
	char colors[5][10]={{"Red"},{"Yellow"},{"Blue"},{"Black"},{"White"}};
	char shapes[4][15]={{"NULL"},{"Square"},{"Rectengular"},{"Circular"}};
	int value1,value2,i,j;
	clear();
	switch(shape)
	{
		case 1:
			value1=sqrt(body_size);
			for(i=0;i<value1;++i)
			{
				for(j=0;j<value1;++j)
					printf("X");
				printf("\n");
			}
			break;
		case 2:
			value1=5;
			value2=body_size/value1;
			for(i=0;i<value1;++i)
			{
				for(j=0;j<value2;++j)
					printf("X");
				printf("\n");
			}
			break;
		case 3:
			value1=(int)(sqrt(body_size/PI)+0.5);		// i add 0.5 because i get more accurate result while type casting do
			if(value1%2==1)
			{
				for(i=0;i<(value1+1)/2;i++)
				{
					for(j=(value1-1)/2;j>i;j--)
						printf("\t");
					for(j=0;j<(2*i)+2;j++)
					{
						if(j==0||j==(2*i)+1&&j!=1)
							printf("X");
						else
							printf("\t");
					}
					printf("\n");
				}
				for(i=0;i<(value1-1)/2;i++)
				{
					for(j=0;j<i+1;j++)
						printf("\t");
					for(j=value1-1;j>2*i;j--)
					{
						if(j==value1-1||j==(2*i)+1&&j!=value1-2)
							printf("X");
						else
							printf("\t");
					}
					printf("\n");
				}
			}
			else
			{
				for(i=0;i<(value1/2)+1;i++)
				{
					for(j=i;j<value1/2;j++)
					{
						if(i==0&&j==(value1/2)-1)
							printf("    ");
						else
							printf("\t");
					}
					for(j=0;j<(2*i)+1;j++)
					{
						if(j==0||j==2*i)
							printf("X");
						else
							printf("\t");	
					}
					printf("\n");
				}
				for(i=0;i<value1/2;i++)
				{
					for(j=0;j<i+1;j++)
					{
						if(i==(value1/2)-1&&j==i)
							printf("    ");
						else
							printf("\t");
					}
					for(j=value1-1;j>2*i;j--)
					{
						if(j==value1-1||j==(2*i)+1)
							printf("X");
						else
							printf("\t");
					}
					printf("\n");
				}
			}
			break;
		default:
			printf("Wrong shape...\nTry again...\n");
			break;
	}
	printf("Name : %s Pokémon\n",shapes[shape]);
	printf("Size : %.2lf\n",body_size);
	printf("Color : %s\n",colors[color]);
	printf("Move : %.2lf\n",move_lenght);
	printf("Attack Power : %d\n",attack_power);
}