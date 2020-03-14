#include "NP_base.h"

NPuzzle::NPuzzle(int r, int c)
{
	setSize(r,c);
	shuffle(r*c);
}

/*
	Precondition: Command line parameters are sent to the function
	Postcondition:
		The necessary operations are performed according to the parameters
		If the file name is sent as a parameter and there is no file, the program ends
		If more than 2 parameters are sent from the command line, the program terminates
*/
void NPuzzle::checkProgramState(int argc, char* argv[])
{
	int r,c;

	switch(argc)
	{
		case 1:
			r = getInt("Row : ",9,2);
			c = getInt("Column : ",9,2);
			setSize(r,c);
			shuffle(80);
			break;
		case 2:
			if(readFromFile(argv[1]) == false)
				exit(1);
			break;
		default:
			std::cout << "Too many arguments have been passed!\n";
			exit(1);
	}
}

/*
	Postcondition: The required functions are called according to the input received from the user
*/
void NPuzzle::getEvent(void)
{
	char event = 0;

	std::cout << "Your move: ";
	std::cin >> event;

	switch(event)
	{
		case 'Q': state = State::QUIT; break;
		case 'S': shuffle(board.getRowCol()); break;
		case 'I': moveIntelligent(); break;
		case 'V': solvePuzzle(); break;
		case 'T': printReport(); break;
		case 'E': writeToFile(getString("File name : ")); break;
		case 'O': readFromFile(getString("File name : ")); break;
		case 'U': if(move('U') != 1) std::cout << "Invalid movement!\nCan't move up!\n"; break;
		case 'D': if(move('D') != 1) std::cout << "Invalid movement!\nCan't move down!\n"; break;
		case 'L': if(move('L') != 1) std::cout << "Invalid movement!\nCan't move left!\n"; break;
		case 'R': if(move('R') != 1) std::cout << "Invalid movement!\nCan't move right!\n"; break;
		default: std::cout << "Couldn't find movement like " << event << "\n\n"; break;
	}
}

/*
	Precondition: Lower,upper bound and a text to inform are sent to the function
	Postcondition: A value is returned in the desired range
*/
int NPuzzle::getInt(std::string text, int upperBound, int lowerBound)const
{
	int num;
	bool exit=false;
	
	std::cout << text;

	if(!lowerBound && !upperBound)
	{
		std::cin >> num;
		return num;
	}

	while(!exit)
	{
		std::cin >> num;
		if(num < lowerBound || num > upperBound)
			std::cout << "Invalid number! Number must be [" << lowerBound << "," << upperBound << "] : ";
		else
			exit = true;
	}
	return num;
}

/*
	Precondition: A text to inform are sent to the function
	Postcondition: A string entry is retrieved from the user and returned
*/
std::string NPuzzle::getString(std::string text)const
{
	std::string input;

	std::cout << text;
	std::cin >> input;

	return input;
}

/*
	Postcondition:
		Checks whether the puzzle is solved
		It checks whether the user wants to terminate the program and returns true or false accordingly
*/
bool NPuzzle::gameState(void)
{
	if(state == State::QUIT)
	{
		printReport();
		return false;
	}

	if(board.isSolved() == 1)
	{
		printReport();
		return false;
	}
	else
		state = State::UNSOLVED;
	return true;
}

/*
	Postcondition: Prints how many moves are made and whether the puzzle is solved
*/
void NPuzzle::printReport(void)const
{
	std::cout << totalNumberOfMoves << " moves was done. ";

	if(board.isSolved() == 1)
		std::cout << "And puzzle was solved!\n";
	else
		std::cout << "But puzzle was not solved!\n";
}

/*
	Precondition: The name of the file to be read is sent to the function
	Postcondition: To read the file, the readFromFile function of the Board class is called and whatever that function returns is returned
*/
bool NPuzzle::readFromFile(std::string fileName) {return board.readFromFile(fileName);}

/*
	Precondition: The name of the file to be written is sent to the function
	Postcondition: To write to the file, the writeToFile function of the Board class is called and whatever that function returns is returned
*/
bool NPuzzle::writeToFile(std::string fileName) {return board.writeToFile(fileName);}

