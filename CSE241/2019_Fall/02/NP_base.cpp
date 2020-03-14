#include "NP_base.h"

Puzzle Create_Puzzle(void)
{
	Puzzle puzzle;

	puzzle.cur_puzzle = puzzle.goal_puzzle = NULL;
	puzzle.row = puzzle.column = puzzle.blank_x = puzzle.blank_y = puzzle.totalNumberOfMoves = 0;
	puzzle.state = State::UNSOLVED;
	puzzle.prev_event = Event::NONE;
	puzzle.event_flag = 0;

	return puzzle;
}

void Check_Program_State(Puzzle& puzzle,int argc, char* argv[])
{
	switch(argc)
	{
		case 1:
			puzzle.row = puzzle.column = Get_Size(3,9);
			Init_Random_Puzzle(puzzle);
			Init_Goal_Puzzle(puzzle);
			Set_Blank_Position(puzzle);
			break;
		case 2:
			if(Load_File(puzzle,argv[1]) != 0)
				exit(1);
			break;
		default:
			cout << "Too many arguments have been passed!\n";
			exit(1);
	}
}

int Get_Size(int lower_bound, int upper_bound)
{
	int num=0;

	do
	{
		cout << "Please enter the problem size : ";
		cin >> num;
		if(num < lower_bound || num > upper_bound)
			cout << "Inlavid size! Please enter [" << lower_bound << "," << upper_bound << "]\n";
	}while(num < lower_bound || num > upper_bound);

	return num;
}

void Init_Goal_Puzzle(Puzzle& puzzle)
{
	int cur_value=1,last_index=0;

	puzzle.goal_puzzle = (int*)malloc(sizeof(int) * (puzzle.row * puzzle.column));	// Allocate enough space

	for(int i=0 ; i < puzzle.row * puzzle.column ; ++i)	// Fill the goal puzzle in order
	{
		puzzle.goal_puzzle[i] = puzzle.cur_puzzle[i];

		if(puzzle.cur_puzzle[i] != 0)
		{
			puzzle.goal_puzzle[i] = cur_value;
			last_index = i;
			++cur_value;
		}
	}
	puzzle.goal_puzzle[last_index] = -1;	// Place the last element as -1
}

void Init_Random_Puzzle(Puzzle& puzzle)
{
	int *nums = NULL;
	int i=0,r=0,selected=0;

	puzzle.cur_puzzle = (int*)malloc(sizeof(int) * puzzle.row * puzzle.column);	// Allocate enough space
	nums = (int*)malloc(sizeof(int) * puzzle.row * puzzle.column);	// This array keep number which is eligible

	do
	{
		selected = 0;
		for(i=0 ; i < puzzle.row * puzzle.column ; ++i)	// Fill the array with numbers
			nums[i] = i;
		nums[0] = -1;

		for(i=0 ; i < puzzle.row * puzzle.column ; ++i)	// Fill the current puzzle with numbers
		{
			r = rand()%(puzzle.row * puzzle.column - selected);	// Get random number
			puzzle.cur_puzzle[i] = nums[r];	// Place random number to current puzzle
			nums[r] = nums[puzzle.row * puzzle.column - selected -1];	// Remove selected number from my nums array
			selected++;	// This integer holds the number of selected numbers. In this way, the selected number can not be selected again
		}
	}while(Is_Solvable(puzzle) == false);	// If created puzzle is unsolvable, create puzzle again

	free(nums);	// Deallocate memory
}

void Set_Blank_Position(Puzzle& puzzle)
{
	for(int i=0 ; i < puzzle.row * puzzle.column ; ++i)
		if(puzzle.cur_puzzle[i] == -1)
			puzzle.blank_x = i % puzzle.column , puzzle.blank_y = i / puzzle.column;
}

bool Is_Solvable(const Puzzle& puzzle)
{
	int inverse=0,blankrow=0;

	// Solvability Rule
	// If my puzzle's edge is odd and number of inverse is even
	// If my puzzle's edge is even,number of inverse is odd and blankrow is even
	// If my puzzle's edge is even,number of inverse is even and blankrow is odd

	for(int i=0 ; i < puzzle.row * puzzle.column ; ++i)	// This loop find inverse number,blankrow
	{
		if(puzzle.cur_puzzle[i] == -1)
		{
			blankrow = i/puzzle.row;
			continue;
		}
		for(int j=i+1 ; j < puzzle.row * puzzle.column ; ++j)	// Compare current puzzle with goal puzzle
			if(puzzle.cur_puzzle[j] != -1 && puzzle.cur_puzzle[i] > puzzle.cur_puzzle[j])
				inverse++;
	}

	blankrow = puzzle.row - blankrow;

	if(((puzzle.row * puzzle.column)%2 == 1 && inverse%2 == 0) ||
	   ((puzzle.row * puzzle.column)%2 == 0 && inverse%2 == 1 && blankrow%2 == 0) ||
	   ((puzzle.row * puzzle.column)%2 == 0 && inverse%2 == 0 && blankrow%2 == 1))
		return true;
	else
		return false;
}

