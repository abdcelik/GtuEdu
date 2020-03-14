#include "BoardArray1D.h"

namespace GTU_Board
{
	BoardArray1D::BoardArray1D():BoardArray1D(0,0)
	{}

	BoardArray1D::BoardArray1D(int size):BoardArray1D(size,size)
	{}

	BoardArray1D::BoardArray1D(int newRow, int newColumn):AbstractBoard()
	{
		setSize(newRow,newColumn);
	}

	BoardArray1D::BoardArray1D(const BoardArray1D& other):AbstractBoard()
	{
		setSize(other.getRow(),other.getColumn());

		for(int i=0 ; i < getRow() ; ++i)
			for(int j=0 ; j < getColumn() ; ++j)
				(*this)(i,j) = other(i,j);
	}

	BoardArray1D& BoardArray1D::operator=(const BoardArray1D& rightSide)
	{
		if(this != &rightSide)
		{
			setSize(rightSide.getRow(),rightSide.getColumn());
			
			for(int i=0 ; i < getRow() ; ++i)
				for(int j=0 ; j < getColumn() ; ++j)
					(*this)(i,j) = rightSide(i,j);

			setTotalMoves(rightSide.numberOfMoves());
			setPrevMove(rightSide.lastMove());
		}
		return *this;
	}

	bool BoardArray1D::setSize(int newRow, int newColumn)
	{
		if(!AbstractBoard::setSize(newRow,newColumn))
			return false;

		if(board != nullptr)
		{
			delete[] board;
			board = nullptr;
		}
		board = new int[getRow() * getColumn()];

		for(int i=0 ; i < getRow() ; ++i)
			for(int j=0 ; j < getColumn() ; ++j)
				(*this)(i,j) = -1;

		reset();
		return true;
	}

	const int BoardArray1D::operator()(const int& receivedRow, const int& receivedCol)const
	{
		if(receivedRow < 0 || receivedRow > getRow() ||
		   receivedCol < 0 || receivedCol > getColumn())
		{
			std::cerr << "Invalid index!\n";
			exit(1);
		}

		return board[receivedRow * getColumn() + receivedCol];
	}

	int& BoardArray1D::operator()(const int& receivedRow, const int& receivedCol)
	{
		if(receivedRow < 0 || receivedRow > getRow() ||
		   receivedCol < 0 || receivedCol > getColumn())
		{
			std::cerr << "Invalid index!\n";
			exit(1);
		}

		return board[receivedRow * getColumn() + receivedCol];
	}

	BoardArray1D::~BoardArray1D()
	{
		delete[] board;
	}
}