/*
	Precondition: The number of times a random move is sent to the function
	Postcondition: The puzzle is shuffled until numOfRandom
*/
void NPuzzle::shuffle(int numOfRandom)
{
	do
	{
		reset();
		for(int i=0 ; i < numOfRandom ; ++i)
			moveRandom();
	}while(board.isSolved() == 1);
}

/*
	Postcondition: The puzzle is made the target puzzle
*/
void NPuzzle::reset(void)
{
	board.reset();
	totalNumberOfMoves=0;
	prevEvent=0;
	eventFlag=0;
	state = State::UNSOLVED;
}

/*
	Precondition: The number of row and column is taken as a parameter
	Postcondition: The setSize function of the Board class is called
*/
void NPuzzle::setSize(int thisRow, int thisCol) {board.setSize(thisRow,thisCol);}

/*
	Postcondition: A valid move is made randomly
*/
void NPuzzle::moveRandom(void)
{
	char ways[4]={'U','D','L','R'};

	while(board.move(ways[rand()%4]) == 0);
}

/*
	Postcondition: The closest move is made to the target
*/
void NPuzzle::moveIntelligent(void)
{
	int i=0,shortest_path=0,index=0;
	char events[4] = {'U','D','L','R'};
	int ways[4]={-1,-1,-1,-1}; // 0-UP,1-DOWN,2-LEFT,3-RIGHT

	if(board.move('X') == -1)
		return;

	for(i=0 ; i<4 ; ++i)
			ways[i] = board.manhattanDistance(events[i]);

	switch(prevEvent)
	{
		case 'U':	prevEvent = 'D' ; break;
		case 'D':	prevEvent = 'U' ; break;
		case 'L':	prevEvent = 'R' ; break;
		case 'R':	prevEvent = 'L' ; break;
		default: break;
	}

	if(eventFlag != 0)
		--eventFlag;
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

	if(eventFlag == 0 && prevEvent == events[index])
		eventFlag = 2;

	prevEvent = events[index];

	move(events[index]);
}

/*
	Precondition: the desired movement is taken
	Postcondition:
		The Board class's move function is called and whatever it returns is returned
		If Board's class's move function return 1, totalNumberOfMoves is added 1
*/
int NPuzzle::move(char event)
{
	int returnValue = board.move(event);

	if(returnValue == 1) ++totalNumberOfMoves;
	return returnValue;
}

/*
	Postcondition: 100,000 moves are made and the result is tried to be reached. If not, the user will be notified
*/
void NPuzzle::solvePuzzle(void)
{
	for(int i=0 ; i < 100000 && board.isSolved() == 0 ; ++i)
	{
		moveIntelligent();
		print();
		std::cout << "\n\n";
	}

	if(board.isSolved() == false)
		std::cout << "\n 100000 moves were made but the puzzle could not be solved.\n\n";
}

/*
	Postcondition:
		If the puzzle is available, it is sent to screen
		If not, the function ends
		The space in the board represents -1 and the walls represent 0
*/
void NPuzzle::Board::print(void)const
{
	if(checkBoard(cur_board) == false)
		return;

	for(int i=0 ; i < row ; ++i)
	{
		for(int j=0 ; j < column ; ++j)
			switch(cur_board[index(i,j)])
			{
				case 0	: std::cout << "\tX";	break;
				case -1	: std::cout << "\t ";	break;
				default	: std::cout << "\t" << cur_board[index(i,j)];	break;
			}
		std::cout << std::endl;
	}
}

/*
	Precondition: The file name to be read is sent to the function
	Postcondition:
		If the file does not exist, false is returned
		Assignments to the required variables are made if available
*/
bool NPuzzle::Board::readFromFile(std::string fileName)
{
	std::ifstream istream(fileName);
	char buff[4],chr=0;

	if(!istream.is_open())
	{
		std::cerr << "Error! Reading file couldn't be done...\n";
		return false;
	}

	if(checkBoard(cur_board) == true) free(cur_board);

	row = column = 0;

	for(std::string buffer ; getline(istream,buffer) ; ++row);	// Calculate row's number

	istream.clear();
	istream.seekg(0,std::ios::beg);

	while(!istream.eof() && chr != '\n')
	{
		istream.get(chr);
		if(chr == ' ' || chr == '\n')
			++column;
	}

	istream.seekg(0,std::ios::beg);

	cur_board = (int*)malloc(sizeof(int)*row*column);

	for(int i=0 ; i < row ; ++i)
		for(int j=0 ; j < column ; ++j)
		{
			istream >> buff;
			cur_board[i*column + j] = stringToInt(buff);
		}

	initGoalBoard(true);
	setBlankPos();

	istream.close();
	return true;
}