bool Is_Solved(const Puzzle& puzzle)
{
	int relation=0;

	for(int i=0 ; i < puzzle.row * puzzle.column ; ++i)	// This loop find relation between current puzzle and goal puzzle
		if(puzzle.goal_puzzle[i] == puzzle.cur_puzzle[i])
			relation++;

	if(relation == puzzle.row * puzzle.column)	// If relation number is same size*size
		return true;
	else
		return false;
}

void Print_Puzzle(const Puzzle& puzzle)
{
	for(int i=0 ; i < puzzle.row ; ++i)
	{
		for(int j=0 ; j < puzzle.column ; ++j)
		{
			cout << "\t";
			switch(puzzle.cur_puzzle[puzzle.column*i + j])
			{
				case 0	: cout << "X";	break;
				case -1	: cout << " ";	break;
				default	: cout << puzzle.cur_puzzle[puzzle.column*i + j]; break;
			}
		}
		cout << endl;
	}
}

void Get_Event(Puzzle& puzzle)
{
	char event = 0;

	cout << "Your move: ";
	cin >> event;

	switch(event)
	{
		case 'Q': puzzle.state = State::QUIT; break;
		case 'S': Shuffle_Puzzle(puzzle); break;
		case 'I': Move_Intelligent(puzzle); puzzle.totalNumberOfMoves++; break;
		case 'V': Solve_Puzzle(puzzle); break;
		case 'T': Print_Report(puzzle); break;
		case 'E': Export_File(puzzle); break;
		case 'Y':
			char buffer[32];
			cout << "File name : ";
			cin >> buffer;
			Load_File(puzzle,buffer);
			break;
		case 'U':
			if(Can_Move(puzzle,Event::UP))
			{
				puzzle.totalNumberOfMoves++;
				Do_Event(puzzle,Event::UP);
			}
			else
				cout << "Invalid movement!\nCan't move up!\n";
			break;
		case 'D':
			if(Can_Move(puzzle,Event::DOWN))
			{
				puzzle.totalNumberOfMoves++;
				Do_Event(puzzle,Event::DOWN);
			}
			else
				cout << "Invalid movement!\nCan't move down!\n";
			break;
		case 'L':
			if(Can_Move(puzzle,Event::LEFT))
			{
				puzzle.totalNumberOfMoves++;
				Do_Event(puzzle,Event::LEFT);
			}
			else
				cout << "Invalid movement!\nCan't move left!\n";
			break;
		case 'R':
			if(Can_Move(puzzle,Event::RIGHT))
			{
				puzzle.totalNumberOfMoves++;
				Do_Event(puzzle,Event::RIGHT);
			}
			else
				cout << "Invalid movement!\nCan't move right!\n";
			break;
		default:
			cout << "Couldn't find movement like " << event << endl << endl;
			break;
	}
}

bool Can_Move(const Puzzle& puzzle, Event event)
{
	if(	(event == Event::UP		&& puzzle.blank_y > 0 					&& puzzle.cur_puzzle[puzzle.column * (puzzle.blank_y-1) + puzzle.blank_x] 	!= 0) ||
		(event == Event::DOWN	&& puzzle.blank_y < puzzle.row-1		&& puzzle.cur_puzzle[puzzle.column * (puzzle.blank_y+1) + puzzle.blank_x] 	!= 0) ||
		(event == Event::LEFT	&& puzzle.blank_x > 0					&& puzzle.cur_puzzle[puzzle.column * puzzle.blank_y + puzzle.blank_x-1] 	!= 0) ||
		(event == Event::RIGHT	&& puzzle.blank_x < puzzle.column-1 	&& puzzle.cur_puzzle[puzzle.column * puzzle.blank_y + puzzle.blank_x+1] 	!= 0) )
		return true;
	else
		return false;
}

