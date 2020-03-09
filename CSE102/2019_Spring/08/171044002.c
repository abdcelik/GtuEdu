#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define clear() printf("\033[H\033[J")	// clear the screen
typedef enum{start,property,tax,punish,fortune}block_type;
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
	struct block *next;
};
struct fortune_card
{
	int card_no;
	char *card_name;
	struct fortune_card *next;
};

void gameplay(struct block*,struct player,struct player);
void player_information(struct player*);
void show_player_properties(struct block*,struct player*);
void show_properties(struct block*);
void buy_property(struct block*,struct player*);
void buy_house(struct block*,struct player*);
void sell_property(struct block*,struct player*);
int make_payment(struct block*,struct player*,struct player*,struct player*,char*);
int block_fortune(struct block*,struct player*,struct player*,struct player*);
void init_the_board(struct block**);
void add_ll(struct block**,int,char*,int,int,int,int,int,int,int,player_type,block_type);
void init_the_fortunecard(struct fortune_card**,int,char*);
void show_board(struct block*,struct player,struct player);
struct player *turn_player_or_ai(struct player*,struct player*,struct player*);
struct block *block_set_index(struct block*,int);
struct fortune_card *fortune_card_set_index(struct fortune_card*,int);
void free_block(struct block*);
void free_fortunecard(struct fortune_card*);
int average_properties(struct block*);
int random_number(int,int);
int get_int(char*,char*,int,int);
int str_cmp(char*,char*);

