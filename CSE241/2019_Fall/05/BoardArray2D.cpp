#include "BoardArray2D.h"

namespace GTU_Board
{
	BoardArray2D::BoardArray2D():BoardArray2D(0,0)
	{}

	BoardArray2D::BoardArray2D(int size):BoardArray2D(size,size)
	{}

	BoardArray2D::BoardArray2D(int newRow, int newColumn):AbstractBoard()
	{
		setSize(newRow,newColumn);
	}

	BoardArray2D::BoardArray2D(const BoardArray2D& other):AbstractBoard()
	{
		setSize(other.getRow(),other.getColumn());

		for(int i=0 ; i < getRow() ; ++i)
			for(int j=0 ; j < getColumn() ; ++j)
				(*this)(i,j) = other(i,j);
	}

	BoardArray2D& BoardArray2D::operator=(const BoardArray2D& rightSide)
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

	bool BoardArray2D::setSize(int newRow, int newColumn)
	{
		if(board != nullptr)
		{
			for(int i=0 ; i < getRow() ; ++i)
				delete[] board[i];
			delete[] board;
			board = nullptr;
		}
		
		if(!AbstractBoard::setSize(newRow,newColumn))
			return false;

		board = new int*[getRow()];

		for(int i=0 ; i < getRow() ; ++i)
			board[i] = new int[getColumn()];

		for(int i=0 ; i < getRow() ; ++i)
			for(int j=0 ; j < getColumn() ; ++j)
				(*this)(i,j) = -1;
			
		reset();
		return true;
	}

	const int BoardArray2D::operator()(const int& receivedRow, const int& receivedCol)const
	{
		if(receivedRow < 0 || receivedRow > getRow() ||
		   receivedCol < 0 || receivedCol > getColumn())
		{
			std::cerr << "Invalid index!\n";
			exit(1);
		}

		return board[receivedRow][receivedCol];
	}

	int& BoardArray2D::operator()(const int& receivedRow, const int& receivedCol)
	{
		if(receivedRow < 0 || receivedRow > getRow() ||
		   receivedCol < 0 || receivedCol > getColumn())
		{
			std::cerr << "Invalid index!\n";
			exit(1);
		}

		return board[receivedRow][receivedCol];
	}

	BoardArray2D::~BoardArray2D()
	{
		for(int i=0 ; i < getRow() ; ++i)
			delete[] board[i];
		delete[] board;
	}
}