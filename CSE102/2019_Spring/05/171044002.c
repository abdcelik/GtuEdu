#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define clear() printf("\033[H\033[J")	// clear the screen
#define DICT_SIZE 15
#define WORD_LEN 10
#define LINE_LEN 18

void wordPuzzle(char *dict[DICT_SIZE],int[][4]);
void generateWordMap(char[][DICT_SIZE],char*[],int[][4]);	// This function create the word map
char getRandomCharacter();									// This function create random character and return it
void printWordMap(char[][DICT_SIZE]);						// This function printf the word map
char *reverseWord(char[]);									// This function reverses the word, and return the adress
int getInput(char[],char[],int,int);						// This function get input from user
int myStringLen(char*);				 						// This function find the length of string
int myStringCmp(char*,char*);								// This function compares two strings and if it is the same, returns 0


int get_line_size(char *line) {
	char *ch_iter = line; // so as not to lose beginning of line
	int counter = 0;
	// go until you see new line or null char
	while(*ch_iter != '\n' && *ch_iter != '\0') {
		ch_iter++; // next char
		counter++; // increment counter
	}
	return counter;
}

void copy_string(char *source, char *destination) {
	// get iterators over original pointers
	char *src_iter = source;
	char *dst_iter = destination;
	// until null char
	while (*src_iter != '\0') {
		// copy pointers
		*dst_iter = *src_iter;
		// advance to next char
		src_iter++;
		dst_iter++;
   }
   // terminate string
   *dst_iter = '\0';
}

void remove_newline(char *line) {
	char *ch_iter = line;
	// go until you see new line
	while(*ch_iter != '\n'&&*ch_iter!='\r') {
		ch_iter++; // next char
	}
	*ch_iter = '\0'; // overwrite new line
}

void print_dictionary(char *dict[]) {
	int i;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		printf("%s\n", dict[i]);
	}
}

void print_coord(int coord[DICT_SIZE][4]) {
	int i, j;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		for(j = 0 ; j < 4 ; j++) {
			printf("%d ", coord[i][j]);
		}
		printf("\n");
	}
}

