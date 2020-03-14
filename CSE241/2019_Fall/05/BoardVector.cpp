#include "BoardVector.h"

namespace GTU_Board
{
	BoardVector::BoardVector():BoardVector(0,0)
	{}

	BoardVector::BoardVector(int size):BoardVector(size,size)
	{}

	BoardVector::BoardVector(int newRow, int newColumn):AbstractBoard()
	{
		setSize(newRow,newColumn);
	}

	BoardVector::BoardVector(const BoardVector& other):AbstractBoard()
	{
		setSize(other.getRow(),other.getColumn());
		board = other.board;
	}

	BoardVector& BoardVector::operator=(const BoardVector& rightSide)
	{
		if(this != &rightSide)
		{
			setSize(rightSide.getRow(),rightSide.getColumn());
			board = rightSide.board;

			setTotalMoves(rightSide.numberOfMoves());
			setPrevMove(rightSide.lastMove());
		}
		return *this;
	}

	bool BoardVector::setSize(int newRow, int newColumn)
	{
		if(!AbstractBoard::setSize(newRow,newColumn))
			return false;

		board.clear();
		board.resize(getRow(),std::vector<int>(getColumn(),-1));
		reset();

		return true;
	}

	const int BoardVector::operator()(const int& receivedRow, const int& receivedCol)const
	{
		if(receivedRow < 0 || receivedRow > getRow() ||
		   receivedCol < 0 || receivedCol > getColumn())
		{
			std::cerr << "Invalid index!\n";
			exit(1);
		}

		return board[receivedRow][receivedCol];
	}

	int& BoardVector::operator()(const int& receivedRow, const int& receivedCol)
	{
		if(receivedRow < 0 || receivedRow > getRow() ||
		   receivedCol < 0 || receivedCol > getColumn())
		{
			std::cerr << "Invalid index!\n";
			exit(1);
		}

		return board[receivedRow][receivedCol];
	}

	BoardVector::~BoardVector()
	{
		board.clear();
	}
}