/*
	Precondition: The file name to be written is sent to the function
	Postcondition:
		If there is no board available, false is returned
		If it is available, it is written to the file in the desired format
*/
bool NPuzzle::Board::writeToFile(std::string fileName)
{
	std::ofstream ostream(fileName);

	if(!ostream.is_open())
	{
		std::cerr << "Error! Writing file couldn't be done...\n";
		return false;
	}

	if(checkBoard(cur_board) == false)
	{
		std::cerr << "The current board couldn't be founded...\n";
		return false;
	}

	int max_digit=0;
	for(int i=0 ; i < row * column ; ++i)
		if(max_digit < digitNumber(cur_board[i]))
			max_digit = digitNumber(cur_board[i]);

	
	for(int i=0 ; i < row ; ++i)
	{
		for(int j=0 ; j < column ; ++j)
		{
			for(int k=digitNumber(cur_board[column*i+j]) ; k < max_digit ; ++k)
			{
				if(cur_board[column*i+j] == -1)
					ostream << "b";
				else
					ostream << "0";
			}

			if(cur_board[column*i+j] == -1)
				ostream << "b";
			else
				ostream << cur_board[column*i+j];

			ostream << " ";
		}
		ostream << std::endl;
	}

	std::cout << "Writing file could be done successfuly...\n";
	
	ostream.close();
	return true;
}

/*
	Postcondition:
		If there is no board, the function ends
		If there is, it is brought to the final position and the position of the gap is arranged
*/
void NPuzzle::Board::reset(void)
{
	if(checkBoard(cur_board) == false || checkBoard(goal_board) == false)
		return;

	for(int i=0 ; i < row*column ; ++i)
		cur_board[i] = goal_board[i];

	setBlankPos();
}

/*
	Precondition: The desired row and column are sent to the function
	Postcondition:
		If the parameters sent are not in the appropriate range, the function terminates
		If appropriate, the board is arranged and reset according to the desired row and column
*/
void NPuzzle::Board::setSize(int thisRow, int thisCol)
{
	if(thisRow < sizeLowerBound || thisRow > sizeUpperBound)
		return;
	if(thisCol < sizeLowerBound || thisCol > sizeUpperBound)
		return;

	row = thisRow;
	column = thisCol;

	if(checkBoard(cur_board) == true) free(cur_board);	// burası için madde 3
	cur_board = (int*)malloc(sizeof(int)*row*column);
	
	initGoalBoard(false);
	reset();
}

/*
	Precondition: The desired movement is sent to the function
	Postcondition:
		If my board is not present, -1 is returned
		If the passed event is not valid, 0 is returned
		If the passed event is valid, 1 is returned
*/
int NPuzzle::Board::move(char event)
{
	if(checkBoard(cur_board) == false)
		return -1;

	int dirX=0,dirY=0;

	switch(event)
	{
		case 'U':	dirX = 0	, dirY = -1;	break;
		case 'D':	dirX = 0	, dirY = 1;		break;
		case 'L':	dirX = -1	, dirY = 0;		break;
		case 'R':	dirX = 1	, dirY = 0;		break;
		default: return 0;
	}

	if(canMove(event))
	{
		swap(blank_y*column+blank_x,(blank_y+dirY)*column+blank_x+dirX);
		blank_x += dirX;
		blank_y += dirY;
		return 1;
	}
	return 0;
}

/*
	Postcondition:
		If puzzle does not exist, return -1
		if not resolved, return 0
		if resolved, return 1
*/
int NPuzzle::Board::isSolved(void)const
{
	if(checkBoard(cur_board) == false || checkBoard(goal_board) == false)
		return -1;

	int relation=0;

	for(int i=0 ; i < row*column ; ++i)	// This loop find relation between current puzzle and goal puzzle
		if(goal_board[i] == cur_board[i])
			relation++;

	if(relation == row * column)	// If relation number is same size*size
		return 1;
	else
		return 0;
}