void Do_Event(Puzzle& puzzle, Event event)
{
	int temp=0,dest_x=0,dest_y=0;

	if(event == Event::UP)
		dest_x = puzzle.blank_x , dest_y = puzzle.blank_y-1;
	else if(event == Event::DOWN)
		dest_x = puzzle.blank_x , dest_y = puzzle.blank_y+1;
	else if(event == Event::LEFT)
		dest_x = puzzle.blank_x-1 , dest_y = puzzle.blank_y;
	else if(event == Event::RIGHT)
		dest_x = puzzle.blank_x+1 , dest_y = puzzle.blank_y;
	else
		dest_x = puzzle.blank_x, dest_y = puzzle.blank_y;

	temp = puzzle.cur_puzzle[puzzle.column*puzzle.blank_y + puzzle.blank_x];		// Change current blank with destination blank
	puzzle.cur_puzzle[puzzle.column*puzzle.blank_y + puzzle.blank_x] = puzzle.cur_puzzle[puzzle.column*dest_y + dest_x];
	puzzle.cur_puzzle[puzzle.column*dest_y + dest_x] = temp;

	puzzle.blank_x = dest_x;
	puzzle.blank_y = dest_y;
}

void Move_Intelligent(Puzzle& puzzle)
{
	int i=0,shortest_path=0,index=0;
	Event events[4] = {Event::UP,Event::DOWN,Event::LEFT,Event::RIGHT};
	int ways[4]={-1,-1,-1,-1}; // 0-UP,1-DOWN,2-LEFT,3-RIGHT

	for(i=0 ; i<4 ; ++i)
		if(Can_Move(puzzle,events[i]))
			ways[i] = Manhattan_Distance(puzzle,events[i]);

	Check_Prev_Event(puzzle);

	if(puzzle.event_flag != 0)
		--puzzle.event_flag;
	else
	{
		for(i=0 ; i<4 ; ++i)	// Set the initial value for shortest path
			if(ways[i] != -1)
			{
				shortest_path = ways[i];
				index = i;
			}

		for(i=0 ; i<4 ; ++i)	// find the actually shortest path
			if(ways[i] != -1 && ways[i] < shortest_path)
			{
				shortest_path = ways[i];
				index = i;
			}

		for(i=0 ; i<4 ; ++i)	// Set -1 if ways[i] is not equal shortest path
			if(ways[i] != shortest_path)
				ways[i] = -1;
	}

	do // seletect on of shorthest path if there are some shortest path
	{
		index = rand() % 4; // for a way
	}while(ways[index] == -1);

	if(puzzle.event_flag == 0 && puzzle.prev_event == events[index])
		puzzle.event_flag = 2;

	puzzle.prev_event = events[index];

	Do_Event(puzzle,events[index]);	
}

void Check_Prev_Event(Puzzle& puzzle)
{
	switch(puzzle.prev_event)
	{
		case Event::UP:		puzzle.prev_event = Event::DOWN ; break;
		case Event::DOWN:	puzzle.prev_event = Event::UP ; break;
		case Event::LEFT:	puzzle.prev_event = Event::RIGHT ; break;
		case Event::RIGHT:	puzzle.prev_event = Event::LEFT ; break;
		default: break;
	}
}

int Manhattan_Distance(Puzzle& puzzle, Event event)
{
	int index=0,exit=0;
	int distance=0,distance_x=0,distance_y=0;

	Do_Event(puzzle,event);

	for(int i=0 ; i < puzzle.row * puzzle.column ; ++i)
	{
		if(puzzle.goal_puzzle[i] != puzzle.cur_puzzle[i])
		{
			while(exit == 0)
			{
				if(puzzle.cur_puzzle[index] != puzzle.goal_puzzle[i])
					++index;
				else
					exit = 1;
			}
			distance_x = i/puzzle.column - index/puzzle.column;
			distance_y = i%puzzle.row - index%puzzle.row;

			if(distance_x < 0)
				distance_x *= -1;
			if(distance_y < 0)
				distance_y *= -1;

			distance += distance_x;
			distance += distance_y;

			exit=0,index=0;
		}
	}

	if(event == Event::UP)			Do_Event(puzzle,Event::DOWN);
	else if(event == Event::DOWN)	Do_Event(puzzle,Event::UP);
	else if(event == Event::LEFT)	Do_Event(puzzle,Event::RIGHT);
	else if(event == Event::RIGHT)	Do_Event(puzzle,Event::LEFT);

	return distance;
}

void Shuffle_Puzzle(Puzzle& puzzle)
{
	Event events[4];
	int r=0,size=0;

	for(int i=0 ; i < puzzle.row * puzzle.column ; ++i)	// Take the current puzzle to goal puzzle
		puzzle.cur_puzzle[i] = puzzle.goal_puzzle[i];

	Set_Blank_Position(puzzle);

	for(int i=0 ; i < puzzle.row * puzzle.column ; ++i)
	{
		size = 0;	// Reset the value
		for(int j=0 ; j<4 ; j++)	// Reset the ways array
			events[4] = Event::NONE;

		if(Can_Move(puzzle,Event::UP))		events[size] = Event::UP , size++;	// if movement is possible
		if(Can_Move(puzzle,Event::DOWN))	events[size] = Event::DOWN , size++;
		if(Can_Move(puzzle,Event::LEFT))	events[size] = Event::LEFT , size++;
		if(Can_Move(puzzle,Event::RIGHT))	events[size] = Event::RIGHT , size++;

		r = rand()%size;	// Select one of possible movement
		Do_Event(puzzle,events[r]);	// Do possible movement
	}

	cout << "\nPuzzle was shuffled in " << puzzle.row * puzzle.column << " moves!\n";
}