int main(){
	char *dict[DICT_SIZE];
    int coord[DICT_SIZE][4];    
    char line[LINE_LEN];

    srand(time(NULL));
	FILE *fp = fopen("word_hunter.dat", "r");
	int line_counter = 0;
	int dict_counter = 0;
	while(fgets(line, LINE_LEN, fp) != NULL) {
		if(line_counter%5 == 0) {
			dict[dict_counter] = (char*) malloc(sizeof(char) * get_line_size(line));
			remove_newline(line);
			copy_string(line, dict[dict_counter]);
		} else if (line_counter%5 == 1){
			coord[dict_counter][0] = atoi(line);
		} else if (line_counter%5 == 2){			
			coord[dict_counter][1] = atoi(line);		
		} else if (line_counter%5 == 3){
			coord[dict_counter][2] = atoi(line);
		} else if (line_counter%5 == 4){
			coord[dict_counter][3] = atoi(line);
			dict_counter++;
		}
		line_counter++;
	}
	fclose(fp);
	wordPuzzle(dict,coord);
	return 0;
}
void wordPuzzle(char *dict[DICT_SIZE],int coord[DICT_SIZE][4])
{
	char wordMap[DICT_SIZE][DICT_SIZE]={'\0'};
	char word[16]={'\0'},temp[16]={'\0'};
    int i,j=0,k,x=0,y=0,row,column,length,exit=1,situation=1,check=0;		// These are my variables
    int ways[8][2]={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};			// These are ways.
    int checkWord[DICT_SIZE]={0},checkGame=0;
    generateWordMap(wordMap,dict,coord);	// The map created
	while(exit)		// "exit" is flag
	{
		clear();
		printWordMap(wordMap);
		printf("\nWord : ");
		scanf(" %[^\n]s",word);
		for(i=0;i<DICT_SIZE;i++)							/* This loop checks if the word is meaningful.					*/
			if(myStringCmp(word,dict[i])==0)
			{		
				checkWord[i]=1;							/* It compares with the meaningful words						*/
				check++;
			}										/* and if the word meaningful, increases the value of count.	*/
		if(check)		// If the word meaningful
		{
			row=getInput("Row","Invalid row! Try again",0,DICT_SIZE);				// Row is taken from user.
			column=getInput("Column","Invalid column! Try again",0,DICT_SIZE);		// Column is taken from user.
			while(j!=8&&situation)			// j represent ways. There are 8 ways. The loop look 8 ways. If word is found 1. way or any way, situation will be 0 and loop is over.
			{
				length=myStringLen(word);
				x=ways[j][0],y=ways[j][1];	// First direction x=0, y=1. Loop add row+x column+y each term.
				i=0;
				while(length!=0&&row+x>=0&&row+x<DICT_SIZE&&column+y>=0&&column+y<DICT_SIZE)		// If the rows and columns are in the boundaries 
				{
					if(length==myStringLen(word))			// I manually assign first character.
						temp[i]=wordMap[row][column];
					else									// The program automatically assigns the remaining characters.
					{
						temp[i]=wordMap[row+x][column+y];
						if(x>0)				// Go my direction 
							x++;
						else if(x<0)		// Go my direction 
							x--;
						if(y>0)
							y++;
						else if(y<0)		// Go my direction 
							y--;
					}
					i++;
					length--;
				}
				for(k=0;k<i;k++)					/* This loop converts that character to a small character 	*/
					if(temp[k]>=65&&temp[k]<=90)	/* if the string has a large character.		 				*/
						temp[k]+=32;
				x=ways[j][0],y=ways[j][1];		// The direction reset
				if(myStringCmp(temp,word)==0||myStringCmp(reverseWord(temp),word)==0)	// If the string is meaningful, change its characters to uppercase.
				{
					while(length!=myStringLen(word))
					{
						if(length==0&&wordMap[row][column]>=97&&wordMap[row][column]<=122)	// If character is lowercase
							wordMap[row][column]-=32;
						else if(length!=0)
						{
							if(wordMap[row+x][column+y]>=97&&wordMap[row][column]<=122)	// If character is lowercase
								wordMap[row+x][column+y]-=32;
							if(x>0)			// Go my direction 
								x++;
							else if(x<0)	// Go my direction 
								x--;
							if(y>0)
								y++;
							else if(y<0)	// Go my direction 
								y--;
						}
						length++;
					}
					situation=0;	// Leave the loop
				}
				for(i=0;i<16;i++)	// Reset temp string
					temp[i]='\0';
				j++;				// The direction changes
			}
		}
		else if(myStringCmp(word,"exit game")==0) // The user enter "exit" to exit.
			exit=0;
		else	// The word is meaningless
			printf("** The word not found **\n");
		for(i=0;i<DICT_SIZE;i++)			// This loop checks if all words are found.
			if(checkWord[i]==1)
				checkGame++;
		if(checkGame==DICT_SIZE)		// If all words are found
		{
			printf("** All words is found **\n");
			exit=0;
		}
		check=0,j=0,situation=1,checkGame=0;	// Reset variables
	}
}
void generateWordMap(char wordMap[][DICT_SIZE],char *dict[],int coord[][4])
{
	char r='.';
	int i,j,k=0,x=0,y=0,wordLength;
	for(i=0;i<DICT_SIZE;i++)
		for(j=0;j<DICT_SIZE;j++)
		{
			r=getRandomCharacter();
			wordMap[i][j]=r;
		}
	i=0,j=0;
	while(i!=DICT_SIZE)
	{
		wordLength=myStringLen(dict[i]);
		while(wordLength!=0)
		{
			wordMap[coord[i][0]+x][coord[i][1]+y]=dict[i][0+k];
			if(coord[i][0]-coord[i][2]<0)
				x++;
			else if(coord[i][0]-coord[i][2]>0)
				x--;
			if(coord[i][1]-coord[i][3]<0)
				y++;
			else if(coord[i][1]-coord[i][3]>0)
				y--;
			wordLength--,k++;
		}
		i++,x=0,y=0,k=0;
	}
}
char getRandomCharacter()
{
	char random;
	random=rand()%26+97;	// [97,122]
	return random;
}
char *reverseWord(char str[])
{
	int i,l=myStringLen(str),l1=l;
	char temp;
	for(i=0;i<(l1+1)/2;i++)
	{
		temp=str[i];
		str[i]=str[l-1];
		str[l-1]=temp;
		l--;
	}
	return str;
}
void printWordMap(char wordMap[][DICT_SIZE])
{
	int i,j;
	for(i=0;i<6;i++)
		printf(" ");
	for(i=0;i<DICT_SIZE;i++)
		printf("%-2d ",i);
	printf("\n    ");
	for(i=0;i<3*DICT_SIZE;i++)
		printf("-");
	printf("\n");
	for(i=0;i<DICT_SIZE;i++)
	{
		printf(" %2d | ",i);
		for(j=0;j<DICT_SIZE;j++)
			printf("%c  ",wordMap[i][j]);
		printf("\n    |\n");
	}
}
int getInput(char s1[],char s2[],int lower_bound,int upper_bound)
{
	int input;
	printf("%s : ",s1);
	scanf("%d",&input);
	while(input<lower_bound||input>upper_bound)
	{
		printf("%s : ",s2);
		scanf("%d",&input);
	}
	return input;
}
int myStringLen(char *str)
{
	int length,i=0;
	while(str[i]!='\0'&&str[i]!='\r') 	// If it is not \0 and carriage return
		i++;
	return i;
}
int myStringCmp(char *str1,char *str2)
{
	while(*str1&&*str2&&*str1==*str2)	// If it is not '\0' and if they are same
		++str1,++str2;
	return *str1-*str2;
}