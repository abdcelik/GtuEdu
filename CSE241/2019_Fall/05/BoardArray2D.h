#ifndef BOARDARRAY2D_H
#define BOARDARRAY2D_H

#include "AbstractBoard.h"

namespace GTU_Board
{
	class BoardArray2D:public AbstractBoard
	{
	public:
		BoardArray2D();
		BoardArray2D(int);
		BoardArray2D(int,int);
		BoardArray2D(const BoardArray2D&);

		BoardArray2D& operator=(const BoardArray2D&);

		virtual bool setSize(int,int);
		virtual const int operator()(const int&,const int&)const;
		virtual int& operator()(const int&,const int&);

		virtual ~BoardArray2D();
	protected:
		int **board=nullptr;
	};
}

#endif