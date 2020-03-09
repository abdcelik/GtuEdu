#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define clear() printf("\033[H\033[J")

typedef enum{empty,Charmander,Pikachu,Squirtle,Bulbasaur,Pidgeotto,Ratata,Mug,Caterpie,Zubat,Krabby}pokemon;
typedef enum{emptyy,linear,quadratic}attack_type;

void menu();
void pokedex(char Pokemon_name[][11],int range[],attack_type type[],int attack_power[],int stamina[]);
void oaks_laboratory(char Pokemon_name[][11],pokemon Pokemons[],pokemon *myPokemons);
void show_Pokemons(char Pokemon_name[][11],pokemon Pokemons[],int pokemon_count);
void catch_a_pokemon(char Pokemon_name[][11],pokemon Pokemons[],pokemon *my_pocket);
void release_a_pokemon(char Pokemon_name[][11],pokemon Pokemons[],pokemon *my_pocket);
void battle(char Pokemon_name[][11],int range[],attack_type type[],int attack_power[],int stamina[],pokemon user_Pokemons[]);
void show_area(char Pokemon_name[][11],int area[][8],int pokemon_staminas_view[][8]);
int checkMoveAndGo(char Pokemon_name[][11],int area[][8],int pokemon_staminas_view[][8],int selectedPokemon,int selectedMovement,int selectedWay,int *turn);
void attack_in_range(int area[][8],int pokemon_staminas_view[][8],int range[],attack_type type[],int attack_power[],int selectedPokemon);
int checkTournament(int area[][8],int pokemon_staminas_view[][8],pokemon user_Pokemons[],int ai_Pokemons[]);
int getInput(char[],char[],int,int);
int myStringCmp(char*,char*);