/*
	Precondition: The movement to be calculated is sent to the function
	Postcondition:
		If there isn't board available, -1 is returned 
		If there is, calculate and return it
*/
int NPuzzle::Board::manhattanDistance(char event)
{
	if(canMove(event) == false)
		return -1;

	int index=0,exit=0;
	int distance=0,distance_x=0,distance_y=0;

	move(event);

	for(int i=0 ; i < row*column ; ++i)
	{
		if(goal_board[i] != cur_board[i])
		{
			while(exit == 0)
			{
				if(cur_board[index] != goal_board[i])
					++index;
				else
					exit = 1;
			}
			distance_x = i/column - index/column;
			distance_y = i%row - index%row;

			if(distance_x < 0)
				distance_x *= -1;
			if(distance_y < 0)
				distance_y *= -1;

			distance += distance_x;
			distance += distance_y;

			exit=0,index=0;
		}
	}

	if(event == 'U')		move('D');
	else if(event == 'D')	move('U');
	else if(event == 'L')	move('R');
	else if(event == 'R')	move('L');

	return distance;
}

/*
	Precondition: Operation is performed according to the parameter named state
	Postcondition:
		If the state is false, the target is created according to the row and column of the board
		If the state is true, the target board is generated according to the current board(for readFromFile)
*/

void NPuzzle::Board::deleteAll()
{
	if(checkBoard(cur_board) == true) free(cur_board);
	if(checkBoard(goal_board) == true) free(goal_board);
}

void NPuzzle::Board::initGoalBoard(bool state)
{
	int i=0;

	if(checkBoard(goal_board) == true) free(goal_board);
	goal_board = (int*)malloc(sizeof(int)*row*column);

	if(state == false)
	{
		for(i=0 ; i < row*column ; ++i)
			goal_board[i] = i+1;

		goal_board[i-1] = -1;
	}
	else
	{
		int digitValue=1;

		for(i=0 ; i < row*column ; ++i)
		{
			goal_board[i] = cur_board[i];
			if(cur_board[i] != 0)
				goal_board[i] = digitValue++;
		}

		goal_board[i-1] = -1;
	}
}

/*
	Precondition: Board is passed.
	Postcondition: If board is exist, return true. If not,return false
*/
bool NPuzzle::Board::checkBoard(int* board)const
{
	if(board == NULL)
		return false;
	else
		return true;
}

/*
	Precondition: The desired movement is passed
	Postcondition:
		Check whether the desired movement is made
		If can be made, return true
		else false
*/
bool NPuzzle::Board::canMove(char event)const
{
	if(	(event == 'U' && blank_y > 0		&& cur_board[column*(blank_y-1) + blank_x]) ||
		(event == 'D' && blank_y < row-1	&& cur_board[column*(blank_y+1) + blank_x]) ||
		(event == 'L' && blank_x > 0		&& cur_board[column*blank_y + (blank_x-1)]) ||
		(event == 'R' && blank_x < column-1	&& cur_board[column*blank_y + (blank_x+1)])	)
		return true;
	else
		return false;
}

int NPuzzle::Board::index(int i, int j)const {return i*column+j;}

void NPuzzle::Board::swap(int i, int j)
{
	int temp = cur_board[i];
	cur_board[i] = cur_board[j];
	cur_board[j] = temp;
}

void NPuzzle::Board::setBlankPos(void)
{
	for(int i=0 ; i < row*column ; ++i)
		if(cur_board[i] == -1)
			blank_x = i % column , blank_y = i / column;
}

int NPuzzle::Board::stringToInt(char *str)const
{
	int num=0,lenght=0;

	while(str[lenght] != '\0')
		lenght++;

	for(int i=0 ; i < lenght ; ++i)
	{
		if(str[i] == 'b')
			num = -1;
		else
			num += power(10,lenght-i-1) * (str[i] - '0');
	}

	return num;
}

int NPuzzle::Board::power(int base, int exponential)const
{
	int num=1;

	for(int i=0 ; i < exponential ; ++i)
		num *= base;

	return num;
}

int NPuzzle::Board::digitNumber(int num)const
{
	int digit=0;

	if(num == 0)	return 1;

	for(; num != 0 ; ++digit,num/=10);
	return digit;
}