#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef enum{UP='U',DOWN='D',LEFT='L',RIGHT='R',INTELLIGENT='I',SHUFFLE='S',EXIT='Q',NONE='.'}Event;
typedef enum{QUIT,UNSOLVED,SOLVED}State;

typedef struct
{
	int *cur_puzzle;	// current puzzle
	int *goal_puzzle;
	int size;
	int blank_x,blank_y;
	int totalNumberOfMoves;
	State state;
	int prev_event;
}Puzzle;

Puzzle Create_Puzzle();	// Create puzzle.
int Get_Size(int lower, int upper);	// Get size from user.
void Init_Random_Puzzle(Puzzle *puzzle);	// Create random puzzle.
void Init_Goal_Puzzle(Puzzle *puzzle);	// Create goal puzzle.
bool Is_Solvable(Puzzle *puzzle);	// Check whether the puzzle is solvable or not.
bool Is_Solved(Puzzle *puzzle);		// Check whether the puzzle is solved.
void Print_Puzzle(Puzzle *puzzle);	// Print the puzzle.
void Get_Event(Puzzle *puzzle);		// Get event from user to move the blank.
void Do_Event(Puzzle *puzzle, char state);	// Move according to the event.
void Move_Intelligent(Puzzle *puzzle);	// Move intelligent.
int Manhattan_Distance(Puzzle *puzzle, char state);		// Calculate the distance of the current puzzle to the goal puzzle.
void Shuffle_Puzzle(Puzzle *puzzle);	// Shuffle puzzle
void Delete_All(Puzzle *puzzle);	// Delete memory allocation

int main()
{
	Puzzle puzzle = Create_Puzzle();	// Create a puzzle

	cout << "Your initial random board is\n";
	Print_Puzzle(&puzzle);

	while(puzzle.state != QUIT)
	{
		Get_Event(&puzzle);
		Print_Puzzle(&puzzle);

		if(puzzle.state != QUIT)
			Is_Solved(&puzzle);

		if(puzzle.state == QUIT)
			cout << "Problem couldn't be solved!\nTotal number of moves : " << puzzle.totalNumberOfMoves << endl;
		if(puzzle.state == SOLVED)
		{
			cout << "Problem Solved!\nTotal number of moves : " << puzzle.totalNumberOfMoves << endl;
			puzzle.state = QUIT;
		}
	}

	Delete_All(&puzzle);
	return 0;
}

Puzzle Create_Puzzle()
{
	Puzzle puzz = {NULL,NULL,0,0,0,0,UNSOLVED,-1};

	srand(time(NULL));

	puzz.size = Get_Size(3,9);
	Init_Goal_Puzzle(&puzz);
	Init_Random_Puzzle(&puzz);

	for(int i=0 ; i < puzz.size * puzz.size ; ++i)	// Find my blank's x and y coordinate in current puzzle
		if(puzz.cur_puzzle[i] == 0)
			puzz.blank_x = i % puzz.size , puzz.blank_y = i / puzz.size;

	return puzz;
}

int Get_Size(int lower, int upper)
{
	int num=0;

	do
	{
		cout << "Please enter the problem size : ";
		cin >> num;
		if(num < lower || num > upper)
			cout << "Inlavid size! Please enter [" << lower << "," << upper << "]\n";
	}while(num < lower || num > upper);

	return num;
}

void Init_Random_Puzzle(Puzzle *puzzle)
{
	int *nums = NULL;
	int i=0,r=0,selected=0;

	puzzle->cur_puzzle = (int*)malloc(sizeof(int) * (puzzle->size * puzzle->size));	// Allocate enough space
	nums = (int*)malloc(sizeof(int) * (puzzle->size * puzzle->size));	// This array keep number which is eligible

	do
	{
		selected = 0;
		for(i=0 ; i < puzzle->size * puzzle->size ; ++i)	// Fill the array with numbers
			nums[i] = i;

		for(i=0 ; i < puzzle->size * puzzle->size ; ++i)	// Fill the current puzzle with numbers
		{
			r = rand()%(puzzle->size * puzzle->size - selected);	// Get random number
			puzzle->cur_puzzle[i] = nums[r];	// Place random number to current puzzle
			nums[r] = nums[puzzle->size * puzzle->size - selected -1];	// Remove selected number from my nums array
			selected++;	// This integer holds the number of selected numbers. In this way, the selected number can not be selected again
		}

	}while(Is_Solvable(puzzle) == false || Is_Solved(puzzle) == true);	// If created puzzle is unsolvable or same as my goal puzzle, create puzzle again

	free(nums);	// Deallocate memory
}

void Init_Goal_Puzzle(Puzzle *puzzle)
{
	puzzle->goal_puzzle = (int*)malloc(sizeof(int) * (puzzle->size * puzzle->size));	// Allocate enough space

	for(int i=0 ; i< puzzle->size * puzzle->size ; ++i)	// Fill the goal puzzle in order
		puzzle->goal_puzzle[i] = i+1;

	puzzle->goal_puzzle[puzzle->size * puzzle->size -1] = 0;	// Place the last element as 0
}