void Solve_Puzzle(Puzzle& puzzle)
{
	for(int i=0 ; i<100000 && Is_Solved(puzzle) == false ; ++i,++puzzle.totalNumberOfMoves)
	{
		Move_Intelligent(puzzle);
		Print_Puzzle(puzzle);
		cout << endl << endl;
	}

	if(Is_Solved(puzzle) == false)
		cout << "\n 100000 moves were made but the puzzle could not be solved.\n\n";
}

void Print_Report(const Puzzle& puzzle)
{
	cout << puzzle.totalNumberOfMoves << " moves was done. ";
	if(Is_Solved(puzzle))
		cout << "And puzzle was solved!\n";
	else
		cout << "But puzzle was not solved!\n";
}

int Load_File(Puzzle& puzzle, char* file_name)
{
	ifstream istream(file_name);
	char buff[4],chr=0;

	if(!istream.is_open())
	{
		cerr << "Error! Reading file couldn't be done...\n";
		return -1;
	}

	if(puzzle.cur_puzzle != NULL)	free(puzzle.cur_puzzle);
	if(puzzle.goal_puzzle != NULL)	free(puzzle.goal_puzzle);

	puzzle.row = puzzle.column = 0;

	for(string buffer ; getline(istream,buffer) ; ++puzzle.row);	// Calculate row's number

	istream.clear();
	istream.seekg(0,ios::beg);

	while(!istream.eof() && chr != '\n')
	{
		istream.get(chr);
		if(chr == ' ' || chr == '\n')
			++puzzle.column;
	}

	istream.seekg(0,ios::beg);

	puzzle.cur_puzzle = (int*)malloc(sizeof(int)*puzzle.row*puzzle.column);

	for(int i=0 ; i < puzzle.row ; ++i)
		for(int j=0 ; j < puzzle.column ; ++j)
		{
			istream >> buff;
			puzzle.cur_puzzle[i*puzzle.column + j] = String_to_Integer(buff);
		}

	Init_Goal_Puzzle(puzzle);
	Set_Blank_Position(puzzle);

	istream.close();
	return 0;
}

int Export_File(const Puzzle& puzzle)
{
	char file_name[32];

	cout << "File name : ";
	cin >> file_name;

	ofstream ostream(file_name);

	if(!ostream.is_open())
	{
		cerr << "Error! Writing file couldn't be done...\n";
		return -1;
	}

	int max_digit=0;
	for(int i=0 ; i < puzzle.row * puzzle.column ; ++i)
		if(max_digit < Digit_Number(puzzle.cur_puzzle[i]))
			max_digit = Digit_Number(puzzle.cur_puzzle[i]);

	
	for(int i=0 ; i < puzzle.row ; ++i)
	{
		for(int j=0 ; j < puzzle.column ; ++j)
		{
			for(int k=Digit_Number(puzzle.cur_puzzle[puzzle.column*i+j]) ; k < max_digit ; ++k)
			{
				if(puzzle.cur_puzzle[puzzle.column*i+j] == -1)
					ostream << "b";
				else
					ostream << "0";
			}

			if(puzzle.cur_puzzle[puzzle.column*i+j] == -1)
				ostream << "b";
			else
				ostream << puzzle.cur_puzzle[puzzle.column*i+j];

			ostream << " ";
		}
		ostream << endl;
	}

	cout << "Writing file could be done successfuly...\n";
	
	ostream.close();
	return 0;
}

int Digit_Number(int num)
{
	int digit=0;

	if(num == 0)	return 1;

	for(; num != 0 ; ++digit,num/=10);
	return digit;
}

int String_to_Integer(char *str)
{
	int num=0,lenght=0;

	while(str[lenght] != '\0')
		lenght++;

	for(int i=0 ; i < lenght ; ++i)
	{
		if(str[i] == 'b')
			num = -1;
		else
			num += Power(10,lenght-i-1) * (str[i] - '0');
	}

	return num;
}

int Power(int base, int exponential)
{
	int num=1;

	for(int i=0 ; i < exponential ; ++i)
		num *= base;

	return num;
}

void Delete_All(Puzzle& puzzle)
{
	if(puzzle.cur_puzzle != NULL) free(puzzle.cur_puzzle);
	if(puzzle.goal_puzzle != NULL) free(puzzle.goal_puzzle);
}