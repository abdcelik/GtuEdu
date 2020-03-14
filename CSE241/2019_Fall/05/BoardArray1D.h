#ifndef BOARDARRAY1D_H
#define BOARDARRAY1D_H

#include "AbstractBoard.h"

namespace GTU_Board
{
	class BoardArray1D:public AbstractBoard
	{
	public:
		BoardArray1D();
		BoardArray1D(int);
		BoardArray1D(int,int);
		BoardArray1D(const BoardArray1D&);
		
		BoardArray1D& operator=(const BoardArray1D&);

		virtual bool setSize(int,int);
		virtual const int operator()(const int&,const int&)const;
		virtual int& operator()(const int&,const int&);

		virtual ~BoardArray1D();
	protected:
		int *board=nullptr;
	};
}

#endif