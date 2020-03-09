#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu();
int make_a_guess(int,int,int);
void show_scores(int,int);
void lucky_number(int*,int*);			// i created this function to keep menu function clean
void draw_hourglass(int);
void draw_mountain_road(int,int);
int getOddNumber();
int getNumber();
int randomNumberGenerator(int,int);

int main()
{
	srand(time(NULL));
	menu();
	return 0;
}
void menu()
{
	int choice,value1,value2,exit=1,countWin=0,countLose=0;
	while(exit)
	{
		printf("\n**** MENU ****\n");
		printf("1. Play Lucky Number\n");
		printf("2. Draw Hourglass\n");
		printf("3. Draw Mountain Road\n");
		printf("4. Exit\n");
		printf("Choice : ");
		scanf("%d",&choice);
		while(!(choice>0&&choice<=4))
		{
			printf("This is an invalid choice. Try again!\nChoice : ");
			scanf("%d",&choice);
		}
		switch(choice)
		{
			case 1:
				lucky_number(&countWin,&countLose);		// I send adress. Because i keept win and lose while the program is running
				show_scores(countWin,countLose);
				break;
			case 2:
				value1=getOddNumber();
				draw_hourglass(value1);
				break;
			case 3:
				printf("\n-- For Length --\n");
				value1=getNumber();
				printf("\n-- For Maximum Radius --\n");
				value2=getNumber();
				draw_mountain_road(value1,value2);
				break;
			case 4:
				exit=0;
				break;
		}
	}
}
int make_a_guess(int trial,int min,int max)
{
	int guessnum;
	printf("\n(Trial : %d)\nMake a guess between %d and %d : ",trial+1,min,max);
	scanf("%d",&guessnum);
	return guessnum;
}
void show_scores(int score_human,int score_program)
{
	printf("Your score : %d    Program Score : %d\n",score_human,score_program);
}
void lucky_number(int *countWin,int *countLose)
{
	int ln,guess,distance,mini=1,maxi=1024,trial=10,index=0,i=1,k=0,exit=1;
	ln=randomNumberGenerator(mini,maxi);				//	ln=[mini,maxi]
	printf("\n(With having T=10 & LN = %d)\n",ln);
	while(k!=trial&&exit)
	{
		guess=make_a_guess(k,mini,maxi);
		distance=ln-guess;
		if(distance<0)
			distance=-distance;
		while(distance/i!=0)		//	I used the connection between the distance and the forces of 2 to find the distance.
		{							//	The variable i is multiplied by the variable i until the result is 0 at the end of the variable named i.
			i*=2;					//	Increasing one index in each transaction.
			++index;				//	As a result,distance is found.
		}
		printf("Distance : %d\n",index);
		if(guess==ln)
		{
			printf("You Win!\n");
			++*countWin;
			exit=0;
		}
		else  if(k==9)
		{
			printf("You Lose! The program won...\n");
			++*countLose;
			exit=0;
		}
		else if(ln>guess&&mini<guess)
			mini=guess;
		else if(guess>ln&&maxi>guess)
			maxi=guess;
		++k;
		i=1,index=0;
	}
}
int getNumber()
{
	int num;
	printf("Please enter a number : ");
	scanf("%d",&num);
	if(num>=0)
		return num;
	else
		return getNumber();
}
int randomNumberGenerator(int lower_bound,int upper_bound)
{
	int num=rand()%(upper_bound-lower_bound+1)+lower_bound;	//	[lower_bound,upper_bound]
	return num;
}
int getOddNumber()
{
	int num;
	printf("\nPlease enter a odd and positive number for height :");
	scanf("%d",&num);
	if(num%2==0||num<=0)
		return getOddNumber();
	else
		return num;
}
void draw_hourglass(int height)
{
	printf("The Height : %d\n",height);
	for(int i=0;i<height;i++)
	{
		if(i<(height+1)/2)
		{
			for(int j=0;j<i;j++)
				printf(" ");
			for(int j=height;j>2*i;j--)
				printf("*");
		}
		else
		{
			for(int j=height-1;j>i;j--)
				printf(" ");
			for(int j=height-2;j<2*i;j++)
				printf("*");
		}
		printf("\n");
	}
}
void draw_mountain_road(int length,int max_radius)
{
	int i,j,r=1,rtemp,index=max_radius+1;
	while(length!=0)
	{
		rtemp=r;
		r=randomNumberGenerator(0,max_radius);
		if(length%2!=0)
		{
			if(rtemp!=0&&r!=0)
				--index;
			for(i=0;i<r+1;i++)
			{
				for(j=0;j<index-r;j++)
					printf(" ");
				for(j=r;j>i;j--)
					printf(" ");
				if(i==r)
					printf("|");
				else
					printf("/");
				printf("\n");
			}
			for(i=0;i<r;i++)
			{
				for(j=0;j<index-r;j++)
					printf(" ");
				for(j=0;j<=i;j++)
					printf(" ");
				printf("\\");
				printf("\n");
			}
		}
		else
		{
			if(rtemp!=0&&r!=0)
				++index;
			for(i=0;i<r+1;i++)
			{
				for(j=0;j<index;j++)
					printf(" ");
				for(j=0;j<=i;j++)
					if(j==i)
						if(i==r)
							printf("|");
						else
							printf("\\");
					else
						printf(" ");
				printf("\n");
			}
			for(i=0;i<r;i++)
			{
				for(j=0;j<index;j++)
					printf(" ");
				for(j=r;j>i;j--)
					if(j==i+1)
						printf("/");
					else
						printf(" ");
				printf("\n");
			}
		}
		--length;
	}
}