int main()
{
	srand(time(NULL));
	struct player player_1  = {car,0,{0},100000,0,"Car"};
	struct player player_ai = {cap,0,{0},100000,0,"Cap"};
	struct block *root = NULL;
	init_the_board(&root);
	gameplay(root,player_1,player_ai);
	free_block(root);
	return 0;
}
void gameplay(struct block *board,struct player player_1,struct player player_ai)
{
	int i,choice=0,bankrupt=0,exit=1,dice=0,deed=0,ave_pro;
	struct player *current_player = ( (random_number(0,1) == 0) ? &player_1 : &player_ai );  // it determine which one is start
	ave_pro=average_properties(board);
	clear();
	printf("** %s will start the Monopoly Game **\n",current_player->name);
	do
	{
		while(current_player->type == car && exit)
		{
			show_board(board,player_1,player_ai);
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
			clear();
			switch(choice)
			{
				case 1:
					dice=random_number(1,6);
					printf("** The dice : %d **\n",dice);
					current_player->current_block_id += dice;
					if(current_player->current_block_id > 23 )	// If player pass the start, the bank will pay 10000$ to player
						current_player->account += 10000 , current_player->current_block_id %= 24;	// And player's position will reset
					exit=0;
					break;
				case 2:
					player_information(current_player);
					break;
				case 3:
					show_player_properties(board,current_player);
					break;
				case 4:
					show_properties(board);
					break;
				case 5:
					buy_property(block_set_index(board,current_player->current_block_id),current_player);
					break;
				case 6:
					buy_house(block_set_index(board,current_player->current_block_id),current_player);
					break;
				case 7:
					sell_property(board,current_player);
					break;
			}
		}
		if(current_player->type == cap)
		{
			clear();
			printf("\n*** The turn is in %s ***\n",current_player->name);
			dice=random_number(1,6);
			printf("** Computer rolled the dice : %d **\n",dice);
			current_player->current_block_id += dice;
			if(current_player->current_block_id > 23 )	// If AI pass the start, the bank will pay 10000$ to AI
				current_player->account += 10000 , current_player->current_block_id %= 24;	// And AI's position will reset
			if(block_set_index(board,current_player->current_block_id)->type == property)
			{
				if(block_set_index(board,current_player->current_block_id)->owner.type == noone)
				{
					dice=random_number(1,6);
					if(block_set_index(board,current_player->current_block_id)->price < ave_pro || (dice>=1 && dice<=3))
						buy_property(block_set_index(board,current_player->current_block_id),current_player);
				}
				if(block_set_index(board,current_player->current_block_id)->owner.type == current_player->type)
				{
					for(i=0;i<=23;i++)
						if(block_set_index(board,i)->owner.type == current_player->type)
							deed++;
					dice=random_number(1,6);
					if(deed >= 4 && dice>=1 && dice<=3)
						buy_house(block_set_index(board,current_player->current_block_id),current_player);
				}
			}
		}
		if(block_set_index(board,current_player->current_block_id)->type == fortune)
			bankrupt=block_fortune(board,current_player,&player_1,&player_ai);
		if(block_set_index(board,current_player->current_block_id)->type == punish)
		{
			current_player->turn_to_wait = block_set_index(board,current_player->current_block_id)->rent;
			printf("** %s will wait %d turn **\n\n",current_player->name,current_player->turn_to_wait);
		}
		if(block_set_index(board,current_player->current_block_id)->type == tax)
			bankrupt=make_payment(board,current_player,&player_1,&player_ai,"Tax");
		if(block_set_index(board,current_player->current_block_id)->type == property)
			if(block_set_index(board,current_player->current_block_id)->owner.type != current_player->type && block_set_index(board,current_player->current_block_id)->owner.type != noone)
				bankrupt=make_payment(board,current_player,&player_1,&player_ai,"Rent");
		exit=1;
		show_board(board,player_1,player_ai);
		while(current_player->type == car && exit)
		{
			printf("1 - End The Tour\n");
			printf("2 - Show My Account\n");
			printf("3 - Show My Properties\n");
			printf("4 - Show Property Deeds\n");
			printf("5 - Buy Property\n");
			printf("6 - Buy House\n");
			printf("7 - Sell Property\n");
			printf("Please select an option to continue : ");
			scanf("%d",&choice);
			clear();
			switch(choice)
			{
				case 1:
					exit=0;
					break;
				case 2:
					player_information(current_player);
					break;
				case 3:
					show_player_properties(board,current_player);
					break;
				case 4:
					show_properties(board);
					break;
				case 5:
					buy_property(block_set_index(board,current_player->current_block_id),current_player);
					break;
				case 6:
					buy_house(block_set_index(board,current_player->current_block_id),current_player);
					break;
				case 7:
					sell_property(board,current_player);
					break;
			}
			show_board(board,player_1,player_ai);
		}
		printf("Enter to continue...");	// These are all for order terminal
		if(current_player->type == car)	//
			getchar();					//
		getchar();						//
		clear();
		current_player=turn_player_or_ai(current_player,&player_1,&player_ai);
		exit=1,deed=0;
	}while(bankrupt==0);
}
void player_information(struct player *current_player)
{
	printf("** %s's amount of the current money : %d$ **\n",current_player->name,current_player->account);
}
void show_player_properties(struct block *board,struct player *current_player)
{
	int i,deed=0;
	for(i=0;i<12;i++)
		if(current_player->owned_block_ids[i]!=0)
			deed++;
	if(deed != 0)
		for(i=0;i<12;i++)
		{
			if(current_player->owned_block_ids[i]!=0)
				printf("%d - %s\n",block_set_index(board,current_player->owned_block_ids[i])->block_id,block_set_index(board,current_player->owned_block_ids[i])->name);
		}
	else
		printf("** You do not have any properties **\n");
}
void show_properties(struct block *board)
{
	int i,j,choice,exit=1;
	printf("** Please select a property to see details **\n\n");
	for(i=0;i<=23;i++)
		if(block_set_index(board,i)->type == property)
			printf("%d -\t%s\n",block_set_index(board,i)->block_id,block_set_index(board,i)->name);
	printf("0 -\tExit\n\n");
	while(exit)
	{
		printf("Choice : ");
		scanf("%d",&choice);
		if(choice == 0)
			exit=0;
		else if(choice >= 0 && choice <= 23)
			if(block_set_index(board,choice)->type == property)
				exit=0;
	}
	if(choice != 0)
	{
		printf("\n\n");
		for(i=0;i<10;i++)
		{
			if(i==0||i==2||i==7||i==9)
				for(j=0;j<33;j++)
					printf("-");
			else if(i==1)	printf("|%10s%-11s%10s|","",block_set_index(board,choice)->name,"");
			else if(i==3)	printf("|%7s%-16s%d$	|","","Rent",block_set_index(board,choice)->rent);
			else if(i==4)	printf("|%7s%-16s%d$	|","","Rent 1 H",block_set_index(board,choice)->rent_1);
			else if(i==5)	printf("|%7s%-16s%d$	|","","Rent 2 H",block_set_index(board,choice)->rent_2);
			else if(i==6)	printf("|%7s%-16s%d$	|","","Rent 3 H",block_set_index(board,choice)->rent_3);
			else			printf("|%7s%-16s%d$	|","","House Price",block_set_index(board,choice)->house_price);
			printf("\n");
		}
	}
}
void buy_property(struct block *current_block,struct player *current_player)
{
	int i=0;
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
		if(current_player->account < current_block->price)
			printf("** Insufficient balance! **\n");
		else
		{
			current_block->owner.type = current_player->type;
			current_player->owned_block_ids[i] = current_block->block_id;
			current_player->account -= current_block->price;
			printf("** %s was bought by %s **\n",current_block->name,current_player->name);
		}
	}
}
void buy_house(struct block *current_block,struct player *current_player)
{
	if(current_player->type == current_block->owner.type)
	{
		printf("** There are %d house in %s **\n",current_block->house_count,current_block->name);
		printf("A house price is %d$.\n",current_block->house_price);
		if(current_block->house_count<3)
		{
			if(current_player->account >= current_block->house_price)
			{
				current_player->account -= current_block->house_price;
				current_block->house_count ++;
				printf("** A house built succesfully **\n");
				printf("** There are %d house in %s **\n",current_block->house_count,current_block->name);
			}
			else
				printf("** Your money isn't enough **\n");
		}
		else if(current_block->house_count == 3)
			printf("** Already built the maximum houses **\n");
	}
	else
		printf("** You can't build this block **\n");
}
void sell_property(struct block *board,struct player *current_player)
{
	int i,j,choice,exit=1,sellPrice=0,deed=0;
	char chr;
	while(exit)
	{
		if(current_player->type == car)
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
						printf("%d - %s\n",current_player->owned_block_ids[i],block_set_index(board,current_player->owned_block_ids[i])->name);
				printf("0 - Exit\n");
				choice=get_int("Choice : ","Choice must be between 0 and 19 : ",0,19);
				if(choice==0)
					exit=0;
				else if(block_set_index(board,choice)->owner.type == current_player->type)
				{
					sellPrice += (block_set_index(board,choice)->price + (block_set_index(board,choice)->house_count * block_set_index(board,choice)->house_price))/2;
					printf("%s's sales fee is %d$.\n",block_set_index(board,choice)->name,sellPrice);
					printf("Do you want to sell ? (Y/N): ");
					scanf(" %c",&chr);
					if(chr == 'Y' || chr == 'y')
					{
						current_player->account += sellPrice;
						for(i=0;i<12;i++)
							if(current_player->owned_block_ids[i] == choice)
								current_player->owned_block_ids[i]=0;
						block_set_index(board,choice)->owner.type = noone;
						block_set_index(board,choice)->house_count = 0;
					}
					else
						printf("** The deed isn't sold **\n");
				}
				else
					printf("** You can't sell this block! **\n");
				sellPrice=0;
			}
		}
		else
		{
			for(i=23;i>=0&&exit;i--)
				if(block_set_index(board,i)->owner.type == current_player->type)
				{
					sellPrice += (block_set_index(board,i)->price + (block_set_index(board,i)->house_count * block_set_index(board,i)->house_price))/2;
					current_player->account += sellPrice;
					for(j=0;j<12;j++)
						if(current_player->owned_block_ids[j] == block_set_index(board,i)->block_id)
							current_player->owned_block_ids[j]=0;
					exit=0;
				}
		}
	}
}
int make_payment(struct block *board,struct player *current_player,struct player *player_1,struct player *player_ai,char *s)
{
	int i,exit=1,deed=0,bankrupt=0,house,payment;
	while(exit)
	{
		deed=0;
		for(i=0;i<=23;i++)
			if(block_set_index(board,i)->owner.type == current_player->type)
				deed++;
		if(str_cmp(s,"Rent")==0 || str_cmp(s,"Tax")==0)
		{
			house=block_set_index(board,current_player->current_block_id)->house_count;
			if(house == 0)	payment=block_set_index(board,current_player->current_block_id)->rent;
			if(house == 1)	payment=block_set_index(board,current_player->current_block_id)->rent_1;
			if(house == 2)	payment=block_set_index(board,current_player->current_block_id)->rent_2;
			if(house == 3)	payment=block_set_index(board,current_player->current_block_id)->rent_3;
			if(current_player->account >= payment)
			{
				current_player->account -= payment;
				block_set_index(board,current_player->current_block_id)->owner.account += payment;
				printf("** %s paid %d$ for %s's rent **\n\n",current_player->name,payment,block_set_index(board,current_player->current_block_id)->name);
				exit=0;
			}
		}
		if(str_cmp(s,"Garnishment")==0)
		{
			payment=5000;
			if(current_player->account >= payment)
			{
				exit=0,current_player->account -=payment;
				printf("** %s paid to the bank %d$ **\n",current_player->name,payment);
			}
		}
		if(str_cmp(s,"Generosity")==0)
		{
			if(current_player->account >= 10000)
			{
				payment=10000;
				if(current_player->type == player_1->type)
				{
					player_1->account -= payment , player_ai->account += payment;
					printf("** %s paid to %s %d$ **\n",player_1->name,player_ai->name,payment);
				}
				else
				{
					player_ai->account -= payment , player_1->account += payment;
					printf("** %s paid to %s %d$ **\n",player_ai->name,player_1->name,payment);
				}
				exit=0;
			}
		}
		if(exit != 0 && deed != 0)
		{
			printf("** %s's money isn't enough to pay %d$**\n",current_player->name,payment);
			sell_property(board,current_player);
		}
		else if(exit != 0 && deed == 0)
		{
			exit=0,bankrupt=1;
			printf("** %s went bankrupt **\n",current_player->name);
		}
	}
	return bankrupt;
}
int block_fortune(struct block *board,struct player *current_player,struct player *player_1,struct player *player_ai)
{
	int i,exit=1,flag=1,dice,deed=0,choice,bankrupt=0;
	struct fortune_card *card_head=NULL;
	init_the_fortunecard(&card_head,1,"Free house"		);
	init_the_fortunecard(&card_head,2,"Time Travel"		);
	init_the_fortunecard(&card_head,3,"Garnishment"		);
	init_the_fortunecard(&card_head,4,"Generosity"		);
	init_the_fortunecard(&card_head,5,"Treasure Hunter"	);
	dice=random_number(1,5);
	switch(dice)
	{
		case 1:
			printf("** Fortune Card : %s **\n",fortune_card_set_index(card_head,0)->card_name);
			printf("** Build a house on one of your properties for free **\n");
			for(i=0;i<=23;i++)
				if(block_set_index(board,i)->owner.type == current_player->type && block_set_index(board,i)->house_count < 3)
					deed++;
			if(current_player->type == player_1->type && deed != 0)
			{
				while(exit)
				{
					show_player_properties(board,current_player);
					choice=get_int("Choice : ","Invalid choice! Try again : ",1,23);
					if(block_set_index(board,choice)->owner.type == current_player->type && block_set_index(board,choice)->house_count < 3)
					{
						block_set_index(board,choice)->house_count += 1;
						printf("** A house was contructed to %s **\n",block_set_index(board,choice)->name);
						exit=0;
					}
				}
			}
			else if(current_player->type == player_ai->type && deed != 0)
			{
				for(i=23;i>=0&&flag;i--)
					if(block_set_index(board,i)->owner.type == current_player->type && block_set_index(board,i)->house_count<3)
					{
						printf("** %s constructed a house to %s **\n",current_player->name,block_set_index(board,i)->name);
						block_set_index(board,i)->house_count += 1;
						flag=0;
					}
			}
			else if(deed == 0)
				printf("** You don't have any properties which you can construct a house **\n");
			break;
		case 2:
			printf("** Fortune Card : %s **\n",fortune_card_set_index(card_head,1)->card_name);
			dice=random_number(1,6);
			if(dice>=1 && dice<=3)
			{
				printf("** Move forward by 2 blocks **\n");
				current_player->current_block_id += 2;
			}
			else
			{
				printf("** Move backward by 2 blocks **\n");
				current_player->current_block_id -= 2;
			}
			break;
		case 3:
			printf("** Fortune Card : %s **\n",fortune_card_set_index(card_head,2)->card_name);
			bankrupt=make_payment(board,current_player,player_1,player_ai,"Garnishment");
			break;
		case 4:
			printf("** Fortune Card : %s **\n",fortune_card_set_index(card_head,3)->card_name);
			bankrupt=make_payment(board,current_player,player_1,player_ai,"Generosity");
			break;
		case 5:
			printf("** Fortune Card : %s **\n",fortune_card_set_index(card_head,4)->card_name);
			printf("** %s took %d$ from the bank **\n",current_player->name,20000);
			current_player->account += 20000;
			break;
	}
	free(card_head);
	return bankrupt;
}
void init_the_board(struct block **root)
{
	add_ll(root , 0 ,"Start"		,    0 ,   0 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,start 		);
	add_ll(root , 1 ,"Esenyurt"		,16000 , 800 , 4000 , 9000 ,25000 ,10000 ,0 ,noone ,property	);
	add_ll(root , 2 ,"Car Park"		,    0 ,1500 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,tax			);
	add_ll(root , 3 ,"Fortune Card"	,    0 ,   0 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,fortune		);
	add_ll(root , 4 ,"Tuzla"		,16500 , 850 , 4250 , 9500 ,26000 ,12000 ,0 ,noone ,property	);
	add_ll(root , 5 ,"Arnavutkoy"	,17000 , 875 , 4500 ,10000 ,28000 ,12000 ,0 ,noone ,property	);
	add_ll(root , 6 ,"Wait 2 Turn"	,    0 ,   2 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,punish		);
	add_ll(root , 7 ,"Catalca"		,20000 ,1000 , 5000 ,12000 ,30000 ,13000 ,0 ,noone ,property	);
	add_ll(root , 8 ,"Beykoz"		,23000 ,1100 , 5500 ,12500 ,33000 ,13000 ,0 ,noone ,property	);
	add_ll(root , 9 ,"Fortune Card"	,    0 ,   0 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,fortune		);
	add_ll(root ,10 ,"Car Fix"		,    0 ,1750 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,tax			);
	add_ll(root ,11 ,"Maltepe"		,30000 ,1350 , 7000 ,15000 ,40000 ,15000 ,0 ,noone ,property	);
	add_ll(root ,12 ,"Bills"		,    0 ,2250 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,tax			);
	add_ll(root ,13 ,"Sisli"		,33000 ,1500 , 8000 ,16000 ,42000 ,16000 ,0 ,noone ,property	);
	add_ll(root ,14 ,"Oil"			,    0 ,2250 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,tax			);
	add_ll(root ,10 ,"Fortune Card"	,    0 ,   0 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,fortune		);
	add_ll(root ,16 ,"Atasehir"		,35000 ,1600 , 8500 ,17000 ,45000 ,17000 ,0 ,noone ,property	);
	add_ll(root ,17 ,"Sariyer"		,40000 ,1750 , 9500 ,19000 ,48000 ,19000 ,0 ,noone ,property	);
	add_ll(root ,18 ,"Wait 1 Turn"	,    0 ,   1 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,punish		);
	add_ll(root ,19 ,"Kadikoy"		,43000 ,1900 ,11000 ,21500 ,55000 ,23000 ,0 ,noone ,property	);
	add_ll(root ,20 ,"Besiktas"		,60000 ,2500 ,15000 ,28000 ,60000 ,30000 ,0 ,noone ,property	);
	add_ll(root ,21 ,"Fortune Card"	,    0 ,   0 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,fortune		);
	add_ll(root ,22 ,"Vocation"		,    0 ,5000 ,    0 ,    0 ,    0 ,    0 ,0 ,noone ,tax			);
	add_ll(root ,23 ,"Bebek"		,70000 ,3500 ,20000 ,35500 ,65000 ,35000 ,0 ,noone ,property	);
}
void add_ll(struct block **root,int id,char *s,int price,int r,int r1,int r2,int r3,int hp,int hc,player_type p,block_type t)
{
	struct block *temp=(struct block*)malloc(sizeof(struct block));
	struct block *iter;
	temp->block_id=id;
	temp->name=s;
	temp->price=price;
	temp->rent=r;
	temp->rent_1=r1;
	temp->rent_2=r2;
	temp->rent_3=r3;
	temp->house_price=hp;
	temp->house_count=hc;
	temp->owner.type=p;
	temp->type=t;
	temp->next=NULL;
	if(*root==NULL)
		*root=temp;
	else
	{
		iter=*root;
		while(iter->next!=NULL)
			iter=iter->next;
		iter->next=temp;
	}
}
void init_the_fortunecard(struct fortune_card **root,int no,char *s)
{
	struct fortune_card *temp=(struct fortune_card*)malloc(sizeof(struct fortune_card));
	struct fortune_card *iter;
	temp->card_no=no;
	temp->card_name=s;
	temp->next=NULL;
	if(*root==NULL)
		*root=temp;
	else
	{
		iter=*root;
		while(iter->next!=NULL)
			iter=iter->next;
		iter->next=temp;
	}
}
void show_board(struct block *board,struct player player_1,struct player player_ai)
{
	int i,j,k,index,p1,p2;
	p1=player_1.current_block_id;
	p2=player_ai.current_block_id;
	for(i=0;i<7;i++)
	{
		if(i>=2&&i<=5)
		{
			for(j=0;j<25;j++)
				printf("-");
			printf("%119s","");
			for(j=0;j<25;j++)
				printf("-");
		}
		else
			for(j=0;j<169;j++)
				printf("-");
		printf("\n");
		for(j=0;j<3;j++)
		{
			for(k=0;k<7;k++)
			{
				if((i>=1&&i<=5)&&(k>=1&&k<=5))
					if(k==1)
						printf("%-24s","|");
					else
						printf("%24s","");
				else
				{
					printf("|");
					if(i<=k)	index=i+k;
					else	index=24-i-k;
					if(j==0)
						printf("%7s%-16s","",block_set_index(board,index)->name);
					else if(j==1&&block_set_index(board,index)->type==property)
						printf("%7s%-5d%-11s","",block_set_index(board,index)->price,"$");	
					else if(j==1&&block_set_index(board,index)->type==tax)
						printf("%7s%-4d%-12s","",block_set_index(board,index)->rent,"$");
					else if(j==2&&p1==p2&&p1==index)
						printf("%7s%-9s%7s","","Cap,Car","");
					else if(j==2&&p1==index)
						printf("%7s%-16s","","Car");
					else if(j==2&&p2==index)
						printf("%7s%-16s","","Cap");			
					else
						printf("%23s","");
				}
			}
			printf("|\n");
		}
	}
	for(j=0;j<169;j++)
		printf("-");
	printf("\n");
	printf("Player 1's money  : %d $\n",player_1.account);
	printf("Player AI's money : %d $\n",player_ai.account);
}
struct player *turn_player_or_ai(struct player *current_player,struct player *player_1,struct player *player_ai)
{
	if(current_player->type == player_1->type)
	{
		if(player_ai->turn_to_wait == 0)	// If other player's waiting time is 0, the tour will pass that player.
			current_player=player_ai;
		else if(player_1->turn_to_wait != 0)   // if player_1 and palyer_ai are waiting
		{
			if(player_1->turn_to_wait > player_ai->turn_to_wait)	// If player_1's waiting time is greater than player_ai's waiting time
			{														// For example, player_1's waiting time is 2, player_ai's waiting time is 1
				player_1->turn_to_wait -= player_ai->turn_to_wait;	// player_1's waiting time will be 2-1=1, player_ai's waiting time will be 0
				player_ai->turn_to_wait = 0;
				current_player = player_ai;
			}
			else													// If player_ai's waiting time is greater than player_1's waiting time
			{														// For example, player_ai's waiting time is 2,player_1's waiting time is 1
				player_ai->turn_to_wait -= player_1->turn_to_wait;	// player_ai's waiting time will be 2-1=1, player_1's waiting time will be 0;
				player_1->turn_to_wait = 0;
			}
		}
		else	// If other player's waiting time is not 0, that player's waiting time will decrease 1 and the tour will not change.
			player_ai->turn_to_wait--;
	}
	else
	{
		if(player_1->turn_to_wait == 0)	// If other player's waiting time is 0, the tour will pass that player.
			current_player = player_1;
		else if(player_ai->turn_to_wait != 0)
		{
			if(player_1->turn_to_wait > player_ai->turn_to_wait)
			{
				player_1->turn_to_wait -= player_ai->turn_to_wait;
				player_ai->turn_to_wait = 0;
			}
			else
			{
				player_ai->turn_to_wait -= player_1->turn_to_wait;
				player_1->turn_to_wait = 0;
				current_player = player_1;
			}
		}
		else		// If other player's waiting time is not 0, that player's waiting time will decrease 1 and the tour will not change.
			player_1->turn_to_wait--;
	}
	return current_player;	// All these process, this function will return current_player
}
struct block *block_set_index(struct block *ll,int index)
{
	int i=0;
	for(i=0;i<index;i++)
		ll=ll->next;
	return ll;
}
struct fortune_card *fortune_card_set_index(struct fortune_card *ll,int index)
{
	int i=0;
	for(i=0;i<index;i++)
		ll=ll->next;
	return ll;
}
void free_block(struct block *ll)
{
	if(ll->next!=NULL)
		free_block(ll->next);
	free(ll);
}
void free_fortunecard(struct fortune_card *ll)
{
	if(ll->next!=NULL)
		free_fortunecard(ll->next);
	free(ll);
}
int average_properties(struct block *board)
{
	int average=0;
	while(board!=NULL)
	{
		average += board->price;
		board = board->next;
	}
	return average/12;
}
int random_number(int lower_bound,int upper_bound)
{
	int r;
	r=rand()%(upper_bound-lower_bound+1)+lower_bound;	// [lower_bound,upper_bound]
	return r;
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
int str_cmp(char *s1,char *s2)
{
	while(*s1&&*s2&&*s1==*s2)
		s1++,s2++;
	return *s1-*s2;
}