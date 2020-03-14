#include "NP_base.h"

int NPuzzle::Board::totalNumberOfBoards=0;

NPuzzle::NPuzzle(int r, int c)
{
	setsize(r,c);
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
			setsize(r,c);
			shuffle(board.getRow()*board.getCol());
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
		case 'S': shuffle(board.getRow()*board.getCol()); break;
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
int NPuzzle::getInt(const std::string& text, int upperBound, int lowerBound)const
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
std::string NPuzzle::getString(const std::string& text)const
{
	std::string input;

	std::cout << text;
	std::cin >> input;

	return input;
}

/*
	Postcondition: Prints how many moves are made and whether the puzzle is solved
*/
void NPuzzle::printReport(void)const
{
	std::cout << board.numberOfMoves() << " moves was done. ";

	if(board.isSolved() == 1)
		std::cout << "And puzzle was solved!\n";
	else
		std::cout << "But puzzle was not solved!\n";
}

/*
	Precondition: The name of the file to be read is sent to the function
	Postcondition: To read the file, the readFromFile function of the Board class is called and whatever that function returns is returned
*/
bool NPuzzle::readFromFile(const std::string& fileName)
{
	bool state = board.readFromFile(fileName);

	boardVec.resize(1);
	boardVec.front() = board;
	board.setNumberOfMoves();

	return state;
}

/*
	Precondition: The name of the file to be written is sent to the function
	Postcondition: To write to the file, the writeToFile function of the Board class is called and whatever that function returns is returned
*/
bool NPuzzle::writeToFile(const std::string& fileName) {return board.writeToFile(fileName);}

/*
	Precondition: The number of times a random move is sent to the function
	Postcondition: The puzzle is shuffled until numOfRandom and boardVec is resized 1
*/
void NPuzzle::shuffle(int numOfRandom)
{
	do
	{
		reset();
		for(int i=0 ; i < numOfRandom ; ++i)
			moveRandom();
	}while(board.isSolved() == 1);

	board.setNumberOfMoves();
}

/*
	Postcondition: The puzzle is made the target puzzle and boardVec is resized 0
*/
void NPuzzle::reset(void)
{
	boardVec.clear();
	board.reset();
}

/*
	Precondition: The number of row and column is taken as a parameter
	Postcondition: The setSize function of the Board class is called
*/
void NPuzzle::setsize(int thisRow, int thisCol)
{
	if(thisRow < sizeLowerBound || thisRow > sizeUpperBound)
		return;
	if(thisCol < sizeLowerBound || thisCol > sizeUpperBound)
		return;

	board.setSize(thisRow,thisCol);
}

/*
	Postcondition: A valid move is made randomly
*/
void NPuzzle::moveRandom(void)
{
	char ways[4]={'U','D','L','R'};

	while(move(ways[rand()%4]) == 0);
}

/*
	Precondition: the desired movement is taken
	Postcondition:
		The Board class's move function is called and whatever it returns is returned
		boardVec is resized 1
*/
int NPuzzle::move(char event)
{
	int state = board.move(event);

	if(state != -1)
	{
		boardVec.resize(1);
		boardVec.front() = board;
	}

	return state;
}

/*
	Postcondition: 25.000 boards is looked and the result is tried to be reached. If not, the user will be notified
*/
void NPuzzle::solvePuzzle(void)
{
	if(boardVec.size() == 0)
		return;

	int totalChild=0,limitChild=25000;
	char way[4] = {'U','D','L','R'};
	bool state = false;

	for(int i=0 ; i < boardVec.front().NumberOfBoards() && !state && totalChild < limitChild ; ++i)
		for(int j=0 ; j<4 && !state ; ++j,++totalChild)
			state = getChild(boardVec[i],way[j]);

	if(totalChild >= limitChild)
	{
		std::cout << limitChild << " boards have been looked and solution could not founded.\n";
		boardVec.resize(1);
		return;
	}

	if(state)
	{
		std::vector<char> solutionPath;
		Board target = boardVec.back();
		char inverseMove;

		for(auto i=boardVec.end()-1 ; i != boardVec.begin() ; --i)
		{

			if(*i == target)
			{
				solutionPath.insert(solutionPath.begin(),i->lastMove());
				switch(i->lastMove())
				{
					case 'U': inverseMove = 'D'; break;
					case 'D': inverseMove = 'U'; break;
					case 'L': inverseMove = 'R'; break;
					case 'R': inverseMove = 'L'; break;
				}
				target.move(inverseMove);
			}
		}

		for(auto i=solutionPath.begin() ; i<solutionPath.end() ; ++i)
		{
			board.move(*i);
			std::cout << std::endl;
			board.print();
			std::cout << std::endl;
		}
	}
}

bool NPuzzle::getChild(const Board& parent, char event)
{
	Board newBoard;

	newBoard = parent;
	newBoard.move(event);

	if(newBoard.isSolved())
	{
		boardVec.push_back(newBoard);
		return true;
	}
	
	if(checkChild(newBoard))
		boardVec.push_back(newBoard);
	else
		newBoard.setNumberOfBoards(newBoard.NumberOfBoards()-1);
	
	return false;
}

bool NPuzzle::checkChild(const Board& target)
{
	for(auto it = boardVec.begin() ; it != boardVec.end() ; ++it)
		if(target == *it)
			return false;
	return true;
}

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
	Here I can call the print function. But I wanted to use the () operator.
*/
std::ostream& operator>>(std::ostream& out, const NPuzzle& obj)
{
	for(int i=0 ; i < obj.board.getRow() ; ++i)
	{
		for(int j=0 ; j < obj.board.getCol(); ++j)
			switch(obj.board(i,j))
			{
				case 0	: out << "\tX";	break;
				case -1	: out << "\t ";	break;
				default	: out << "\t" << obj.board(i,j);	break;
			}
		out << std::endl;
	}
	return out;
}

std::istream& operator<<(std::istream& in, NPuzzle& obj)
{
	std::string buffer;

	std::cout << "File name: ";
	std::cin >> buffer;
	obj.readFromFile(buffer);

	return in;
}

/*
	Postcondition:
		If the puzzle is available, it is sent to screen
		If not, the function ends
		The space in the board represents -1 and the walls represent 0
*/
void NPuzzle::Board::print(void)const
{
	if(checkBoard(cur) == false)
		return;

	for(int i=0 ; i <row ; ++i)
	{
		for(int j=0 ; j <column ; ++j)
			switch(cur[i][j])
			{
				case 0	: std::cout << "\tX";	break;
				case -1	: std::cout << "\t ";	break;
				default	: std::cout << "\t" << cur[i][j];	break;
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
bool NPuzzle::Board::readFromFile(const std::string& fileName)
{
	std::ifstream istream(fileName);
	char buff[4],chr=0;

	if(!istream.is_open())
	{
		std::cerr << "Error! Reading file couldn't be done...\n";
		return false;
	}

	cur.clear();
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

	cur.resize(row,std::vector<int>(column,-1));

	for(int i=0 ; i <row ; ++i)
		for(int j=0 ; j <column ; ++j)
		{
			istream >> buff;
			cur[i][j] = stringToInt(buff);
		}

	istream.close();

	initGoalBoard();
	setBlankPos();
	return true;
}

/*
	Precondition: The file name to be written is sent to the function
	Postcondition:
		If there is no board available, false is returned
		If it is available, it is written to the file in the desired format
*/
bool NPuzzle::Board::writeToFile(const std::string& fileName)
{
	if(checkBoard(cur) == false)
	{
		std::cerr << "The current board couldn't be founded...\n";
		return false;
	}

	std::ofstream ostream(fileName);

	if(!ostream.is_open())
	{
		std::cerr << "Error! Writing file couldn't be done...\n";
		return false;
	}

	int max_digit=0;
	for(int i=0 ; i <row ; ++i)
		for(int j=0 ; j<column ; ++j)
			if(max_digit < digitNumber(cur[i][j]))
				max_digit = digitNumber(cur[i][j]);
	
	for(int i=0 ; i<row ; ++i)
	{
		for(int j=0 ; j<column ; ++j)
		{
			for(int k=digitNumber(cur[i][j]) ; k < max_digit ; ++k)
			{
				if(cur[i][j] == -1)
					ostream << "b";
				else
					ostream << "0";
			}

			if(cur[i][j] == -1)	ostream << "b";
			else	ostream << cur[i][j];

			if(j < column-1) ostream << " ";
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
	if(checkBoard(cur) == false || checkBoard(goal) == false)
		return;

	for(int i=0 ; i<row ; ++i)
		for(int j=0 ; j<column ; ++j)
			cur[i][j] = goal[i][j];

	setBlankPos();
}

/*
	Precondition: The desired row and column are sent to the function
	Postcondition:
		the board is arranged and reset according to the desired row and column
*/
void NPuzzle::Board::setSize(int thisRow, int thisCol)
{
	row = thisRow;
	column = thisCol;

	cur.clear();
	cur.resize(row,std::vector<int>(column,-1));
	
	initGoalBoard();
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
	if(checkBoard(cur) == false)
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
		int temp = cur[blank_y][blank_x];
		cur[blank_y][blank_x] = cur[blank_y+dirY][blank_x+dirX];
		cur[blank_y+dirY][blank_x+dirX] = temp;
		
		++totalNumberOfMoves;
		prevMove = event;
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
	if(checkBoard(cur) == false || checkBoard(goal) == false)
		return -1;

	int relation=0;

	for(int i=0 ; i<row ; ++i)	// This loop find relation between current puzzle and goal puzzle
		for(int j=0 ; j<column ; ++j)
			if(goal[i][j] == cur[i][j])
				++relation;

	if(relation == row * column)	// If relation number is same size*size
		return 1;
	else
		return 0;
}

int NPuzzle::Board::operator()(const int& i1, const int& i2)const
{
	if((i1 < 0 || i1 >= row) || (i2 < 0 || i2 >= column))
	{
		std::cerr << "The index I1 and I2 are not an element of the board object(core dumped)\n";
		exit(1);
	}

	return cur[i1][i2];
}

const bool NPuzzle::Board::operator==(const Board& other)const
{
	if(row != other.row || column != other.column)
		return false;

	for(int i=0 ; i<row ; ++i)
		for(int j=0 ; j<column ; ++j)
			if(cur[i][j] != other.cur[i][j])
				return false;

	return true;
}

inline bool NPuzzle::Board::checkBoard(const std::vector<std::vector<int> >& vec)const {return vec.size();}

void NPuzzle::Board::initGoalBoard(void)
{
	int i=0,j=0,digitValue=1;

	goal.clear();
	goal.resize(row,std::vector<int>(column,-1));

	if(checkBoard(cur) == true)
		for(i=0 ; i<row ; ++i)
			for(j=0 ; j<column ; ++j)
			{
				goal[i][j] = cur[i][j];
				if(cur[i][j] != 0)
					goal[i][j] = digitValue++;
			}
	else
		for(i=0 ; i<row ; ++i)
			for(j=0 ; j<column ; ++j)
				goal[i][j] = digitValue++;

	goal[i-1][j-1] = -1;
}

void NPuzzle::Board::setBlankPos(void)
{
	for(int i=0 ; i<row ; ++i)
		for(int j=0 ; j<column ; ++j)
			if(cur[i][j] == -1)
				blank_x = j , blank_y = i;
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
	if(	(event == 'U' && blank_y > 0		&& cur[blank_y-1][blank_x]) ||
		(event == 'D' && blank_y < row-1	&& cur[blank_y+1][blank_x]) ||
		(event == 'L' && blank_x > 0		&& cur[blank_y][blank_x-1]) ||
		(event == 'R' && blank_x < column-1	&& cur[blank_y][blank_x+1]))
		return true;
	else
		return false;
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
			num += pow(10,lenght-i-1) * (str[i] - '0');
	}

	return num;
}

int NPuzzle::Board::digitNumber(int num)const
{
	int digit=0;

	if(num == 0)	return 1;

	for(; num != 0 ; ++digit,num/=10);
	return digit;
}