bool Is_Solvable(Puzzle *puzzle)
{
	int i=0,j=0,inverse=0,blankrow=0;

	// Solvability Rule
	// If my puzzle's edge is odd and number of inverse is even
	// If my puzzle's edge is even,number of inverse is odd and blankrow is even
	// If my puzzle's edge is even,number of inverse is even and blankrow is odd

	for(i=0 ; i < puzzle->size * puzzle->size ; ++i)	// This loop find inverse number,blankrow
	{
		if(puzzle->cur_puzzle[i] == 0)
		{
			blankrow = i/puzzle->size;
			continue;
		}
		for(j=i+1 ; j < puzzle->size * puzzle->size ; ++j)	// Compare current puzzle with goal puzzle
			if(puzzle->cur_puzzle[j] && puzzle->cur_puzzle[i] > puzzle->cur_puzzle[j])
				inverse++;
	}

	blankrow = puzzle->size - blankrow;

	if((puzzle->size%2 == 1 && inverse%2 == 0) || (puzzle->size%2 == 0 && blankrow%2 == 0 && inverse%2 == 1) || (puzzle->size%2 == 0 && blankrow%2 == 1 && inverse%2 == 0))
		return true;
	else
		return false;
}

bool Is_Solved(Puzzle *puzzle)
{
	int relation=0;

	for(int i=0 ; i < puzzle->size * puzzle->size ; ++i)	// This loop find relation between current puzzle and goal puzzle
		if(puzzle->goal_puzzle[i] == puzzle->cur_puzzle[i])
			relation++;

	if(relation == puzzle->size * puzzle->size)	// If relation number is same size*size
	{
		puzzle->state = SOLVED;
		return true;
	}
	else
	{
		puzzle->state = UNSOLVED;
		return false;
	}
}

