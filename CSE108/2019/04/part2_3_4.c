#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum{false,true}bool;
typedef enum{NOONE=0,LEFTBOTTOM=1,BOTTOM=2,RIGHTBOTTOM=3,LEFT=4,RIGHT=6,LEFTTOP=7,UP=8,RIGHTTOP=9}Move;

#define SIZE 10

#define HORIZONTALDISTANCE 3
#define VERTICALDISTANCE 4
#define DIAGONALDISTANCE 5

void print_the_grid(int,int,int,int);
int find_min_path(int,int,int,int);
int checkMove(int,int,Move);
bool checkGame(int,int,int,int);
void updateAnt(int*,int*,Move,int*);
int getRandom(int,int);
int getInt(const char*);

int main(void)
{
	int nestX=0,nestY=0,antX=0,antY=0,distance=0;
	bool exit = false;
	Move move = NOONE;

	srand(time(NULL));

	nestX = getRandom(0,9);
	nestY = getRandom(0,9);
	
	printf("Minimum distance : %d\n",find_min_path(antX,antY,nestX,nestY));
	
	while(!exit)
	{
		print_the_grid(antX,antY,nestX,nestY);
		move = getInt("Choice : ");

		if(checkMove(antX,antY,move) == true)
			updateAnt(&antX,&antY,move,&distance);
		else
			printf("Invalid movement!\n");

		if(checkGame(antX,antY,nestX,nestY) == true)
		{
			printf("The ant arrived ant nest!\n");
			printf("The distance : %d\n",distance);
			exit = true;
		}
	}

	return 0;
}

void print_the_grid(int x_pos_ant, int y_pos_ant ,int x_pos_nest, int y_pos_nest)
{
	for(int i=0 ; i < SIZE ; ++i)
	{
		for(int j=0 ; j < SIZE ; ++j)
		{
			if(j == x_pos_ant && i == y_pos_ant)
				printf("X");
			else if(j == x_pos_nest && i == y_pos_nest)
				printf("0");
			else
				printf(".");
		}
		printf("\n");
	}
}

int find_min_path(int x_pos_ant, int y_pos_ant, int x_pos_nest, int y_pos_nest)
{
	bool exit = false;
	int minDistance = 0;

	while(!exit)
	{
		if(x_pos_ant != x_pos_nest && y_pos_ant != y_pos_nest)
			++x_pos_ant , ++y_pos_ant , minDistance += DIAGONALDISTANCE;
		else if(x_pos_ant != x_pos_nest)
			++x_pos_ant , minDistance += HORIZONTALDISTANCE;
		else
			++y_pos_ant , minDistance += VERTICALDISTANCE;

		if(x_pos_ant == x_pos_nest && y_pos_ant == y_pos_nest)
			exit = true;
	}

	return minDistance;
}

int checkMove(int x_pos_ant, int y_pos_ant, Move move)
{
	bool movement = true;

	if	(move == LEFT		&& --x_pos_ant >= 0);
	else if	(move == RIGHT		&& ++x_pos_ant < SIZE);
	else if	(move == UP		&& --y_pos_ant >= 0);
	else if	(move == BOTTOM		&& ++y_pos_ant < SIZE);
	else if	(move == LEFTBOTTOM 	&& --x_pos_ant >=0 	&& ++y_pos_ant < SIZE);
	else if	(move == RIGHTBOTTOM	&& ++x_pos_ant <SIZE 	&& ++y_pos_ant < SIZE);
	else if	(move == LEFTTOP	&& --x_pos_ant >=0 	&& --y_pos_ant >= 0);
	else if	(move == RIGHTTOP	&& ++x_pos_ant <SIZE 	&& --y_pos_ant >= 0);
	else
		movement=false;;

	return movement;
}

void updateAnt(int* antX, int* antY, Move move, int* distance)
{
	switch(move)
	{
		case LEFT:
			--(*antX);
			*distance += HORIZONTALDISTANCE;
			break;
		case RIGHT:
			++(*antX);
			*distance += HORIZONTALDISTANCE;
			break;
		case UP:
			--(*antY);
			*distance += VERTICALDISTANCE;
			break;
		case BOTTOM:
			++(*antY);
			*distance += VERTICALDISTANCE;
			break;
		case LEFTTOP:
			--(*antX);
			--(*antY);
			*distance += DIAGONALDISTANCE;
			break;
		case RIGHTBOTTOM:
			++(*antX);
			++(*antY);
			*distance += DIAGONALDISTANCE;
			break;
		case LEFTBOTTOM:
			--(*antX);
			++(*antY);
			*distance += DIAGONALDISTANCE;
			break;
		case RIGHTTOP:
			++(*antX);
			--(*antY);
			*distance += DIAGONALDISTANCE;
			break;
	}
}

bool checkGame(int antX, int antY, int nestX, int nestY)
{
	return antX == nestX && antY == nestY;
}

int getRandom(int lowerBound, int upperBound)
{
	return rand() % (upperBound-lowerBound+1) + lowerBound;
}

int getInt(const char* text)
{
	int var=0;
	
	printf("%s",text);
	scanf("%d",&var);

	return var;
}
