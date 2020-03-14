#include "AbstractBoard.h"

namespace
{
	int digitNumber(int);
	int power(int,int);
	int stringToInt(char*);
	bool isValid(const GTU_Board::AbstractBoard*,const GTU_Board::AbstractBoard*);
}

namespace GTU_Board
{
	int AbstractBoard::totalNumberOfBoards=0;

	void AbstractBoard::print(void)const
	{
		for(int i=0 ; i < getRow() ; ++i)
		{
			for(int j=0 ; j < getColumn() ; ++j)
				switch((*this)(i,j))
				{
					case 0	: std::cout << "\tX";	break;
					case -1	: std::cout << "\t ";	break;
					default	: std::cout << "\t" << (*this)(i,j);	break;
				}
			std::cout << std::endl;
		}
	}

	bool AbstractBoard::readFromFile(const std::string& fileName)
	{
		std::ifstream istream(fileName);
		char buff[4],chr=0;
		int newRow=0,newColumn=0;

		if(!istream.is_open())
		{
			std::cerr << "Error! Reading file couldn't be done...\n";
			return false;
		}

		setSize(0,0);

		for(std::string buffer ; getline(istream,buffer) ; newRow++);	// Calculate row's number

		istream.clear();
		istream.seekg(0,std::ios::beg);

		while(!istream.eof() && chr != '\n')
		{
			istream.get(chr);
			if(chr == ' ' || chr == '\n')
				newColumn++;
		}

		istream.seekg(0,std::ios::beg);

		setSize(newRow,newColumn);

		for(int i=0 ; i < getRow() ; ++i)
			for(int j=0 ; j < getColumn() ; ++j)
			{
				istream >> buff;
				(*this)(i,j) = stringToInt(buff);
			}

		istream.close();

		for(int i=0 ; i < getRow() ; ++i)
			for(int j=0 ; j < getColumn() ; ++j)
				if((*this)(i,j) == -1)
					blank_x = j , blank_y = i;

		return true;
	}

	bool AbstractBoard::writeToFile(const std::string& fileName)const
	{
		std::ofstream ostream(fileName);

		if(!ostream.is_open())
		{
			std::cerr << "Error! Writing file couldn't be done...\n";
			return false;
		}

		int max_digit=0;
		for(int i=0 ; i < getRow() ; ++i)
			for(int j=0 ; j < getColumn() ; ++j)
				if(max_digit < digitNumber((*this)(i,j)))
					max_digit = digitNumber((*this)(i,j));
		
		for(int i=0 ; i < getRow() ; ++i)
		{
			for(int j=0 ; j < getColumn() ; ++j)
			{
				for(int k=digitNumber((*this)(i,j)) ; k < max_digit ; ++k)
				{
					if((*this)(i,j) == -1)
						ostream << "b";
					else
						ostream << "0";
				}

				if((*this)(i,j) == -1)	ostream << "b";
				else	ostream << (*this)(i,j);

				if(j < getColumn()-1) ostream << " ";
			}
			ostream << std::endl;
		}

		std::cout << "Writing file could be done successfuly...\n";
		ostream.close();
		return true;
	}

	void AbstractBoard::reset(void)
	{
		int digitValue=1;

		totalNumberOfMoves=0;
		prevMove='S';

		for(int i=0 ; i < getRow() ; ++i)
			for(int j=0 ; j < getColumn() ; ++j)
				if((*this)(i,j) != 0)
					(*this)(i,j) = digitValue++;

		if(getRow() && getColumn())
		{
			blank_y = getRow()-1;
			blank_x = getColumn()-1;
			(*this)(blank_y,blank_x) = -1;
		}
	}

	bool AbstractBoard::setSize(int receivedRow, int receivedColumn)
	{
		if(!setRow(receivedRow) || !setColumn(receivedColumn))
			return false;
		return true;
	}

	bool AbstractBoard::move(char event)
	{
		int dirX=0,dirY=0;

		switch(event)
		{
			case 'U':	dirX = 0	, dirY = -1;	break;
			case 'D':	dirX = 0	, dirY = 1;		break;
			case 'L':	dirX = -1	, dirY = 0;		break;
			case 'R':	dirX = 1	, dirY = 0;		break;
			default: return false;
		}

		if(canMove(event))
		{
			int temp = (*this)(blank_y,blank_x);
			(*this)(blank_y,blank_x) = (*this)(blank_y+dirY,blank_x+dirX);
			(*this)(blank_y+dirY,blank_x+dirX) = temp;
			
			++totalNumberOfMoves;
			prevMove = event;
			blank_x += dirX;
			blank_y += dirY;
			return true;
		}
		return false;
	}

	bool AbstractBoard::canMove(char event)const
	{
		if(	(event == 'U' && blank_y > 0				&& (*this)(blank_y-1,blank_x)) ||
			(event == 'D' && blank_y < getRow()-1		&& (*this)(blank_y+1,blank_x)) ||
			(event == 'L' && blank_x > 0				&& (*this)(blank_y,blank_x-1)) ||
			(event == 'R' && blank_x < getColumn()-1	&& (*this)(blank_y,blank_x+1)) )
			return true;
		else
			return false;
	}

	bool AbstractBoard::isSolved(void)const
	{
		int digitValue=0,relation=0;

		for(int i=0 ; i < getRow() ; ++i)
			for(int j=0 ; j < getColumn() ; ++j)
				if((*this)(i,j) != 0)
				{
					++digitValue;
					if((*this)(i,j) == digitValue)
						++relation;
				}

		if(relation == digitValue-1)	// If relation number is same digitValue
			return 1;
		else
			return 0;
	}

	const bool AbstractBoard::operator==(const AbstractBoard& other)const
	{
		if(getRow() != other.getRow() || getColumn() != other.getColumn())
			return false;

		for(int i=0 ; i < getRow() ; ++i)
			for(int j=0 ; j < getColumn() ; ++j)
				if((*this)(i,j) != other(i,j))
					return false;

		return true;
	}

	bool AbstractBoard::setRow(int newRow)
	{
		if(newRow < 0)
		{
			row = 0;
			return false;
		}

		row = newRow;
		return true;
	}

	bool AbstractBoard::setColumn(int newColumn)
	{
		if(newColumn < 0)
		{
			column = 0;
			return false;
		}

		column = newColumn;
		return true;
	}

	bool checkValidSequence(const AbstractBoard* const board[], int size)
	{
		if(!size && !board[size-1]->isSolved())
			return false;
			
		for(int i=0 ; i < size-1 ; ++i)
			if(!isValid(board[i],board[i+1]))
				return false;

		return true;
	}
}

namespace
{
	int digitNumber(int num)
	{
		int digit=0;

		if(num == 0)	return 1;

		for(; num != 0 ; ++digit,num/=10);
		return digit;
	}

	int power(int x, int y)
	{
		if(y == 0)
			return 1;
		else if(y%2 == 0)
			return power(x,y/2)*power(x,y/2);
		else
			return x*power(x,y/2)*power(x,y/2);
	}

	int stringToInt(char *str)
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

	bool isValid(const GTU_Board::AbstractBoard* board1, const GTU_Board::AbstractBoard* board2)
	{
		int distanceX = board1->getPosX() - board2->getPosX();
		int distanceY = board1->getPosY() - board2->getPosY();

		if(distanceX < 0) distanceX = -distanceX;
		if(distanceY < 0) distanceY = -distanceY;

		if(distanceX + distanceY == 1)
			return true;
		return false;
	}
}