void Print_Puzzle(Puzzle *puzzle)
{
	for(int i=0 ; i < puzzle->size ; ++i)
	{
		for(int j=0 ; j < puzzle->size ; ++j)
		{
			if(puzzle->cur_puzzle[puzzle->size*i + j] == 0)
				cout << "\t";
			else
				cout << puzzle->cur_puzzle[puzzle->size*i + j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void Get_Event(Puzzle *puzzle)
{
	char event = 0;

	cout << "Your move: ";
	cin >> event;

	switch(event)
	{
		case EXIT:
			puzzle->state = QUIT;
			break;
		case SHUFFLE:
			Shuffle_Puzzle(puzzle);
			break;
		case INTELLIGENT:
			puzzle->totalNumberOfMoves++;
			Move_Intelligent(puzzle);
			break;
		case UP:
			if(puzzle->blank_y > 0)
			{
				puzzle->totalNumberOfMoves++;
				Do_Event(puzzle,UP);
			}
			else
				cout << "Invalid movement!\nCan't move up!\n";
			break;
		case DOWN:
			if(puzzle->blank_y < puzzle->size - 1)
			{
				puzzle->totalNumberOfMoves++;
				Do_Event(puzzle,DOWN);
			}
			else
				cout << "Invalid movement!\nCan't move down!\n";
			break;
		case LEFT:
			if(puzzle->blank_x > 0)
			{
				puzzle->totalNumberOfMoves++;
				Do_Event(puzzle,LEFT);
			}
			else
				cout << "Invalid movement!\nCan't move left!\n";
			break;
		case RIGHT:
			if(puzzle->blank_x < puzzle->size - 1)
			{
				puzzle->totalNumberOfMoves++;
				Do_Event(puzzle,RIGHT);
			}
			else
				cout << "Invalid movement!\nCan't move right!\n";
			break;
		default:
			cout << "Couldn't find movement like " << event << endl << endl;
			break;
	}
}

void Do_Event(Puzzle *puzzle, char state)
{
	int temp=0,dest_x=0,dest_y=0;

	if(state == UP)
		dest_x = puzzle->blank_x , dest_y = puzzle->blank_y-1;
	else if(state == DOWN)
		dest_x = puzzle->blank_x , dest_y = puzzle->blank_y+1;
	else if(state == LEFT)
		dest_x = puzzle->blank_x-1 , dest_y = puzzle->blank_y;
	else if(state == RIGHT)
		dest_x = puzzle->blank_x+1 , dest_y = puzzle->blank_y;
	else
		dest_x = puzzle->blank_x, dest_y = puzzle->blank_y;

	temp = puzzle->cur_puzzle[puzzle->size*puzzle->blank_y + puzzle->blank_x];		// Change current blank with destination blank
	puzzle->cur_puzzle[puzzle->size*puzzle->blank_y + puzzle->blank_x] = puzzle->cur_puzzle[puzzle->size*dest_y + dest_x];
	puzzle->cur_puzzle[puzzle->size*dest_y + dest_x] = temp;

	puzzle->blank_x = dest_x;
	puzzle->blank_y = dest_y;
}

void Move_Intelligent(Puzzle *puzzle)
{
	int i=0,shortest_path=0,index=0;
	int ways[4]={0}; // 0-LEFT,1-RIGHT,2-UP,3-DOWN

	if(puzzle->blank_x > 0) // Look left. If blank can move left, calculate manhattan distance. Else place index -1.
		ways[0] = Manhattan_Distance(puzzle,LEFT);
	else
		ways[0] = -1;

	if(puzzle->blank_x < puzzle->size - 1) // Look right. If blank can move right, calculate manhattan distance. Else place index -1.
		ways[1] = Manhattan_Distance(puzzle,RIGHT);
	else
		ways[1] = -1;

	if(puzzle->blank_y > 0) // Look up. If blank can move up, calculate manhattan distance. Else place index -1.
		ways[2] = Manhattan_Distance(puzzle,UP);
	else
		ways[2] = -1;

	if(puzzle->blank_y < puzzle->size - 1) // Look down. If blank can move down, calculate manhattan distance. Else place index -1.
		ways[3] = Manhattan_Distance(puzzle,DOWN);
	else
		ways[3] = -1;

	if(puzzle->prev_event == 0)			// Previous movement control statement
		puzzle->prev_event = 1;
	else if(puzzle->prev_event == 1)
		puzzle->prev_event = 0;
	else if(puzzle->prev_event == 2)
		puzzle->prev_event = 3;
	else if(puzzle->prev_event == 3)
		puzzle->prev_event = 2;

	if(puzzle->prev_event != -1)	// Do not move reverse of the previous move
		ways[puzzle->prev_event] = -1;	

	for(i=3 ; i >= 0 ; --i)		// Set the initial value for shortest path
		if(ways[i] != -1)
		{
			shortest_path = ways[i];
			index = i;
		}

	for(i=3 ; i >= 0 ; --i)	// find the actually shortest path
		if(ways[i] != -1 && ways[i] < shortest_path)
		{
			shortest_path = ways[i];
			index = i;
		}

	for(i=3 ; i >= 0 ; --i)		// Set -1 if ways[i] is not equal shortest path
		if(ways[i] != shortest_path)
			ways[i] = -1;

	do // seletect on of shorthest path if there are some shortest path
	{
		index = rand() % 4; // for a way
	}while(ways[index] == -1);

	puzzle->prev_event = index;

	if(index == 0)
		Do_Event(puzzle,LEFT);
	else if(index == 1)
		Do_Event(puzzle,RIGHT);
	else if(index == 2)
		Do_Event(puzzle,UP);
	else if(index == 3)
		Do_Event(puzzle,DOWN);	
}

int Manhattan_Distance(Puzzle *puzzle, char state)
{
	int i=0,j=0,exit=0;
	int distance=0,distance_x=0,distance_y=0;

	Do_Event(puzzle,state);

	for(i=0 ; i < puzzle->size * puzzle->size ; ++i)
	{
		if(puzzle->goal_puzzle[i] != puzzle->cur_puzzle[i])
		{
			while(exit == 0)
			{
				if(puzzle->cur_puzzle[j] != puzzle->goal_puzzle[i])
					++j;
				else
					exit = 1;
			}
			distance_x = i/puzzle->size - j/puzzle->size;
			distance_y = i%puzzle->size - j%puzzle->size;

			if(distance_x < 0)
				distance_x *= -1;
			if(distance_y < 0)
				distance_y *= -1;

			distance += distance_x;
			distance += distance_y;

			exit=0,j=0;
		}
	}

	if(state == UP)
		Do_Event(puzzle,DOWN);
	else if(state == DOWN)
		Do_Event(puzzle,UP);
	else if(state == LEFT)
		Do_Event(puzzle,RIGHT);
	else if(state == RIGHT)
		Do_Event(puzzle,LEFT);

	return distance;
}

void Shuffle_Puzzle(Puzzle *puzzle)
{
	char ways[4];
	int i=0,j=0,r=0,size=0;

	for(i=0 ; i < puzzle->size * puzzle->size ; ++i)	// Take the current puzzle to goal puzzle
		puzzle->cur_puzzle[i] = puzzle->goal_puzzle[i];

	for(i=0 ; i < puzzle->size * puzzle->size ; ++i)	// Find the blank's position
		if(puzzle->cur_puzzle[i] == 0)
			puzzle->blank_x = i % puzzle->size , puzzle->blank_y = i / puzzle->size;

	for(i=0 ; i < puzzle->size * puzzle->size ; ++i)
	{
		size = 0;	// Reset the value
		for(j=0 ; j<4 ; j++)	// Reset the ways array
			ways[4] = 0;

		if(puzzle->blank_x > 0)					ways[size] = LEFT , size++;		// if movement is possible
		if(puzzle->blank_x < puzzle->size - 1)	ways[size] = RIGHT , size++;
		if(puzzle->blank_y > 0)					ways[size] = UP , size++;
		if(puzzle->blank_y < puzzle->size - 1)	ways[size] = DOWN , size++;

		r = rand()%size;	// Select one of possible movement
		Do_Event(puzzle,ways[r]);	// Do possible movement
	}

	cout << "\nPuzzle was shuffled in " << puzzle->size * puzzle->size << " moves!\n";
}

void Delete_All(Puzzle *puzzle)
{
	free(puzzle->cur_puzzle);	// Deallocate memory
	free(puzzle->goal_puzzle);
}