int main()
{
	srand(time(NULL));
	menu();
	return 0;
}
void menu()
{
	int choice,exit=1;
	char Pokemon_name[][11]={{"empty"},{"Charmander"},{"Pikachu"},{"Squirtle"},{"Bulbasaur"},{"Pidgeotto"},{"Ratata"},{"Mug"},{"Caterpie"},{"Zubat"},{"Krabby"}};
	int range[]={0,1,3,4,3,2,2,1,2,3,2};																			/* First index is empty, because pokemon    */
	attack_type type[]={emptyy,quadratic,linear,linear,linear,quadratic,linear,quadratic,quadratic,linear,linear};	/* index start 1. So, All data start		*/
	int attack_power[]={0,500,350,300,400,250,250,350,200,350,300};													/* 0 or empty. This will facilitate my work */
	int stamina[]={0,2200,1500,1700,2500,1900,2500,3000,1200,1250,2600};											/* in the following sections.				*/
	pokemon Pokemons[]={empty,Charmander,Pikachu,Squirtle,Bulbasaur,Pidgeotto,Ratata,Mug,Caterpie,Zubat,Krabby};
	pokemon myPokemons[4]={0};
	clear();
	while(exit)
	{
		printf("Please select an option to continue:\n\n");
		printf("1) Open Pokedex\n");
		printf("2) Go to Oak’s Laboratory\n");
		printf("3) Enter the tournament\n");
		printf("4) Exit\n");
		printf("Choice : ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				clear();
				pokedex(Pokemon_name,range,type,attack_power,stamina);
				clear();
				break;
			case 2:
				clear();
				oaks_laboratory(Pokemon_name,Pokemons,myPokemons);
				break;
			case 3:
				clear();
				battle(Pokemon_name,range,type,attack_power,stamina,myPokemons);
				break;
			case 4:
				printf("\nExiting...\n");
				exit=0;
				break;
		}
	}
}
void pokedex(char Pokemon_name[][11],int range[],attack_type type[],int attack_power[],int stamina[])
{
	int i,exit=1;
	char str[32];
	clear();
	while(exit)
	{
		printf("Please type name of the Pokémon (type exit to close Pokedex): ");
		scanf("%s",str);
		for(i=1;i<=10;i++)
			if(myStringCmp(Pokemon_name[i],str)==0)
			{
				printf("\n  Name: %s\n",Pokemon_name[i]);
				if(type[i]==linear)
					printf("  A. Type: Linear\n");
				else if(type[i]==quadratic)
					printf("  A. Type: Quadratic\n");
				printf("  Range: %d\n",range[i]);
				printf("  A. Power: %d\n",attack_power[i]);
				printf("  Stamina: %d\n\n",stamina[i]);
			}
		if(myStringCmp(str,"exit")==0)
			exit=0;
	}
}
void oaks_laboratory(char Pokemon_name[][11],pokemon Pokemons[],pokemon *myPokemons)
{
	int choice,exit=1;
	while(exit)
	{
		printf("Welcome to Laboratory of Professer Oak. How can i help you?\n\n");
		printf("1) Show Pokémons\n");
		printf("2) Catch a Pokémon\n");
		printf("3) Release a Pokémon\n");
		printf("4) Show my pocket\n");
		printf("5) Back\n");
		printf("Choice : ");
		scanf("%d",&choice);
		clear();
		switch(choice)
		{
			case 1:
				show_Pokemons(Pokemon_name,myPokemons,10);
				break;
			case 2:
				catch_a_pokemon(Pokemon_name,Pokemons,myPokemons);
				break;
			case 3:
				release_a_pokemon(Pokemon_name,Pokemons,myPokemons);
				break;
			case 4:
				show_Pokemons(Pokemon_name,myPokemons,0);
				break;
			case 5:
				exit=0;
				break;
		}
	}
}
void show_Pokemons(char Pokemon_name[][11],pokemon Pokemons[],int pokemon_count)
{
	int i=0,exit=1;
	if(pokemon_count==10)
		for(i=1;i<=pokemon_count;i++)
			printf("  %d - %s\n",i,Pokemon_name[i]);
	else
		while(exit)
		{
			if(Pokemons[i]!=0&&i<4)
				printf("%d - %s\n",i+1,Pokemon_name[Pokemons[i]]);
			if(i==4)
				exit=0;
			i++;
		}
}
void catch_a_pokemon(char Pokemon_name[][11],pokemon Pokemons[],pokemon *my_pocket)
{
	int i=0,j,choice,situation=1;
	while(my_pocket[i]!=0&&i<4)		/* It's looking at the condition of our pocket. */
		++i;						/* It passes the full parts and comes to the empty part. */
	if(i<4)		// If pocket is not full
	{
		show_Pokemons(Pokemon_name,Pokemons,10);
		printf("\nYour pocket situation (%d/4)\n\n",i);
		choice=getInput("What pokémon do you want to catch ?\nChoice : ","Pokémon isn't found. Try again.\n",1,10);
		for(j=0;j<4;j++)
			if(my_pocket[j]==choice)
				situation=0;
		clear();
		if(situation)
		{
			printf("** %s was successfully caught. **\n\n",Pokemon_name[choice]);
			my_pocket[i]=choice;
		}
		else
			printf("** %s was caught before. Try again. **\n\n",Pokemon_name[choice]);
	}
	else
		printf("** Your pocket is full. **\n\n");
}
void release_a_pokemon(char Pokemon_name[][11],pokemon Pokemons[],pokemon *my_pocket)
{
	int i=0,count=0,choice;
	for(i=0;i<4;i++)			/* It's looking at the condition of our pocket. */
		if(my_pocket[i]!=0)
			++count;
	if(count>0)		// If we have a pokemon
	{
		show_Pokemons(Pokemon_name,my_pocket,0);
		choice=getInput("What pokémon do you want to release : ","Pokémon isn't found. Try again...\n",1,4);
		if(my_pocket[choice-1]!=0)
		{
			printf("%s was released from your pocket...\n",Pokemon_name[my_pocket[choice-1]]);
			my_pocket[choice-1]=0;
		}
		else
			printf("\n** This poketop is already empty. Try again. **\n\n");
	}
	else
		printf("** You don't have any pokemon.  **\n\n");
}
void battle(char Pokemon_name[][11],int range[],attack_type type[],int attack_power[],int stamina[],pokemon user_Pokemons[])
{
	int area[8][8]={0};
	int pokemon_staminas_view[8][8]={0};
	int checkSelected[][2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1}};	// This array will allow us to put our pokemon in different places. I choose initial values as -1.
	int i=0,j=0,n1=0,n2=0,count=0,situation=1,turn=0;
	int random,rx,ry,checkRand[4]={0};
	char str[255];
	int selectedPokemon,selectedMovement,selectedWay;
	int checkMovement;

	while(user_Pokemons[i]!=0&&i<4)		/* It's looking at the condition of our pocket. */
		++i;
	if(i==4)	// If our pocket is full
	{
		for(i=0;i<25;i++)
		{
			for(j=0;j<73;j++)
				if(i%3==0)
					printf("-");
				else if(j%9==0)
					printf("|");
				else if((i==2||i==5)&&i%3==2&&j%9==2)
				{
					printf("(%d,%d)",n1,n2);
					++n2;
					if(n2==8)
						n2=0,n1++;
				}
				else if((i==2||i==5)&&(j%9==3||j%9==4||j%9==5||j%9==6));
				else
					printf(" ");
			printf("\n");
		}
		while(count!=4)
		{
			printf("Where would you like to place the %s?\n",Pokemon_name[user_Pokemons[count]]);
			n1=getInput("Row: ","Please select right row : ",0,1);
			n2=getInput("Column : ","Please select right column : ",0,7);
			for(i=0;i<4;i++)											/*	This loop check the place 						*/
				if(checkSelected[i][0]==n1&&checkSelected[i][1]==n2)	/*	If this place is empty, situation will return 1 */
					situation=0;										/*	Else situation will return 0 					*/
			if(situation)
			{
				checkSelected[count][0]=n1;
				checkSelected[count][1]=n2;
				area[n1][n2]=user_Pokemons[count];
				count++;
			}
			else
				printf("This area was selected before.\nTry again.\n");
			situation=1;
		}
		for(i=0;i<4;i++)					/* This loop will place AI's pokemon. */
		{
			random=rand()%10+1;				/* Random pokemon will be selected. */
			rx=rand()%2+6;					/* Random coordinate will be selected. */
			ry=rand()%8;					/* Random coordinate will be selected. */
			for(j=0;j<4;j++)				/* This loop will check if the same Pokémon was selected before */
				if(checkRand[j]==-random)
					situation=0;
			if(area[rx][ry]==0&&situation)	/* If the area to be placed is empty, place it again, if not, select random position again. */
			{
				area[rx][ry]=-random;		/* AI's pokemons is like that -Pikachu -Charmander */
				checkRand[i]=-random;
			}
			else
				i--;
			situation=1;
		}
		for(i=0;i<8;i++)						/* This loop will place the health of all the pokemon on the map. */
			for(j=0;j<8;j++)
				if(area[i][j]!=0)
					if(area[i][j]<0)
						pokemon_staminas_view[i][j]=stamina[-area[i][j]];	/* -area because AI's pokemons is like that -Pikachu,-Charmander. */
					else
						pokemon_staminas_view[i][j]=stamina[area[i][j]];
		clear();
		while(checkTournament(area,pokemon_staminas_view,user_Pokemons,checkRand))
		{
			show_area(Pokemon_name,area,pokemon_staminas_view);
			if(turn%2==0)	// if turn is ours
			{
				while(situation)
				{
					printf("What pokémon do you want to move (Full name): ");
					scanf(" %s",str);
					for(i=1;i<=10;i++)
						for(j=0;j<4;j++)
							if(myStringCmp(str,Pokemon_name[i])==0&&user_Pokemons[j]==i)
							{
								selectedPokemon=i;
								situation=0;
							}
				}
				selectedWay=getInput("Which way would you like to go? : ","Please select right way! ",3,7);
				if(selectedWay!=5)
					selectedMovement=getInput("How many units would you like to go forward? [0,2]: ","Please select right movement! ",0,2);
				clear();
				checkMovement=checkMoveAndGo(Pokemon_name,area,pokemon_staminas_view,selectedPokemon,selectedMovement,selectedWay,&turn);
				if(checkMovement)
					attack_in_range(area,pokemon_staminas_view,range,type,attack_power,selectedPokemon);
			}
			else
			{
				selectedPokemon=checkRand[rand()%4];	// AI's pokemons
				while(selectedPokemon==0)
					selectedPokemon=checkRand[rand()%4];
				selectedMovement=rand()%3;				// AI's pokemon's movement
				selectedWay=rand()%5+3;					// AI's pokemon's way
				clear();
				checkMovement=checkMoveAndGo(Pokemon_name,area,pokemon_staminas_view,selectedPokemon,selectedMovement,selectedWay,&turn);
				if(checkMovement)
					attack_in_range(area,pokemon_staminas_view,range,type,attack_power,selectedPokemon);
			}
			situation=1;
		}
	}
	else
		printf("** Your Pokémon number is insufficient. **\n** Pokémon number should be 4. **\n** Catch the pokémon in the lab. **\n\n");
}
void show_area(char Pokemon_name[][11],int area[][8],int pokemon_staminas_view[][8])
{
	int i,j;
	for(i=0;i<25;i++)
	{
		for(j=0;j<73;j++)
		{
			if(i%3==0)
				printf("-");
			else
				if(j%9==0)
					printf("|");
				else
					if(i%3==1&&j%9==4&&area[(i-1)/3][j/9]!=0)
						if(area[(i-1)/3][j/9]<0)
							printf("%c%c",Pokemon_name[-area[(i-1)/3][j/9]][0],Pokemon_name[-area[(i-1)/3][j/9]][1]);
						else
							printf("%c%c",Pokemon_name[area[(i-1)/3][j/9]][0],Pokemon_name[area[(i-1)/3][j/9]][1]);
					else if(i%3==1&&j%9==5&&area[(i-1)/3][j/9]!=0);
					else if(i%3==2&&j%9==2)
						if(area[((i+1)/3)-1][(j/9)]!=0)
							printf("(%4d)",pokemon_staminas_view[((i+1)/3)-1][(j/9)]);
						else
							printf("      ");
					else if(i%3==2&&(j%9==3||j%9==4||j%9==5||j%9==6||j%9==7));
					else
						printf(" ");
		}
		printf("\n");
	}
	printf("\t\t\t            3\n");		/* These are for show the ways. */
	printf("\t\t\t            ^\n");
	printf("\t\t\t            |\n");
	printf("\t\t\t     4 < -- 5 -- > 6\n");
	printf("\t\t\t            |\n");
	printf("\t\t\t            V\n");
	printf("\t\t\t            7\n");
}
int checkMoveAndGo(char Pokemon_name[][11],int area[][8],int pokemon_staminas_view[][8],int selectedPokemon,int selectedMovement,int selectedWay,int *turn)
{
	int i,j,x,y,situation=0;
	for(i=0;i<8;i++)						 	/* This loop controls where Pokemon is. */
		for(j=0;j<8;j++)					 	/* Then loop save coordinats. */
			if(area[i][j]==selectedPokemon)
				x=i,y=j;
	switch(selectedWay)																		/* If the selected movement is able to do.*/
	{
		case 7:
			if(x+selectedMovement<8&&area[x+selectedMovement][y]==0)
			{
				area[x+selectedMovement][y]=selectedPokemon;
				pokemon_staminas_view[x+selectedMovement][y]=pokemon_staminas_view[x][y];
				situation=1;
			}
			break;
		case 6:
			if(y+selectedMovement<8&&area[x][y+selectedMovement]==0)
			{
				area[x][y+selectedMovement]=selectedPokemon;
				pokemon_staminas_view[x][y+selectedMovement]=pokemon_staminas_view[x][y];
				situation=1;
			}
			break;
		case 5:
			situation=1;
			break;
		case 4:
			if(y-selectedMovement>=0&&area[x][y-selectedMovement]==0)
			{
				area[x][y-selectedMovement]=selectedPokemon;
				pokemon_staminas_view[x][y-selectedMovement]=pokemon_staminas_view[x][y];
				situation=1;
			}
			break;
		case 3:
			if(x-selectedMovement>=0&&area[x-selectedMovement][y]==0)
			{
				area[x-selectedMovement][y]=selectedPokemon;
				pokemon_staminas_view[x-selectedMovement][y]=pokemon_staminas_view[x][y];
				situation=1;
			}
			break;
	}
	if(situation&&selectedWay!=5)	// if pokemon don't stops
	{
		area[x][y]=0;
		pokemon_staminas_view[x][y]=0;
	}
	else if(selectedWay==5);	// ıf pokemon stops, it will do anyting.
	else
	{
		printf("** Invalid movement **\n** Try again **\n");
		(*turn)--;		// Turn is changing
	}
	if(situation&&(*turn)%2==0)
		printf("** We attacked with %s **\n",Pokemon_name[selectedPokemon]);
	if(situation&&(*turn)%2==1)
		printf("** The AI attacked with %s **\n",Pokemon_name[-selectedPokemon]);
	(*turn)++;
	return situation;
}
void attack_in_range(int area[][8],int pokemon_staminas_view[][8],int range[],attack_type type[],int attack_power[],int selectedPokemon)
{
	int i,j,x,y;
	int distance=0,minDistance=5,turn=1;
	for(i=0;i<8;i++)				/* This loop will find the where pokemon is. */
		for(j=0;j<8;j++)
			if(area[i][j]==selectedPokemon)
				x=i,y=j;

	if(selectedPokemon<0)
		turn=-1,selectedPokemon=-selectedPokemon;

	if(type[selectedPokemon]==linear)			// ıf type linear,
	{
		for(i=1;i<=range[selectedPokemon];i++)
		{
			distance=i;
			if(x-i>=0)							/* It finds the nearest enemy pokemon. */
			{
				if(area[x-i][y]>0&&turn==-1)
					if(minDistance>distance)
						minDistance=distance;
				if(area[x-i][y]<0&&turn==1)
					if(minDistance>distance)
						minDistance=distance;
			}
			if(y+i<8)
			{
				if(area[x][y+i]>0&&turn==-1)
					if(minDistance>distance)
						minDistance=distance;
				if(area[x][y+i]<0&&turn==1)
					if(minDistance>distance)
						minDistance=distance;
			}
			if(x+i<8)
			{
				if(area[x+i][y]>0&&turn==-1)
					if(minDistance>distance)
						minDistance=distance;
				if(area[x+i][y]<0&&turn==1)
					if(minDistance>distance)
						minDistance=distance;
			}
			if(y-i>=0)
			{
				if(area[x][y-i]>0&&turn==-1)
					if(minDistance>distance)
						minDistance=distance;
				if(area[x][y-i]<0&&turn==1)
					if(minDistance>distance)
						minDistance=distance;
			}
		}
		if(minDistance!=5)
		{
			if(x-minDistance>=0)
			{
				if(area[x-minDistance][y]>0&&turn==-1)
					pokemon_staminas_view[x-minDistance][y]-=attack_power[selectedPokemon];	// AI's pokemon will attack
				if(area[x-minDistance][y]<0&&turn==1)
					pokemon_staminas_view[x-minDistance][y]-=attack_power[selectedPokemon]; // Our's pokemon will attack
			}
			if(x+minDistance<8)
			{
				if(area[x+minDistance][y]>0&&turn==-1)
					pokemon_staminas_view[x+minDistance][y]-=attack_power[selectedPokemon];	// AI's pokemon will attack
				if(area[x+minDistance][y]<0&&turn==1)
					pokemon_staminas_view[x+minDistance][y]-=attack_power[selectedPokemon];	// Our's pokemon will attack
			}
			if(y+minDistance<8)
			{
				if(area[x][y+minDistance]>0&&turn==-1)
					pokemon_staminas_view[x][y+minDistance]-=attack_power[selectedPokemon];	// AI's pokemon will attack
				if(area[x][y+minDistance]<0&&turn==1)
					pokemon_staminas_view[x][y+minDistance]-=attack_power[selectedPokemon];	// Our's pokemon will attack
			}
			if(y-minDistance>=0)
			{
				if(area[x][y-minDistance]>0&&turn==-1)
					pokemon_staminas_view[x][y-minDistance]-=attack_power[selectedPokemon];	// AI's pokemon will attack
				if(area[x][y-minDistance]<0&&turn==1)
					pokemon_staminas_view[x][y-minDistance]-=attack_power[selectedPokemon];	// Our's pokemon will attack
			}
		}
	}
	else
		for(i=x-range[selectedPokemon];i<=x+range[selectedPokemon];i++)				/* This loop check. If there are any pokemons in the range, */
			for(j=y-range[selectedPokemon];j<=y+range[selectedPokemon];j++)			/* selected pokemon attacks him. 							*/
				if((i>=0&&i<8)&&(j>=0&&j<8))
				{
					if(area[i][j]>0&&turn==-1)		// If AI's pokemons
						pokemon_staminas_view[i][j]-=attack_power[selectedPokemon];		
					else if(area[i][j]<0&&turn==1)
						pokemon_staminas_view[i][j]-=attack_power[selectedPokemon];
				}
}
int checkTournament(int area[][8],int pokemon_staminas_view[][8],pokemon user_Pokemons[],int ai_Pokemons[])
{
	int i,j,k,countHUMAN=0,countAI=0;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
			if(pokemon_staminas_view[i][j]<=0)
			{
				if(area[i][j]<0)
					for(k=0;k<4;k++)
						if(ai_Pokemons[k]==area[i][j])
							ai_Pokemons[k]=0;
				if(area[i][j]>0)
					for(k=0;k<4;k++)
						if(user_Pokemons[k]==area[i][j])
							user_Pokemons[k]=0;
				area[i][j]=0;
			}
			if(area[i][j]>0)
				countHUMAN++;
			if(area[i][j]<0)
				countAI++;
		}
	if(countHUMAN>0&&countAI==0){
		printf("** Congrulations. **\n** You win. **\n");
		return 0;
	}
	if(countAI>0&&countHUMAN==0){
		printf("** AI won. **\n** You lose. **\n");
		return 0;
	}
	return 1;
}
int getInput(char str1[],char str2[],int lower_bound,int upper_bound)
{
	int num;
	printf("%s",str1);
	scanf(" %d",&num);
	while(num<lower_bound||num>upper_bound)
	{
		printf("%s",str2);
		scanf(" %d",&num);
	}
	return num;
}
int myStringCmp(char *str1,char *str2)
{
	while(*str1&&*str2&&*str1==*str2)
		++str1,++str2;
	return *str1-*str2;
}