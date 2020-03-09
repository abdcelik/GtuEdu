#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define clear() printf("\033[H\033[J")	// clear the screen
typedef enum{start,property,tax,punish}block_type;
typedef enum{noone,cap,car}player_type;

struct player
{
	player_type type;
	int current_block_id;
	int owned_block_ids[12];
	int account;
	int turn_to_wait;
	char *name;
};

struct block
{
	int block_id;
	char *name;
	int price;
	int rent;
	int rent_1;
	int rent_2;
	int rent_3;
	int house_price;
	int house_count;
	struct player owner;
	block_type type; 
};

void init_the_board(struct block board[]);
void show_board(struct block board[],struct player player_one,struct player player_two);
void show_properties(struct block board[]);
void buy_property(struct block* current_block,struct player* current_player);
void sell_property(struct block board[],struct player* current_player);
void gameplay(struct block board[],struct player player_one,struct player player_two);

void player_information(struct player* current_player);
int buy_house(struct block* current_block,struct player* current_player);
int pay_rent(struct block board[],struct player* current_player);
void fill_board(struct block*,int,char*,int,int,int,int,int,int,int,player_type,block_type);
int get_int(char*,char*,int,int);
int random_number(int,int);

int main()
{
	struct block board[20];
	struct player player1 = {cap,0,{0},100000,0,"Cap"};
	struct player player2 = {car,0,{0},100000,0,"Car"};
	srand(time(NULL));
	init_the_board(board);
	gameplay(board,player1,player2);
	return 0;
}
void gameplay(struct block board[],struct player player_one,struct player player_two)
{
	int i,exit=1,deed=0,bankrupt=0,choice=0,movement,situation;
	char chr;
	struct player *current_player = ( (random_number(0,1)==0) ? &player_one : &player_two );
	show_board(board,player_one,player_two);
	do
	{
		while(choice!=1)
		{
			printf("\n*** The turn is in %s ***\n",current_player->name);
			printf("1 - Roll The Dice\n");
			printf("2 - Show My Account\n");
			printf("3 - Show My Properties\n");
			printf("4 - Show Property Deeds\n");
			printf("5 - Buy Property\n");
			printf("6 - Buy House\n");
			printf("7 - Sell Property\n");
			printf("Please select an option to continue : ");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:
					movement=random_number(1,6);
					printf("The dice : %d\n",movement);
					break;
				case 2:
					show_board(board,player_one,player_two);
					player_information(current_player);
					break;
				case 3:
					for(i=0;i<11;i++)
						if(current_player->owned_block_ids[i]!=0)
							printf("%s\n",board[current_player->owned_block_ids[i]].name);
					break;
				case 4:
					show_board(board,player_one,player_two);
					show_properties(board);
					break;
				case 5:
					buy_property(&board[current_player->current_block_id],current_player);
					break;
				case 6:
					situation=buy_house(&board[current_player->current_block_id],current_player);
					break;
				case 7:
					sell_property(board,current_player);
					break;
			}
		}
		current_player->current_block_id += movement;		/* The dice is added to current block id 	*/
		if(current_player->current_block_id > 19 )			/* if current block id is greater than 19 	*/
			current_player->account += 10000;				/* means the current user is past the start */
		current_player->current_block_id %= 20;				/* so 10.000$ is added his/her account 		*/
		show_board(board,player_one,player_two);			/* and current block id is got %20			*/
		
		if		(board[current_player->current_block_id].type == start);		// Don't anything
		else if	(board[current_player->current_block_id].type == punish)
		{
			current_player->turn_to_wait = board[current_player->current_block_id].rent;
			printf("** You will wait %d turn **\n",current_player->turn_to_wait);
		}
		else if	(board[current_player->current_block_id].type == tax)
			bankrupt=pay_rent(board,current_player);
		else if	(board[current_player->current_block_id].type == property)
		{
			if(board[current_player->current_block_id].owner.type == noone)
			{
				while(exit)
				{
					if(current_player->account >= board[current_player->current_block_id].price)
					{
						buy_property(&board[current_player->current_block_id],current_player);
						exit=0;
					}
					else
					{
						deed=0;
						clear();
						show_board(board,player_one,player_two);
						printf("** Your money isn't enough **\n");
						for(i=0;i<12;i++)
							if(current_player->owned_block_ids[i]!=0)
								deed++;
						if(deed!=0)
						{
							printf("** The required money is %d$ **\n",board[current_player->current_block_id].price - current_player->account);
							printf("Do you want to sell your deeds ? (Y/N) : ");
							scanf(" %c",&chr);
							if(chr=='Y'||chr=='y')
								sell_property(board,current_player);
							else
								exit=0;
						}
						else
							exit=0;
					}
				}
			}
			else if(board[current_player->current_block_id].owner.type != current_player->type)
				bankrupt=pay_rent(board,current_player);
		}
		if(board[current_player->current_block_id].owner.type == current_player->type)
		{
			exit=1;
			while(exit)
			{
				deed=0;
				situation=buy_house(&board[current_player->current_block_id],current_player);
				if(situation==-1)
				{
					for(i=0;i<12;i++)
						if(current_player->owned_block_ids[i]!=0)
							deed++;
					printf("Do you want to sell your deeds ?(Y/N) : ");
					scanf(" %c",&chr);
					if((chr == 'Y' || chr == 'y') && deed != 0)
						sell_property(board,current_player);
					else
						exit=0;
				}
				else if(situation==-2)
					exit=0;
			}
		}

		if(current_player->type==player_one.type)
		{
			if(player_two.turn_to_wait==0)
				current_player=&player_two;
			else if(player_one.turn_to_wait!=0)
			{
				if(player_one.turn_to_wait>=player_two.turn_to_wait)
				{
					player_one.turn_to_wait-=player_two.turn_to_wait;
					player_two.turn_to_wait=0;
				}
				else
				{
					player_two.turn_to_wait-=player_one.turn_to_wait;
					player_one.turn_to_wait=0;
				}
			}
			else
				player_two.turn_to_wait--;
		}
		else
		{
			if(player_one.turn_to_wait==0)
				current_player=&player_one;
			else
				player_one.turn_to_wait--;
		}
		choice=0,exit=1;
	}while(bankrupt==0);
}
void buy_property(struct block* current_block,struct player* current_player)
{
	int i=0;
	char choice;
	if(current_block->type != property)
		printf("** This block can not bought! **\n");
	else if(current_block->owner.type == current_player->type)
		printf("** This deed already yours **\n");
	else if(current_block->owner.type != noone)
		printf("** This block was bought by other players **\n");
	else
	{
		while(current_player->owned_block_ids[i] != 0)
			i++;
		player_information(current_player);
		printf("Do you want to buy %s for %d$ (Y/N): ", current_block->name,current_block->price);
		scanf(" %c",&choice);
		if(choice == 'Y' || choice == 'y')
		{
			if(current_player->account < current_block->price)
				printf("** Insufficient balance! **\n");
			else
			{
				current_block->owner.type = current_player->type;
				current_player->owned_block_ids[i] = current_block->block_id;
				current_player->account -= current_block->price;
				printf("** %s was bought **\n",current_block->name);
			}
		}
	}
}
int buy_house(struct block* current_block,struct player* current_player)
{
	char choice=1;
	if(current_player->type == current_block->owner.type)
	{
		printf("** There are %d house in %s **\n",current_block->house_count,current_block->name);
		printf("A house price is %d$.\n",current_block->house_price);
		printf("Do you want to build house ? (Y/N): ");
		scanf(" %c",&choice);
		if((choice == 'Y' || choice == 'y') && current_block->house_count<3)
		{
			if(current_player->account >= current_block->house_price)
			{
				current_player->account -= current_block->house_price;
				current_block->house_count ++;
				printf("** A house built succesfully **\n");
			}
			else
			{
				printf("** Your money isn't enough **\n");
				return -1;
			}
		}
		else if(current_block->house_count == 3)
		{
			printf("** Already built the maximum houses **\n");
			return -2;
		}
		else
		{
			choice=0;
			return -2;
		}
	}
	else
	{
		printf("** You can't build this block **\n");
		return -2;
	}
	return 0;
}
void sell_property(struct block board[],struct player* current_player)
{
	int i,choice,exit=1,sellPrice=0,deed=0;
	char chr;
	while(exit)
	{
		for(i=0;i<12;i++)
			if(current_player->owned_block_ids[i]!=0)
				deed++;
		if(deed==0)
		{
			printf("** There is no deed to be sold **\n");
			exit=0;
		}
		else
		{
			for(i=0;i<12;i++)
				if(current_player->owned_block_ids[i]!=0)
					printf("%d - %s\n",current_player->owned_block_ids[i],board[current_player->owned_block_ids[i]].name);
			printf("0 - Exit\n");
			choice=get_int("Choice : ","Choice must be between 0 and 19 : ",0,19);
			if(choice==0)
				exit=0;
			else if(board[choice].owner.type == current_player->type)
			{
				sellPrice += (board[choice].price + (board[choice].house_count * board[choice].house_price))/2;
				printf("%s's sales fee is %d$.\n",board[choice].name,sellPrice);
				printf("Do you want to sell ? (Y/N): ");
				scanf(" %c",&chr);
				if(chr == 'Y' || chr == 'y')
				{
					current_player->account += sellPrice;
					for(i=0;i<12;i++)
						if(current_player->owned_block_ids[i] == choice)
							current_player->owned_block_ids[i]=0;
					board[choice].owner.type = noone;
					board[choice].house_count = 0;
				}
				else
					printf("** The deed isn't sold **\n");
			}
			else
				printf("** You can't sell this block! **\n");
			sellPrice=0;
		}
	}
}
int pay_rent(struct block board[],struct player* current_player)
{
	int i,exit=1,bankrupt=0,deed=0,payment;
	int house=board[current_player->current_block_id].house_count;
	if(house == 0)
		payment=board[current_player->current_block_id].rent;
	else if(house == 1)
		payment=board[current_player->current_block_id].rent_1;
	else if(house == 2)
		payment=board[current_player->current_block_id].rent_2;
	else
		payment=board[current_player->current_block_id].rent_3;
	while(exit)
	{
		if(current_player->account>=payment)
		{
			current_player->account -= payment;
			board[current_player->current_block_id].owner.account += payment;
			printf("** %s paid %d$ for %s's rent **\n",current_player->name,payment,board[current_player->current_block_id].name);
			exit=0;
		}
		else
		{
			player_information(current_player);
			printf("** Your money's not enough to pay %d$ rent **\n",payment);
			for(i=0;i<12;i++)
				if(current_player->owned_block_ids[i]!=0)
					deed++;
			if(deed==0)
			{
				printf("** %s went bankrupt **\n",current_player->name);
				exit=0,bankrupt=1;
			}
			else
			{
				printf("** You must sell your deed **\n");
				sell_property(board,current_player);
			}
		}
	}
	return bankrupt;
}
void show_properties(struct block board[])
{
	int i,j,choice,exit=1;
	printf("Please select a property to see details:\n");
	for(i=0;i<20;i++)
		if(board[i].type==property)
			printf("%d -\t%s\n",board[i].block_id,board[i].name);
	printf("0 -\tExit\n\n");
	while(exit)
	{
		printf("Choice : ");
		scanf("%d",&choice);
		if(choice==0)
			exit=0;
		else if(choice>=0&&choice<=19)
			if(board[choice].type==property)
				exit=0;
	}
	if(choice!=0)
	{
		printf("\n\n\n");
		for(i=0;i<10;i++)
		{
			if(i==0||i==2||i==7||i==9)
				for(j=0;j<33;j++)
					printf("-");
			else if(i==1)	printf("|%10s%-11s%10s|","",board[choice].name,"");
			else if(i==3)	printf("|%7s%-16s%d$	|","","Rent",board[choice].rent);
			else if(i==4)	printf("|%7s%-16s%d$	|","","Rent 1 H",board[choice].rent_1);
			else if(i==5)	printf("|%7s%-16s%d$	|","","Rent 2 H",board[choice].rent_2);
			else if(i==6)	printf("|%7s%-16s%d$	|","","Rent 3 H",board[choice].rent_3);
			else			printf("|%7s%-16s%d$	|","","House Price",board[choice].house_price);
			printf("\n");
		}
	}
}
void show_board(struct block board[],struct player player_one,struct player player_two)
{
	int i,j,k,index,p1,p2;
	clear();
	p1=player_one.current_block_id;
	p2=player_two.current_block_id;
	for(i=0;i<6;i++)
	{
		if(i>=2&&i<=4)
		{
			for(j=0;j<25;j++)
				printf("-");
			printf("%95s","");
			for(j=0;j<25;j++)
				printf("-");
		}
		else
			for(j=0;j<145;j++)
				printf("-");
		printf("\n");
		for(j=0;j<3;j++)
		{
			for(k=0;k<6;k++)
			{
				if((i>=1&&i<=4)&&(k>=1&&k<=4))
					if(k==1)
						printf("%-24s","|");
					else
						printf("%24s","");
				else
				{
					printf("|");
					if(i<=k)	index=i+k;
					else	index=20-i-k;
					if(j==0)
						printf("%7s%-16s","",board[index].name);
					else if(j==1&&board[index].type==property)
						printf("%7s%-5d%-11s","",board[index].price,"$");	
					else if(j==1&&board[index].type==tax)
						printf("%7s%-4d%-12s","",board[index].rent,"$");
					else if(j==2&&p1==p2&&p1==index)
						printf("%7s%-9s%7s","","Cap,Car","");
					else if(j==2&&p1==index)
						printf("%7s%-16s","","Cap");
					else if(j==2&&p2==index)
						printf("%7s%-16s","","Car");			
					else
						printf("%23s","");
				}
			}
			printf("|\n");
		}
	}
	for(j=0;j<145;j++)
		printf("-");
	printf("\n");
}
void init_the_board(struct block board[])
{
	fill_board(&board[ 0] , 0 ,"Start"		 ,    0 ,   0 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,start 		);
	fill_board(&board[ 1] , 1 ,"Esenyurt"	 ,16000 , 800 , 4000 , 9000 ,25000 ,10000 ,0 ,noone ,property	);
	fill_board(&board[ 2] , 2 ,"Car Park"	 ,    0 ,1500 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,tax		);
	fill_board(&board[ 3] , 3 ,"Tuzla"		 ,16500 , 850 , 4250 , 9500 ,26000 ,12000 ,0 ,noone ,property	);
	fill_board(&board[ 4] , 4 ,"Arnavutkoy"	 ,17000 , 875 , 4500 ,10000 ,28000 ,12000 ,0 ,noone ,property	);
	fill_board(&board[ 5] , 5 ,"Wait 2 Turn" ,    0 ,   2 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,punish		);
	fill_board(&board[ 6] , 6 ,"Catalca"	 ,20000 ,1000 , 5000 ,12000 ,30000 ,13000 ,0 ,noone ,property	);
	fill_board(&board[ 7] , 7 ,"Beykoz"		 ,23000 ,1100 , 5500 ,12500 ,33000 ,13000 ,0 ,noone ,property	);
	fill_board(&board[ 8] , 8 ,"Car Fix"	 ,    0 ,1750 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,tax		);
	fill_board(&board[ 9] , 9 ,"Maltepe"	 ,30000 ,1350 , 7000 ,15000 ,40000 ,15000 ,0 ,noone ,property	);
	fill_board(&board[10] ,10 ,"Bills"		 ,    0 ,2250 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,tax		);
	fill_board(&board[11] ,11 ,"Sisli"		 ,33000 ,1500 , 8000 ,16000 ,42000 ,16000 ,0 ,noone ,property	);
	fill_board(&board[12] ,12 ,"Oil"		 ,    0 ,2250 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,tax		);
	fill_board(&board[13] ,13 ,"Atasehir"	 ,35000 ,1600 , 8500 ,17000 ,45000 ,17000 ,0 ,noone ,property	);
	fill_board(&board[14] ,14 ,"Sariyer"	 ,40000 ,1750 , 9500 ,19000 ,48000 ,19000 ,0 ,noone ,property	);
	fill_board(&board[15] ,15 ,"Wait 1 Turn" ,    0 ,   1 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,punish		);
	fill_board(&board[16] ,16 ,"Kadikoy"	 ,43000 ,1900 ,11000 ,21500 ,55000 ,23000 ,0 ,noone ,property	);
	fill_board(&board[17] ,17 ,"Besiktas"	 ,60000 ,2500 ,15000 ,28000 ,60000 ,30000 ,0 ,noone ,property	);
	fill_board(&board[18] ,18 ,"Vocation"	 ,    0 ,5000 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,tax		);
	fill_board(&board[19] ,19 ,"Bebek"		 ,70000 ,3500 ,20000 ,35500 ,65000 ,35000 ,0 ,noone ,property	);
}
void fill_board(struct block *index,int id,char *n,int price,int r,int r1,int r2,int r3,int hp,int hc,player_type p,block_type t)
{
	index->block_id=id;
	index->name=n;
	index->price=price;
	index->rent=r;
	index->rent_1=r1;
	index->rent_2=r2;
	index->rent_3=r3;
	index->house_price=hp;
	index->house_count=hc;
	index->owner.type=p;
	index->type=t;
}
void player_information(struct player* current_player)
{
	printf("** %s's amount of the current money : %d$ **\n",current_player->name,current_player->account);
}
int get_int(char *s1,char *s2,int lower_bound,int upper_bound)
{
	int var;
	printf("%s",s1);
	scanf("%d",&var);
	while(var < lower_bound || var >upper_bound)
	{
		printf("%s",s2);
		scanf("%d",&var);
	}
	return var;
}
int random_number(int lower_bound,int upper_bound)
{
	int r;
	r=rand()%(upper_bound-lower_bound+1)+lower_bound;	// [lower_bound,upper_bound]
	return r;
}